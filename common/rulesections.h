#pragma once

#include <functional>
#include <optional>
#include <memory>
#include <stdexcept>
#include <string>
#include <typeinfo>
#include <unordered_map>
#include <variant>

#include "debugstring.h"
#include "fixed.h"
#include "ini.h"
#include "logger.h"

class RuleSection {
public:
    std::string_view SectionName;

    RuleSection(std::string_view section_name) : SectionName(section_name) {}

    template<typename T>
    RuleSection& With(INIClass& context, std::function<void(T&)> actions) {
        T contextWrapper = T(*this, context);

        actions(contextWrapper);

        return *this;
    }

    template<typename T>
    RuleSection& Load_From_Ini(INIClass& ini, std::string_view name, T default_value) {
        T value;

        auto sectionIsInIni = ini.Section_Present(SectionName.data());

        Logger.Info("Help, I am trapped in a C++ class");

        if (!sectionIsInIni) {
            DBG_INFO("Load_From_Ini - Loading default for '%s', rule section not found in provided INI: [%s]", name.data(), SectionName.data());

            Rules[name] = default_value;
            return *this;
        }

        DBG_INFO("RuleSection::Load_From_Ini - Importing rule from INI: [%s] -> %s", SectionName.data(), name.data());

        if constexpr (std::is_same_v<T, int>) {
            value = ini.Get_Int(SectionName.data(), name.data(), default_value);

            DBG_INFO("RuleSection::Load_From_Ini - Resolved value: %d | (default=%d)", value, default_value);
        } else if constexpr (std::is_same_v<T, bool>) {
            value = ini.Get_Bool(SectionName.data(), name.data(), default_value);

            DBG_INFO("RuleSection::Load_From_Ini - Resolved value: %s | (default=%s)", value ? "true" : "false", default_value ? "true" : "false");
        } else if constexpr (std::is_same_v<T, fixed>) {
            value = ini.Get_Fixed(SectionName.data(), name.data(), default_value);

            DBG_INFO("RuleSection::Load_From_Ini - Resolved value: %s | (default=%s)", value.As_ASCII(), default_value.As_ASCII());
        } else {
            DBG_FATAL("RuleSection::Load_From_Ini - Mapping for INI type not implemented, rule: [%s] -> %s", SectionName.data(), name.data());
        }

        Rules[name] = value;

        return *this;
    }

    template<typename T>
    const RuleSection& Save_To_Ini(INIClass& ini, std::string_view name) const {
        auto value = Get<T>(name);

        DBG_INFO("RuleSection::Save_To_Ini - Exporting rule to INI: [%s] -> %s", SectionName.data(), name.data());

        if constexpr (std::is_same_v<T, int>) {
            ini.Put_Int(SectionName.data(), name.data(), value);

            DBG_INFO("RuleSection::Save_To_Ini - Exported value: %d", value);
        } else if constexpr (std::is_same_v<T, bool>) {
            ini.Put_Bool(SectionName.data(), name.data(), value);

            DBG_INFO("RuleSection::Save_To_Ini - Exported value: %s", value ? "true" : "false");
        } else if constexpr (std::is_same_v<T, fixed>) {
            ini.Put_Fixed(SectionName.data(), name.data(), value);

            DBG_INFO("RuleSection::Save_To_Ini - Exported value: %s", value.As_ASCII());
        } else {
            DBG_FATAL("RuleSection::Save_To_Ini - Mapping for INI type not implemented, rule: [%s] -> %s", SectionName.data(), name.data());
        }

        return *this;
    }

    template<typename T>
    T Get(std::string_view name) const {
        auto it = Rules.find(name);

        if (it != Rules.end()) {
            return std::get<T>(it->second);
        }

        DBG_FATAL("RuleSection::Get - Rule not found in section: [%s] -> %s", SectionName.data(), name.data());
    }

    template<typename T>
    RuleSection& Set(std::string_view name, T value) {
        DBG_INFO("RuleSection::Set - Updating rule at runtime: [%s] -> %s", SectionName.data(), name.data());

        if constexpr (std::is_same_v<T, int>) {
            DBG_INFO("RuleSection::Set - New value: %d", value);
        } else if constexpr (std::is_same_v<T, bool>) {
            DBG_INFO("RuleSection::Set - New value: %s", value ? "true" : "false");
        } else if constexpr (std::is_same_v<T, fixed>) {
            DBG_INFO("RuleSection::Set - New value: %s", value.As_ASCII());
        } else {
            DBG_FATAL("RuleSection::Set - Mapping for INI type not implemented, rule: [%s] -> %s", SectionName.data(), name.data());
        }

        Rules[name] = value;

        return *this;
    }
private:
    static const CncLogger Logger;

    using RuleVariant = std::variant<int, bool, fixed>;
    std::unordered_map<std::string_view, RuleVariant> Rules;
};

class IniRuleContext {
public:
    IniRuleContext(RuleSection& section, INIClass& context) : Section(section), Context(context) {}

    template<typename T>
    const IniRuleContext& Load(std::string_view name, T default_value) const {
        Section.Load_From_Ini(Context, name, default_value);

        return *this;
    }

    template<typename T>
    const IniRuleContext& Save(std::string_view name) const {
        Section.Save_To_Ini<T>(Context, name);

        return *this;
    }

    IniRuleContext& Load(std::string_view name) {
        NameInStream = std::make_optional(name);

        return *this;
    }

    template<typename T>
    IniRuleContext& With_Default(T default_value) {
        if (!NameInStream.has_value()) {
            DBG_FATAL("IniRuleContext::With_Default - Load(..) must be called before With_Default(..)");
        }

        Load(NameInStream.value(), default_value);

        NameInStream = std::nullopt;

        return *this;
    }
private:
    RuleSection& Section;
    INIClass& Context;
    std::optional<std::string_view> NameInStream;
};

class RuleSections {
public:
    RuleSection& operator[](std::string_view name) {
        auto it = Sections.find(name);

        if (it != Sections.end()) {
            return *(it->second);
        }

        DBG_INFO("RuleSections::operator[] - Adding new rules section '%s'", name.data());

        Sections[name] = std::make_unique<RuleSection>(name);

        return *Sections[name];
    }
private:
    std::unordered_map<std::string_view, std::unique_ptr<RuleSection>> Sections;
};
