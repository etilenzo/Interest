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
struct KV {
public:
    /// @brief Key
    std::string m_key;

    /// @brief Value
    std::string m_value;

    /// @brief Empty constructor
    KV();

    /**
     *  @brief Create struct with param initialization
     *  @param key m_key
     *  @param value m_value
     */
    KV(const std::string& key, const std::string& value);

    /**
     *  @brief Create struct with param initialization
     *  @param key m_key
     *  @param value m_value
     */
    KV(std::string&& key, std::string&& value);

    /**
     *  @brief Create struct from string
     *  @param line line to parse
     *  @see fromString()
     */
    KV(const std::string& line);

    /**
     *  @brief Create struct from string
     *  @param line line to parse
     *  @see fromString()
     */
    KV(std::string&& line);

    /**
     * @brief Copy constructor
     * @param kv const l-value reference to another struct
     */
    KV(const KV& kv);

    /**
     * @brief Move constructor
     * @param kv r-value reference to another struct
     */
    KV(KV&& kv);

    /**
     * @brief Copy assignment operator
     * @param kv const l-value reference to another struct
     * @return *this
     */
    KV& operator=(const KV& kv);

    /**
     * @brief Move assignment operator
     * @param kv r-value reference to another struct
     * @return *this
     */
    KV& operator=(KV&& kv);

    /**
     * @brief Parse key and value from string
     * @details Beautifies string and parses it. Throws exceptions if string is incorrect
     * @param line string to parse
     * @see uncommentLine()
     * @see beautifyPrefix()
     * @see beautifySuffix()
     */
    template <typename T>
    void fromString(T line);

    /// @brief Empty destructor
    ~KV();
};


}  // namespace ES
