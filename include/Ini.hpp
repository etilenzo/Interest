/**
 * @file
 * @brief This file contains declaration of Ini class
 * @author Evilenzo
 * @version 0.1
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
    /// @brief Constructor with param initialization
    Ini(Settings settings = Settings(), std::string name = "",
        std::vector<Section> sections = std::vector<Section>())
        : m_settings(std::move(settings)), Container(std::move(name), std::move(sections)) {}

    /**
     * @brief Create Ini container from input stream
     * @param is input stream l-value reference
     */
    Ini(std::istream& is) { parseFromStream(is); }

    /**
     * @brief Copy constructor
     * @param ini const l-value reference to another instance
     */
    Ini(const Ini& ini) : m_settings(ini.m_settings), Container(ini) {}

    /**
     * @brief Move constructor
     * @param ini r-value reference to another instance
     */
    Ini(Ini&& ini) noexcept : m_settings(std::move(ini.m_settings)), Container(ini) {}

    /**
     * @brief Parse Ini from input stream
     * @details Parse std::istream line by line beautifiing every string. Throws exceptions if
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
    // friend std::ostream& operator<<(std::ostream& os, const Ini& container);

    /// Empty destructor
    ~Ini() = default;

private:
    /// @brief Settings of parsing
    Settings m_settings;

    /**
     * @brief Overrided construct function
     * @param name of new Section
     * @return created Section class
     */
    Section construct(std::string name) override;
};


}  // namespace ES
