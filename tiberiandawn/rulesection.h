#ifndef RULEPROPERTIES_H
#define RULEPROPERTIES_H

#include <string>
#include <unordered_map>
#include <variant>
#include <stdexcept>
#include <typeinfo>

#include <common/ini.h>
#include <fixed.h>

class RuleSection {
public:
    const char* SectionName;

    RuleSection(const char* sectionName) : SectionName(sectionName) {}

    template<typename T>
    void Set(const char* name, T value) {
        properties[name] = value;
    }

    template<typename T>
    void Set(const INIClass& ini, const char* name, T defaultValue) {
        T value;

        if constexpr (std::is_same_v<T, int>) {
            value = ini.Get_Int(SectionName, name, defaultValue);
        } else if constexpr (std::is_same_v<T, bool>) {
            value = ini.Get_Bool(SectionName, name, defaultValue);
        } else if constexpr (std::is_same_v<T, fixed>) {
            value = ini.Get_Fixed(SectionName, name, defaultValue);
        } else {
            DBG_FATAL("Mapping for INI type not implemented in RuleProperties::Set for rule: [%s] -> %s", SectionName, name);
        }

        properties[name] = value;
    }

    template<typename T>
    T Get(const char* name) const {
        auto it = properties.find(name);

        if (it != properties.end()) {
            return std::get<T>(it->second);
        }

        DBG_FATAL("Rule not found in RuleProperties section: [%s] -> %s", SectionName, name);
    }

private:
    using RulePropertyVariant = std::variant<int, bool, fixed>;
    std::unordered_map<std::string, RulePropertyVariant> properties;
};

#endif
