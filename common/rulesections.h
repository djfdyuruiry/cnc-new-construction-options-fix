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

class RuleSection {
public:
    const char* SectionName;

    RuleSection(const char* section_name) : SectionName(section_name) {}

    template<typename T>
    RuleSection& With(INIClass& context, std::function<void(T&)> actions) {
        T contextWrapper = T(*this, context);

        actions(contextWrapper);

        return *this;
    }

    template<typename T>
    RuleSection& Load_From_Ini(INIClass& ini, const char* name, T default_value) {
        T value;

        auto sectionIsInIni = ini.Section_Present(SectionName);

        if (!sectionIsInIni) {
            DBG_INFO("RuleSection::Load_From_Ini - Loading default for '%s', rule section not found in provided INI: [%s]", name, SectionName);

            Rules[name] = default_value;
            return *this;
        }

        DBG_INFO("%s - Importing rule from INI: [%s] -> %s", __PRETTY_FUNCTION__, SectionName, name);

        if constexpr (std::is_same_v<T, int>) {
            value = ini.Get_Int(SectionName, name, default_value);

            DBG_INFO("RuleSection::Load_From_Ini - Resolved value: %d | (default=%d)", value, default_value);
        } else if constexpr (std::is_same_v<T, bool>) {
            value = ini.Get_Bool(SectionName, name, default_value);

            DBG_INFO("RuleSection::Load_From_Ini - Resolved value: %s | (default=%s)", value ? "true" : "false", default_value ? "true" : "false");
        } else if constexpr (std::is_same_v<T, fixed>) {
            value = ini.Get_Fixed(SectionName, name, default_value);

            DBG_INFO("RuleSection::Load_From_Ini - Resolved value: %s | (default=%s)", value.As_ASCII(), default_value.As_ASCII());
        } else {
            DBG_FATAL("RuleSection::Load_From_Ini - Mapping for INI type not implemented, rule: [%s] -> %s", SectionName, name);
        }

        Rules[name] = value;

        return *this;
    }

    template<typename T>
    const RuleSection& Save_To_Ini(INIClass& ini, const char* name) const {
        auto value = Get<T>(name);

        DBG_INFO("RuleSection::Save_To_Ini - Exporting rule to INI: [%s] -> %s", SectionName, name);

        if constexpr (std::is_same_v<T, int>) {
            ini.Put_Int(SectionName, name, value);

            DBG_INFO("RuleSection::Save_To_Ini - Exported value: %d", value);
        } else if constexpr (std::is_same_v<T, bool>) {
            ini.Put_Bool(SectionName, name, value);

            DBG_INFO("RuleSection::Save_To_Ini - Exported value: %s", value ? "true" : "false");
        } else if constexpr (std::is_same_v<T, fixed>) {
            ini.Put_Fixed(SectionName, name, value);

            DBG_INFO("RuleSection::Save_To_Ini - Exported value: %s", value.As_ASCII());
        } else {
            DBG_FATAL("RuleSection::Save_To_Ini - Mapping for INI type not implemented, rule: [%s] -> %s", SectionName, name);
        }

        return *this;
    }

    template<typename T>
    T Get(const char* name) const {
        auto it = Rules.find(name);

        if (it != Rules.end()) {
            return std::get<T>(it->second);
        }

        DBG_FATAL("RuleSection::Get - Rule not found in section: [%s] -> %s", SectionName, name);
    }

    template<typename T>
    RuleSection& Set(const char* name, T value) {
        DBG_INFO("RuleSection::Set - Updating rule at runtime: [%s] -> %s", SectionName, name);

        if constexpr (std::is_same_v<T, int>) {
            DBG_INFO("RuleSection::Set - New value: %d", value);
        } else if constexpr (std::is_same_v<T, bool>) {
            DBG_INFO("RuleSection::Set - New value: %s", value ? "true" : "false");
        } else if constexpr (std::is_same_v<T, fixed>) {
            DBG_INFO("RuleSection::Set - New value: %s", value.As_ASCII());
        } else {
            DBG_FATAL("RuleSection::Set - Mapping for INI type not implemented, rule: [%s] -> %s", SectionName, name);
        }

        Rules[name] = value;

        return *this;
    }
private:
    using RuleVariant = std::variant<int, bool, fixed>;
    std::unordered_map<std::string, RuleVariant> Rules;
};

class IniRuleContext {
public:
    IniRuleContext(RuleSection& Section, INIClass& Context) : Section(Section), Context(Context) {}

    template<typename T>
    const IniRuleContext& Load(const char* name, T default_value) const {
        Section.Load_From_Ini(Context, name, default_value);

        return *this;
    }

    template<typename T>
    const IniRuleContext& Save(const char* name) const {
        Section.Save_To_Ini<T>(Context, name);

        return *this;
    }

    IniRuleContext& Load(const char* name) {
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
    std::optional<const char*> NameInStream;
};

class RuleSections {
public:
    RuleSection& operator[](const char* name) {
        auto it = Sections.find(name);

        if (it != Sections.end()) {
            return *(it->second);
        }

        DBG_INFO("RuleSections::operator[] - Adding new rules section '%s'", name);

        Sections[name] = std::make_unique<RuleSection>(name);

        return *Sections[name];
    }
private:
    std::unordered_map<std::string, std::unique_ptr<RuleSection>> Sections;
};
