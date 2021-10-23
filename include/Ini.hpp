/**
 * @file
 * @brief This file contains declaration of Ini class
 * @author Evilenzo
 * @version 1.0
 */

#pragma once

#include <fstream>

#include "Error.hpp"
#include "Section.hpp"
#include "Settings.hpp"

namespace ES {


/// @brief Ini container class
class Ini : public Container<Section> {
public:
    /// @brief Settings of parsing
    Settings m_settings = {};

    /**
     * @brief Constructor with param initialization
     * @param settings settings of ini parsing
     * @param name name of this container
     * @param sections vector of Sections
     */
    Ini(Settings settings = {}, std::string name = {}, std::vector<Section> sections = {})
        : m_settings(settings), Container(std::move(name), std::move(sections)) {}

    /// @brief Copy constructor
    Ini(const Ini& ini) = default;

    /// @brief Move constructor
    Ini(Ini&& ini) noexcept = default;

    /// @brief Copy assignment operator
    auto operator=(const Ini& ini) -> Ini& = default;

    /// @brief Move assignment operator
    auto operator=(Ini&& ini) -> Ini& = default;

    /**
     * @brief Finds and returns l-value reference on Section or inserts new
     * @details Tries to find element in the m_elements vector. If found, returns l-value reference
     * to it. If not, calls insert() and returns new one
     * @param name name of searched Section
     * @return reference on Section
     * @see find()
     * @see insert()
     */
    auto operator[](std::string name) -> Section& { return findOrInsert(std::move(name)); }

    /**
     * @brief Finds and returns const l-value reference or boost::none
     * @param name name of searched Section
     * @return l-value reference to found Section or boost::none if not found
     * @see find()
     */
    auto operator[](std::string name) const -> const Section& {
        boost::optional<const Section&> temp = (find(std::move(name)));

        if (temp) {
            return *temp;
        }

        return m_empty;
    }

    /**
     * @brief Parse Ini from input stream
     * @details Parse std::istream line by line beautifying every string. Throws exceptions if
     * stream contains wrong ini formatting
     * @param is std::istream l-value reference
     */
    auto parseFromStream(std::istream& is) -> boost::optional<Error> {
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
                        boost::optional<Error> result = createOption(*section, line, keys);

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

    /**
     * @brief Dump Ini to output stream
     * @details Writes Ini contents to std::ostream with standard ini formatting
     * @param os std::ostream l-value reference
     */
    auto dumpToStream(std::ostream& os) const -> void {
        for (const auto& i : *m_elements) {
            os << i << std::endl;
        }
    }

    /**
     * @brief Operator << for std::ostream
     * @details Same as dumpToStream() but nice
     * @param os std::ostream l-value reference
     * @param container Ini container const reference
     * @return std::ostream l-value reference
     */
    friend auto operator<<(std::ostream& os, const Ini& container) -> std::ostream& {
        container.dumpToStream(os);

        return os;
    }

    /// Empty destructor
    ~Ini() override = default;

private:
    /// @brief Placeholder for const operator[]
    static inline Section m_empty = {};

    /// @brief Construct a new Section
    auto construct(std::string name) -> Section override { return {std::move(name)}; }

    auto createSection(Section** section, std::string& line, bool& skip,
                       std::vector<std::string>& names, std::vector<std::string>& keys) -> void {
        if (m_settings.m_section_duplicate == SectionDuplicate::FIRST) {
            if (!names.empty()) {
                auto entry = std::find(names.begin(), names.end(), line);

                if (entry != names.end()) {
                    skip = true;
                    return;
                }
            }

            *section = &insert(construct(std::move(line)));
            Section* tmp = *section;

            names.push_back(tmp->m_name);
            keys.clear();

        } else if (m_settings.m_section_duplicate == SectionDuplicate::LAST) {
            *section = &operator[](line);
            Section* tmp = *section;

            if (!tmp->empty()) {
                tmp->clear();
                keys.clear();
            }

        } else if (m_settings.m_section_duplicate == SectionDuplicate::UNITE) {
            *section = &operator[](line);
        }

        skip = false;
    }

    auto createOption(Section& section, std::string& line, std::vector<std::string>& keys)
        -> boost::optional<Error> {
        KV option(std::move(line));

        if (!option.wrong()) {
            if (!empty()) {
                if (m_settings.m_option_duplicate == OptionDuplicate::FIRST) {
                    if (!keys.empty()) {
                        auto entry = std::find(keys.begin(), keys.end(), option.m_key);

                        if (entry != keys.end()) {
                            return boost::none;
                        }
                    }

                    keys.push_back(option.m_key);
                    section.m_elements->push_back(std::move(option));

                    return boost::none;

                } else if (m_settings.m_option_duplicate == OptionDuplicate::LAST) {
                    section.findOrInsert(option.m_key) = std::move(option);

                    return boost::none;
                }
            } else {
                return Error(Code::MISSING_FIRST_SECTION);
            }
        }

        return Error(Code::WRONG_LINE);
    }
};


}  // namespace ES
