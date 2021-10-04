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

std::optional<Error> Ini::parseFromStream(std::istream& is) {
    if (is) {
        clear();

        std::string line;
        std::size_t num = 0;
        std::string name;
        Section* section;
        std::vector<std::string> names;
        std::vector<std::string> keys;

        while (getline(is, line)) {
            ++num;

            removeComment(line);
            beautifyPrefix(line);
            removeBreakers(line);

            if (!line.empty()) {
                std::string temp = line;
                trimBrackets(temp);

                if (!temp.empty()) {
                    if (names.empty() ||
                        std::find(names.begin(), names.end(), temp) == names.end()) {
                        name = std::move(temp);
                        names.push_back(name);
                        section = &insert(std::move(name));
                        keys.clear();

                        continue;
                    }
                } else if (num == 1) {
                    return Error(Code::MISSING_FIRST_SECTION, num);
                } else {
                    KV kv(std::move(line));
                    if (!kv.empty()) {
                        if (keys.empty() ||
                            std::find(keys.begin(), keys.end(), kv.m_key) == keys.end()) {
                            keys.push_back(kv.m_key);
                            section->m_options.push_back(std::move(kv));
                        }
                    } else {
                        return Error(Code::WRONG_STRING, num);
                    }
                }
            }
        }

        return std::nullopt;
    } else
        return Error(Code::BROKEN_INPUT_STREAM, 0);
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
