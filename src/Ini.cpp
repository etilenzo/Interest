/**
 * @file
 * @brief This file contains definitions of Ini class and Error struct
 * @author Evilenzo
 * @version 0.1
 */

#include "Ini.hpp"

namespace ES {


Section& Ini::operator[](std::string name) {
    boost::optional<Section&> element = find(name);

    if (element) {
        return *element;
    }

    return insert(Section(std::move(name)));
}

boost::optional<const Section&> Ini::operator[](std::string name) const {
    return boost::optional<const Section&>(find(std::move(name)));
}

boost::optional<Error> Ini::parseFromStream(std::istream& is) {
    if (is) {
        if (m_settings.m_parse_type == ParseType::NEW) {
            clear();
        }

        std::string line;
        std::size_t num = 0;
        bool skip = true;
        Section* section = nullptr;
        std::vector<std::string> names;
        std::vector<std::string> keys;

        while (getline(is, line)) {
            ++num;

            delComment(line);

            if (m_settings.m_quotation_marks == QuotationMarks::REMOVE) {
                delQuotationMarks(line);
            }

            prefixDelSpaces(line);
            suffixDelBreakers(line);

            if (!line.empty()) {
                std::string temp = line;
                trimBrackets(temp);

                if (!temp.empty()) {
                    if (m_settings.m_section_duplicate == SectionDuplicate::FIRST) {
                        if (names.empty() ||
                            std::find(names.begin(), names.end(), temp) == names.end()) {
                            section = &insert(Section(std::move(temp)));
                            names.push_back(section->m_name);
                            keys.clear();
                            skip = false;
                        } else {
                            skip = true;
                        }
                    } else if (m_settings.m_section_duplicate == SectionDuplicate::LAST) {
                        section = &operator[](temp);
                        section->clear();
                    } else if (m_settings.m_section_duplicate == SectionDuplicate::UNITE) {
                        section = &operator[](temp);
                    }
                } else if (!skip) {
                    KV kv(std::move(line));

                    if (!kv.empty()) {
                        if (section != nullptr) {
                            if (m_settings.m_option_duplicate == OptionDuplicate::FIRST) {
                                if (keys.empty() ||
                                    std::find(keys.begin(), keys.end(), kv.m_key) == keys.end()) {
                                    keys.push_back(kv.m_key);
                                    section->m_elements->push_back(std::move(kv));
                                }
                            } else if (m_settings.m_option_duplicate == OptionDuplicate::LAST) {
                                section->findOrInsert(kv.m_key) = std::move(kv);
                            }
                        }
                    } else {
                        return Error(Code::MISSING_FIRST_SECTION, num);
                    }
                } else {
                    return Error(Code::WRONG_STRING, num);
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

Section Ini::construct(std::string name) { return Section(std::move(name)); }

/*std::ostream& operator<<(std::ostream& os, const ES::Ini& container) {
    container.dumpToStream(os);

    return os;
}*/


}  // namespace ES
