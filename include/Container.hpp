/**
 * @file
 * @brief This file contains declaration of abstract template Container class
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
    std::vector<T> m_elements;

    /// @brief Empty constructor
    Container() = default;

    /**
     * @brief Copy constructor
     * @param container const l-value reference to another instance
     */
    Container(const Container& container);

    /**
     * @brief Move constructor
     * @param container r-value reference to another instance
     */
    Container(Container&& container) noexcept;

    /**
     * @brief Copy assignment operator
     * @param container const l-value reference to another instance
     * @return *this
     */
    // Container& operator=(const Container& container);

    /**
     * @brief Move assignment operator
     * @param container r-value reference to another instance
     * @return *this
     */
    // Container& operator=(Container&& container) noexcept;

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
    virtual void clear();

    /**
     * @brief Check on emptyness
     */
    virtual void empty();

    /**
     * @brief Operator << for std::ostream
     * @details Same as dumpToStream() but nice
     * @param os std::ostream l-value reference
     * @param container container container const reference
     * @return std::ostream l-value reference
     */
    // friend std::ostream& operator<<(std::ostream& os, const Container& container);

    /// Empty destructor
    virtual ~Container() = default;
};
