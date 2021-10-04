/**
 * @file
 * @brief This file contains definition of Ini class
 * @author Evilenzo
 * @version 0.1
 */

#include "Ini.hpp"

using std::literals::operator""s;

namespace ES {


Ini::Ini() {}

Ini::Ini(std::istream& is) { parseFromStream(is); }

Ini::Ini(const Ini& ini) : m_sections(ini.m_sections) {}

Ini::Ini(Ini&& ini) : m_sections(std::move(ini.m_sections)) {
    ini.m_sections.erase(ini.m_sections.begin(), ini.m_sections.end());
}

Ini& Ini::operator=(const Ini& ini) {
    if (this == &ini) return *this;

    m_sections = ini.m_sections;

    return *this;
}

Ini& Ini::operator=(Ini&& ini) {
    if (this == &ini) return *this;

    m_sections = std::move(ini.m_sections);
    ini.m_sections.erase(ini.m_sections.begin(), ini.m_sections.end());

    return *this;
}

Section& Ini::operator[](const std::string& name) { return find(name); }

Section& Ini::operator[](std::string&& name) { return find(name); }

void Ini::parseFromStream(std::istream& is) {
    if (is) {
        clear();

        std::string line;
        std::size_t num = 0;
        std::string name;
        std::vector<std::string> names;
        std::vector<std::string> keys;
        Section* section;

        while (getline(is, line)) {
            ++num;

            try {
                beautifyPrefix(line);
                beautifySuffix(line);
                std::string temp = line;
                parseBrackets(temp);

                if (!temp.empty()) {
                    if (names.empty() ||
                        std::find(names.begin(), names.end(), temp) == names.end()) {
                        name = std::move(temp);
                        names.push_back(name);
                        section = &insert(name);
                        keys.clear();
                        continue;
                    }
                } else
                    throw std::runtime_error("Empty section name");
            } catch (const std::runtime_error& err) {
                if (err.what() != "Syntax error: line is not staring with ["s)
                    throw std::runtime_error(err.what() + LINE_BREAKER + "On line: "s +
                                             std::to_string(num));
                else {
                    if (num == 1)
                        throw std::runtime_error(
                            "Ini formatting is wrong.\n"
                            "Missing first section");
                }
            }

            try {
                KV kv(line);
                if (keys.empty() || std::find(keys.begin(), keys.end(), kv.m_key) == keys.end()) {
                    keys.push_back(kv.m_key);
                    section->m_options.push_back(std::move(kv));
                }
            } catch (const std::runtime_error& err) {
                throw std::runtime_error(err.what() + LINE_BREAKER + "On line: "s +
                                         std::to_string(num));
            }
        }
    } else
        throw std::runtime_error("Input stream is broken");
}


void Ini::dumpToStream(std::ostream& os) const {
    for (const Section& temp : m_sections) {
        os << OPENING_BRACKET << temp.m_name << CLOSING_BRACKET << std::endl;

        for (auto& line : temp.m_options) {
            os << line.m_key << EQUAL_SYMBOL << line.m_value << std::endl;
        }
    }
}

void Ini::removeEmpty() {
    m_sections.erase(std::remove_if(m_sections.begin(), m_sections.end(),
                                    [](const Section& i) { return i.m_options.empty(); }),
                     m_sections.end());
}

void Ini::clear() { m_sections.clear(); }

template <typename T>
Section& Ini::find(T name) {
    if (m_sections.size() != 0) {
        auto temp = std::find_if(m_sections.begin(), m_sections.end(),
                                 [name](const Section& i) { return i.m_name == name; });
        if (temp != m_sections.end())
            return *temp;
        else
            return insert(name);
    } else
        return insert(name);
}

template <typename T>
Section& Ini::insert(T name) {
    Section temp(name, std::vector<KV>());
    m_sections.push_back(temp);
    return m_sections.back();
}

Ini::~Ini() {}


std::ostream& operator<<(std::ostream& os, const ES::Ini& container) {
    container.dumpToStream(os);

    return os;
}


}  // namespace ES
