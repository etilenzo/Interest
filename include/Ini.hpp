/**
 * @file
 * @brief This file contains declaration of Ini class
 * @author Evilenzo
 * @version 0.2
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
    Settings m_settings;

    /**
     * @brief Constructor with param initialization
     * @param settings settings of ini parsing
     * @param name name of this container
     * @param sections vector of Sections
     */
    Ini(Settings settings = Settings(), std::string name = std::string(),
        std::vector<Section> sections = std::vector<Section>())
        : m_settings(settings), Container(std::move(name), std::move(sections)) {}

    /// @brief Copy constructor
    Ini(const Ini& ini) = default;

    /// @brief Move constructor
    Ini(Ini&& ini) noexcept = default;

    /// @brief Copy assignment operator
    Ini& operator=(const Ini& ini) = default;

    /// @brief Move assignment operator
    Ini& operator=(Ini&& ini) = default;

    /**
     * @brief Finds and returns l-value reference on Section or inserts new
     * @details Tries to find element in the m_elements vector. If found, returns l-value reference
     * to it. If not, calls insert() and returns new one
     * @param name name of searched Section
     * @return reference on Section
     * @see find()
     * @see insert()
     */
    Section& operator[](std::string name);

    /**
     * @brief Finds and returns const l-value reference or boost::none
     * @param name name of searched Section
     * @return l-value reference to found Section or boost::none if not found
     * @see find()
     */
    const Section& operator[](std::string name) const;

    /**
     * @brief Parse Ini from input stream
     * @details Parse std::istream line by line beautifying every string. Throws exceptions if
     * stream contains wrong ini formatting
     * @param is std::istream l-value reference
     */
    boost::optional<Error> parseFromStream(std::istream& is);

    /**
     * @brief Dump Ini to output stream
     * @details Writes Ini contents to std::ostream with standard ini formatting
     * @param os std::ostream l-value reference
     */
    void dumpToStream(std::ostream& os) const;

    /**
     * @brief Operator << for std::ostream
     * @details Same as dumpToStream() but nice
     * @param os std::ostream l-value reference
     * @param container Ini container const reference
     * @return std::ostream l-value reference
     */
    friend std::ostream& operator<<(std::ostream& os, const Ini& container);

    /// Empty destructor
    ~Ini() override = default;

private:
    /// @brief Placeholder for const []
    static inline Section m_empty = Section();

    /// @brief Construct a new Section
    Section construct(std::string name) override;

    void createSection(Section** section, std::string& line, bool& skip,
                       std::vector<std::string>& names, std::vector<std::string>& keys);

    boost::optional<Error> createKV(Section& section, std::string& line,
                                    std::vector<std::string>& keys);
};


}  // namespace ES
