/**
 * @file
 * @brief This file contains declaration Section class
 * @author Evilenzo
 * @version 0.1
 */

#pragma once

#include <algorithm>
#include <numeric>
#include <memory>
#include <vector>

#include "KV.hpp"

namespace ES {


/// @brief Ini section struct
class Section {
    /// @brief Name
    std::string m_name;

    /// @brief KV structs vector
    std::vector<KV> m_options;

    /// @brief Empty constructor
    Section();

    /**
     *  @brief Create struct with param initialization
     *  @param name m_name
     *  @param options KV vector
     */
    Section(const std::string& name, const std::vector<KV>& options);

    /**
     *  @brief Create struct with param initialization
     *  @param name m_name
     *  @param options KV vector
     */
    Section(std::string&& name, std::vector<KV>&& options);

    /**
     * @brief Copy constructor
     * @param section const l-value reference to another struct
     */
    Section(const Section& section);

    /**
     * @brief Move constructor
     * @param section r-value reference to another struct
     */
    Section(Section&& section);

    /**
     * @brief Copy assignment operator
     * @param section const l-value reference to another struct
     * @return *this
     */
    Section& operator=(const Section& section);

    /**
     * @brief Move assignment operator
     * @param section r-value reference to another struct
     * @return *this
     */
    Section& operator=(Section&& section);

    /**
     * @brief Operator [] for the struct
     * @details Calls find()
     * @param key key of the searched struct
     * @return l-value reference to value of found or created KV struct
     * @see find()
     */
    std::string& operator[](const std::string& key);

    /**
     * @brief Operator [] for the struct
     * @details Calls find()
     * @param key key of the searched struct
     * @return l-value reference to value of found or created KV struct
     * @see find()
     */
    std::string& operator[](std::string&& key);

    /**
     * @brief Finds KV or creates one
     * @details Tries to find KV struct with the given key in options vector. If found, returns
     * l-value reference to the value string of this KV struct. If not, calls insert()
     * @param key key of the searched struct
     * @return l-value reference to value of found or created KV struct
     */
    template <typename T>
    std::string& find(T key);

    /**
     * @brief Insert KV with given key
     * @details Creates KV struct with given key and empty value then returns l-value reference to
     * value string. Throws exception if key param is empty
     * @param key key
     * @return l-value reference to value of created KV struct
     */
    template <typename T>
    std::string& insert(T key);

    /**
     * @brief Clear container
     */
    void clear();

    /// Empty destructor
    ~Section();
};


/**
 * @brief Overloaded operator << to output section content in std::ostream
 * @param os std::ostream l-value reference
 * @param section section const l-value reference
 * @return std::ostream l-value reference
 */
std::ostream& operator<<(std::ostream& os, const Section& section);


}  // namespace ES
