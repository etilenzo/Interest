/**
 * @file
 * @brief This file contains declaration of KV class
 * @author Evilenzo
 * @version 0.1
 */

#pragma once

#include "Beautifiers.hpp"

namespace ES {


/// @brief Key-Value struct
class KV {
public:
    /// @brief Key
    std::string m_key;

    /// @brief Value
    std::string m_value;

    /**
     *  @brief Create struct with param initialization
     *  @param key m_key
     *  @param value m_value
     */
    KV(std::string key = "", std::string value = "")
        : m_key(std::move(key)), m_value(std::move(value)) {}

    /**
     *  @brief Create struct from string
     *  @param line line to parse
     *  @see fromString()
     */
    KV(std::string line) { fromString(std::move(line)); }

    /**
     * @brief Copy constructor
     * @param kv const l-value reference to another instance
     */
    KV(const KV& kv) : m_key(kv.m_key), m_value(kv.m_value) {}

    /**
     * @brief Move constructor
     * @param kv r-value reference to another instance
     */
    KV(KV&& kv) noexcept : m_key(std::move(kv.m_key)), m_value(std::move(kv.m_value)) {}

    /**
     * @brief Copy assignment operator
     * @param kv const l-value reference to another instance
     * @return *this
     */
    KV& operator=(const KV& kv);

    /**
     * @brief Move assignment operator
     * @param kv r-value reference to another instance
     * @return *this
     */
    KV& operator=(KV&& kv) noexcept;

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
     * @return true if key is empty
     */
    bool empty() const noexcept;

    /// @brief Default destructor
    ~KV() = default;
};


}  // namespace ES
