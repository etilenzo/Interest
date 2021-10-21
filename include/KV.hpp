/**
 * @file
 * @brief This file contains declaration of KV class
 * @author Evilenzo
 * @version 1.0
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
    std::string m_key = {};

    /// @brief Value
    std::string m_value = {};

    /// Empty constructor
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
    bool operator==(const std::string& key) const noexcept { return m_key == key; }

    /**
     * @brief Parse key and value from string
     * @details Beautifies string and parses it. Throws exceptions if string is incorrect
     * @param line string to parse
     * @see uncommentLine()
     * @see beautifyPrefix()
     * @see beautifySuffix()
     */
    void fromString(std::string line) {
        delComment(line);

        if (!line.empty()) {
            std::size_t equal_pos = line.find(EQUAL_SYMBOL);

            if (equal_pos != std::string::npos) {
                std::string&& key = line.substr(0, equal_pos);
                prefixDelSpaces(key);
                suffixDelSpaces(key);

                if (!key.empty()) {
                    m_key = std::move(key);

                    line.erase(0, equal_pos + 1);
                    prefixDelSpaces(line);
                    suffixDelBreakers(line);

                    m_value = std::move(line);
                }
            }
        }
    }

    /**
     * @brief Determine if class is empty
     * @return true if value is empty
     */
    bool empty() const noexcept { return m_value.empty(); }

    /**
     * @brief Determine if class is wrong
     * @return true if key and value are empty
     */
    bool wrong() const noexcept { return m_key.empty() && m_value.empty(); }

    friend std::ostream& operator<<(std::ostream& os, const KV& kv) {
        os << kv.m_key << EQUAL_SYMBOL << kv.m_value << std::endl;
        return os;
    }

    /// @brief Default destructor
    ~KV() = default;
};


}  // namespace ES
