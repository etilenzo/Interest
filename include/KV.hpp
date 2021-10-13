/**
 * @file
 * @brief This file contains declaration of KV class
 * @author Evilenzo
 * @version 0.2
 */

#pragma once

#include <iostream>

#include "Utils.hpp"

namespace ES {

class Section;

/// @brief Key-Value struct
class KV {
public:
    /// @brief Key
    std::string m_key;

    /// @brief Value
    std::string m_value;

    /// @brief Empty constructor
    KV() = default;

    /**
     *  @brief Create struct with param initialization
     *  @param key
     *  @param value
     */
    KV(std::string key, std::string value) : m_key(std::move(key)), m_value(std::move(value)) {}

    /**
     *  @brief Create struct from string
     *  @param line line to parse
     *  @see fromString()
     */
    KV(std::string line) { fromString(std::move(line)); }

    /// @brief Copy constructor
    KV(const KV& kv) = default;

    /// @brief Move constructor
    KV(KV&& kv) noexcept = default;

    /// @brief Copy assignment operator
    KV& operator=(const KV& kv) = default;

    /// @brief Move assignment operator
    KV& operator=(KV&& kv) noexcept = default;

    /**
     * @brief Equality operator for find algorithm
     * @param key key to check
     * @return m_key == key
     */
    bool operator==(const std::string& key) const noexcept;

    /**
     * @brief Parse key and value from string
     * @details Beautifies string and parses it. Throws exceptions if string is incorrect
     * @param line string to parse
     * @see uncommentLine()
     * @see beautifyPrefix()
     * @see beautifySuffix()
     */
    void fromString(std::string line);

    /**
     * @brief Determine if class is empty
     * @return true if key and value are empty
     */
    bool empty() const noexcept;

    friend std::ostream& operator<<(std::ostream& os, const KV& kv);

    /// @brief Default destructor
    ~KV() = default;
};


}  // namespace ES
