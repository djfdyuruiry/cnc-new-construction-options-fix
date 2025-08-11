#ifndef RULEPROPERTIES_H
#define RULEPROPERTIES_H

#include <functional>
#include <optional>
#include <stdexcept>
#include <string>
#include <typeinfo>
#include <unordered_map>
#include <variant>

#include <common/ini.h>
#include <fixed.h>

class RuleSectionContext;

class RuleSection {
public:
    const char* SectionName;

    RuleSection(const char* section_name) : SectionName(section_name) {}

    template<typename T>
    void Set(const char* name, T value) {
        properties[name] = value;
    }

    template<typename T>
    RuleSection& With_Context(const INIClass& source, std::function<void(T&)> initialiser) {
        T context = T(*this, source);

        initialiser(context);

        return *this;
    }

    template<typename T>
    RuleSection& Set_With_Ini(const INIClass& ini, const char* name, T default_value) {
        T value;

        auto sectionIsInIni = ini.Section_Present(SectionName);

        if (!sectionIsInIni) {
            DBG_INFO("RuleSection::Set_With_Ini - Loading default for '%s', rule section not found in provided INI: [%s]", name, SectionName);

            properties[name] = default_value;
            return *this;
        }

        DBG_INFO("RuleSection::Set_With_Ini - Importing rule from INI: [%s] -> %s", SectionName, name);

        if constexpr (std::is_same_v<T, int>) {
            value = ini.Get_Int(SectionName, name, default_value);

            DBG_INFO("RuleSection::Set_With_Ini - Resolved value: %d | (default=%d)", value, default_value);
        } else if constexpr (std::is_same_v<T, bool>) {
            value = ini.Get_Bool(SectionName, name, default_value);

            DBG_INFO("RuleSection::Set_With_Ini - Resolved value: %s | (default=%s)", value ? "true" : "false", default_value ? "true" : "false");
        } else if constexpr (std::is_same_v<T, fixed>) {
            value = ini.Get_Fixed(SectionName, name, default_value);

            DBG_INFO("RuleSection::Set_With_Ini - Resolved value: %s | (default=%s)", value.As_ASCII(), default_value.As_ASCII());
        } else {
            DBG_FATAL("RuleSection::Set - Mapping for INI type not implemented, rule: [%s] -> %s", SectionName, name);
        }

        properties[name] = value;

        return *this;
    }

    template<typename T>
    T Get(const char* name) const {
        auto it = properties.find(name);

        if (it != properties.end()) {
            return std::get<T>(it->second);
        }

        DBG_FATAL("RuleSection::Get - Rule not found in section: [%s] -> %s", SectionName, name);
    }

private:
    using RulePropertyVariant = std::variant<int, bool, fixed>;
    std::unordered_map<std::string, RulePropertyVariant> properties;
};

class RuleSectionContext {
public:
    RuleSectionContext(RuleSection& Section, const INIClass& Context) : Section(Section), Context(Context) {}

    template<typename T>
    RuleSectionContext& Set(const char* name, T default_value) {
        Section.Set_With_Ini(Context, name, default_value);

        return *this;
    }

    RuleSectionContext& operator<<(const char* name) {
        NameInStream = std::make_optional(name);

        return *this;
    }

    template<typename T>
    RuleSectionContext& operator<<(T default_value) {
        if (!NameInStream.has_value()) {
            DBG_FATAL("RuleSectionContext::operator<< - Value passed before rule name in streaming assignment");
        }

        Section.Set_With_Ini(Context, NameInStream.value(), default_value);

        NameInStream = std::nullopt;

        return *this;
    }
private:
    RuleSection& Section;
    const INIClass& Context;
    std::optional<const char*> NameInStream;
};

#endif
