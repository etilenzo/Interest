/**
 * @file
 * @brief This file contains definitions of Ini class and Error struct
 * @author Evilenzo
 * @version 0.1
 */

#include "Ini.hpp"

namespace ES {


boost::optional<Error> Ini::parseFromStream(std::istream& is) {
    if (is) {
        clear();

        std::string line;
        std::size_t num = 0;
        std::string name;
        Section* section = nullptr;
        std::vector<const std::string&> names;
        std::vector<const std::string&> keys;

        while (getline(is, line)) {
            ++num;

            delComment(line);
            if (m_settings.m_spaces == Spaces::REMOVE) {
                prefixDelSpaces(line);
            }
            suffixDelBreakers(line);

            if (!line.empty()) {
                std::string temp = line;
                trimBrackets(temp);

                if (!temp.empty()) {
                    if (names.empty() ||
                        std::find(names.begin(), names.end(), temp) == names.end()) {
                        name = std::move(temp);
                        section = &insert(std::move(name));
                        names.push_back(section->m_name);
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
                            section->m_elements->push_back(std::move(kv));
                        }
                    } else {
                        return Error(Code::WRONG_STRING, num);
                    }
                }
            }
        }

        return boost::none;
    }

    return Error(Code::BROKEN_INPUT_STREAM, 0);
}

void Ini::dumpToStream(std::ostream& os) const {
    for (const Section& temp : *m_elements) {
        os << OPENING_BRACKET << temp.m_name << CLOSING_BRACKET << std::endl;

        for (const auto& line : *temp.m_elements) {
            os << line.m_key << EQUAL_SYMBOL << line.m_value << std::endl;
        }
    }
}

Section Ini::construct(std::string name) { return Section(name, std::vector<KV>()); }

std::ostream& operator<<(std::ostream& os, const ES::Ini& container) {
    container.dumpToStream(os);

    return os;
}


}  // namespace ES
