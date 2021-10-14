/**
 * @file
 * @brief This file contains definitions of Ini class and Error struct
 * @author Evilenzo
 * @version 0.2
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

const Section& Ini::operator[](std::string name) const {
    boost::optional<const Section&> temp = (find(std::move(name)));

    if (temp) {
        return *temp;
    }

    return m_empty;
}

boost::optional<Error> Ini::parseFromStream(std::istream& is) {
    if (is) {
        if (m_settings.m_parse_type == ParseType::NEW) {
            clear();
        }

        std::size_t num{0};
        std::string line;
        bool skip = false;

        std::vector<std::string> names;
        std::vector<std::string> keys;

        Section* section = nullptr;

        while (getline(is, line)) {
            ++num;

            delComment(line);

            if (m_settings.m_quotation_marks == QuotationMarks::REMOVE) {
                delQuotationMarks(line);
            }

            prefixDelSpaces(line);
            suffixDelBreakers(line);

            if (!line.empty()) {
                std::string copy = line;
                trimBrackets(copy);

                if (!copy.empty()) {
                    createSection(&section, copy, skip, names, keys);
                } else if (!skip) {
                    boost::optional<Error> result = createKV(*section, line, keys);

                    if (result) {
                        return result;
                    }
                }
            }
        }

        return boost::none;
    }

    return Error(Code::BROKEN_INPUT_STREAM, 0);
}

void Ini::dumpToStream(std::ostream& os) const {
    for (const auto& i : *m_elements) {
        os << i;
    }
}

Section Ini::construct(std::string name) { return {std::move(name)}; }

void Ini::createSection(Section** section, std::string& line, bool& skip,
                        std::vector<std::string>& names, std::vector<std::string>& keys) {
    if (m_settings.m_section_duplicate == SectionDuplicate::FIRST) {
        if (!names.empty()) {
            auto entry = std::find(names.begin(), names.end(), line);

            if (entry != names.end()) {
                skip = true;
                return;
            }
        }

        *section = &insert(Section(std::move(line)));
        Section* tmp = *section;

        names.push_back(tmp->m_name);
        keys.clear();

    } else if (m_settings.m_section_duplicate == SectionDuplicate::LAST) {
        *section = &operator[](line);
        Section* tmp = *section;

        if (!tmp->empty()) {
            tmp->clear();
        }

    } else if (m_settings.m_section_duplicate == SectionDuplicate::UNITE) {
        *section = &operator[](line);
    }

    skip = false;
}

boost::optional<Error> Ini::createKV(Section& section, std::string& line,
                                     std::vector<std::string>& keys) {
    KV kv(std::move(line));

    if (!kv.empty()) {
        if (!empty()) {
            if (m_settings.m_option_duplicate == OptionDuplicate::FIRST) {
                if (!keys.empty()) {
                    auto entry = std::find(keys.begin(), keys.end(), kv.m_key);

                    if (entry != keys.end()) {
                        return boost::none;
                    }
                }

                keys.push_back(kv.m_key);
                section.m_elements->push_back(std::move(kv));

                return boost::none;

            } else if (m_settings.m_option_duplicate == OptionDuplicate::LAST) {
                section.findOrInsert(kv.m_key) = std::move(kv);

                return boost::none;
            }
        } else {
            return Error(Code::MISSING_FIRST_SECTION);
        }
    }

    return Error(Code::WRONG_LINE);
}

std::ostream& operator<<(std::ostream& os, const ES::Ini& container) {
    container.dumpToStream(os);

    return os;
}


}  // namespace ES
