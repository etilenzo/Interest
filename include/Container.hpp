/**
 * @file
 * @brief This file contains declaration of basic Container class
 * @author Evilenzo
 * @version 0.1
 */

#pragma once

#include <memory>
#include <vector>
#include <string>

template <typename T>
class Container {
public:
    /// @brief Vector of contained elements
    std::vector<T> m_sections;

    /// @brief Empty constructor
    Container() = default;

    /**
     * @brief Copy constructor
     * @param ini const l-value reference to another class
     */
    Container(const Container& container);

    /**
     * @brief Move constructor
     * @param ini r-value reference to another class
     */
    Container(Container&& container) noexcept;

    /**
     * @brief Copy assignment operator
     * @param ini const l-value reference to another class
     * @return *this
     */
    // Ini& operator=(const Ini& ini);

    /**
     * @brief Move assignment operator
     * @param ini r-value reference to another class
     * @return *this
     */
    // Ini& operator=(Ini&& ini) noexcept;

    /**
     * @brief Operator [] for the class
     * @details Tries to find Section struct with the given name in sections vector. If found,
     * returns l-value reference to it. If not, calls insert()
     * @param name name of the searched struct
     * @return l-value reference to value of found or created Section struct
     */
    // Section& operator[](const std::string& name);

    /**
     * @brief Operator [] for the class
     * @details Tries to find Section struct with the given name in sections vector. If found,
     * returns l-value reference to it. If not, calls insert()
     * @param name name of the searched struct
     * @return l-value reference to value of found or created Section struct
     */
    // Section& operator[](std::string&& name);

    /**
     * @brief Remove empty Section entries
     */
    // void removeEmpty();

    /**
     * @brief Clear container
     */
    // void clear();

    /**
     * @brief Operator << for std::ostream
     * @details Same as dumpToStream() but nice
     * @param os std::ostream l-value reference
     * @param container Ini container const reference
     * @return std::ostream l-value reference
     */
    // friend std::ostream& operator<<(std::ostream& os, const Ini& container);

    /// Empty destructor
    ~Container() = default;
};
