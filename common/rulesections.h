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
    void Set(const char* name, T value) {
        Rules[name] = value;
    }

    template<typename T>
    RuleSection& Import_From(const INIClass& source, std::function<void(T&)> initialiser) {
        T context = T(*this, source);

        initialiser(context);

        return *this;
    }

    template<typename T>
    RuleSection& Load_From_Ini(const INIClass& ini, const char* name, T default_value) {
        T value;

        auto sectionIsInIni = ini.Section_Present(SectionName);

        if (!sectionIsInIni) {
            DBG_INFO("RuleSection::Load_From_Ini - Loading default for '%s', rule section not found in provided INI: [%s]", name, SectionName);

            Rules[name] = default_value;
            return *this;
        }

        DBG_INFO("RuleSection::Load_From_Ini - Importing rule from INI: [%s] -> %s", SectionName, name);

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
            DBG_FATAL("RuleSection::Set - Mapping for INI type not implemented, rule: [%s] -> %s", SectionName, name);
        }

        Rules[name] = value;

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
private:
    using RuleVariant = std::variant<int, bool, fixed>;
    std::unordered_map<std::string, RuleVariant> Rules;
};

class IniRuleImporter {
public:
    IniRuleImporter(RuleSection& Section, const INIClass& Context) : Section(Section), Context(Context) {}

    template<typename T>
    IniRuleImporter& Load(const char* name, T default_value) {
        Section.Load_From_Ini(Context, name, default_value);

        return *this;
    }

    IniRuleImporter& Load(const char* name) {
        NameInStream = std::make_optional(name);

        return *this;
    }

    template<typename T>
    IniRuleImporter& With_Default(T default_value) {
        if (!NameInStream.has_value()) {
            DBG_FATAL("IniRuleImporter::With_Default - Value passed before rule name in chain/stream assignment");
        }

        Load(NameInStream.value(), default_value);

        NameInStream = std::nullopt;

        return *this;
    }

    IniRuleImporter& operator<<(const char* name) {
        Load(name);

        return *this;
    }

    template<typename T>
    IniRuleImporter& operator<<(T default_value) {
        With_Default<T>(default_value);

        return *this;
    }
private:
    RuleSection& Section;
    const INIClass& Context;
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
