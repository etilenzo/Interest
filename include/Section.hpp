/**
 * @file
 * @brief This file contains declaration Section class
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
    /// @brief Empty constructor
    Section() = default;

    /**
     * @brief Container with param initialization
     * @param name m_name
     * @param options m_options
     */
    Section(std::string name, std::vector<KV> options) noexcept : Container<KV>(name, options) {}

    /**
     * @brief Copy constructor
     * @param container const l-value reference to another instance
     */
    Container(const Container& container) noexcept
        : m_name(container.m_name), m_elements(container.m_elements) {}

    /**
     * @brief Move constructor
     * @param container r-value reference to another instance
     */
    Container(Container&& container) noexcept
        : m_name(std::move(container.m_name)), m_elements(std::move(container.m_elements)) {
        container.m_name.clear();
        container.m_elements.reset();
    }

    /**
     * @brief Operator [] for the class
     * @details Calls find()
     * @param key key of the searched class
     * @return l-value reference to value of found or created KV class
     * @see find()
     */
    std::string& operator[](const std::string& key);

    /**
     * @brief Operator [] for the class
     * @details Calls find()
     * @param key key of the searched class
     * @return l-value reference to value of found or created KV class
     * @see find()
     */
    std::string& operator[](std::string&& key);

    /**
     * @brief Clear container
     */
    void clear();

    /// Empty destructor
    ~Section() = default;

private:
    /**
     * @brief Finds KV or creates one
     * @details Tries to find KV class with the given key in options vector. If found, returns
     * l-value reference to the value string of this KV class. If not, calls insert()
     * @param key key of the searched class
     * @return l-value reference to value of found or created KV class
     */
    template <typename T>
    std::string& find(T key);

    /**
     * @brief Insert KV with given key
     * @details Creates KV class with given key and empty value then returns l-value reference to
     * value string
     * @param key key
     * @return l-value reference to value of created KV class
     */
    template <typename T>
    std::string& insert(T key);
};


/**
 * @brief Overloaded operator << to output section content in std::ostream
 * @param os std::ostream l-value reference
 * @param section section const l-value reference
 * @return std::ostream l-value reference
 */
std::ostream& operator<<(std::ostream& os, const Section& section);


}  // namespace ES
