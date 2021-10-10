/**
 * @file
 * @brief This file contains declaration of Section class
 * @author Evilenzo
 * @version 0.1
 */

#pragma once

#include <algorithm>
#include <numeric>

#include "Container.hpp"
#include "KV.hpp"

namespace ES {


/// @brief Section container class
class Section : public Container<KV> {
public:
    /**
     * @brief Container with param initialization
     * @param name m_name
     * @param options m_options
     */
    Section(std::string name = std::string(), std::vector<KV> options = std::vector<KV>())
        : Container(std::move(name), std::move(options)) {}

    /// @brief Copy constructor
    Section(const Section& section) : Container(section) {}

    /// @brief Move constructor
    Section(Section&& section) noexcept : Container(section) {}

    /// @brief Copy assignment operator
    Section& operator=(const Section& section) = default;

    /// @brief Move assignment operator
    Section& operator=(Section&& section) = default;

    /**
     * @brief Finds and returns or inserts
     * @details Tries to find element with the comparator in the m_elements vector. If found,
     * returns l-value reference to it. If not, calls insert() with construct() to construct and
     * insert object in m_elements
     * @param line key, name etc. of the searched value
     * @return reference on returnal value of object
     * @see find()
     * @see insert()
     * @see construct()
     */
    std::string& operator[](std::string line);

    /**
     * @brief Finds and returns const l-value reference or std::nullopt
     * @param line key, name etc. of the searched value
     * @return l-value reference to found object or std::nullopt if not found
     * @see find()
     */
    boost::optional<const std::string&> operator[](std::string line) const;


    /// Empty destructor
    ~Section() = default;
};


/**
 * @brief Overloaded operator << to output section content in std::ostream
 * @param os std::ostream l-value reference
 * @param section section const l-value reference
 * @return std::ostream l-value reference
 */
// std::ostream& operator<<(std::ostream& os, const Section& section);


}  // namespace ES
