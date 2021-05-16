/**
 * @file
 * @brief This file contains declarations of KV and Section structs plus some util functions and
 * symbol constants
 * @author Evilenzo
 * @version 0.1
 */

#pragma once

#include <iostream>
#include <algorithm>
#include <numeric>
#include <string>
#include <string_view>
#include <vector>


namespace ES {


/////////////////////////////////////////////////////////////////////


inline constexpr char OPENING_BRACKET = '[';
inline constexpr char CLOSING_BRACKET = ']';
inline constexpr char EQUAL_SYMBOL = '=';
inline constexpr char LINE_BREAKER = '\n';
inline constexpr char CARRIAGE_RETURN = '\r';
inline constexpr char SPACE_SYMBOL = ' ';
inline constexpr char COMMENT_SYMBOLS[3] = "#;";
inline constexpr char EMPTY_STRING[1] = "";


/////////////////////////////////////////////////////////////////////


/// @brief Remove everything after # or ! from  the line
std::string uncommentLine(std::string_view line);

/// @brief Remove line breaker, carriage return and space symbols from the line prefix
std::string beautifyPrefix(std::string_view line);

/// @brief Remove line breaker, carriage return and space symbols from the line suffix
std::string beautifySuffix(std::string_view line);


/////////////////////////////////////////////////////////////////////


/// @brief Key-Value struct
struct KV {
    /// @brief Empty constructor
    KV();

    /**
     *  @brief Create struct with param initialization
     *  @param _key key
     *  @param _value value
     */
    KV(std::string_view _key, std::string_view _value);

    /**
     *  @brief Create struct from string
     *  @param line line to parse
     *  @see fromString()
     */
    explicit KV(std::string_view line);

    /**
     * @brief Copy constructor
     * @param kv l-value reference to another struct
     */
    KV(const KV& kv);

    /**
     * @brief Copy operator =
     * @param kv const l-value reference to another struct
     * @return *this
     */
    KV& operator=(const KV& kv);

    /// @brief Key
    std::string key;

    /// @brief Value
    std::string value;


    /**
     * @brief Parse key and value from string
     * @details Beautifies string and parses it. Throws exceptions if string is incorrect
     * @param line string to parse
     * @see uncommentLine()
     * @see beautifyPrefix()
     * @see beautifySuffix()
     */
    void fromString(std::string_view line);

    /// @brief Empty destructor
    ~KV();
};


/////////////////////////////////////////////////////////////////////


/// @brief Ini section struct
struct Section {
    /// @brief Empty constructor
    Section();

    /**
     *  @brief Create struct with param initialization
     *  @param _name name
     *  @param _options KV vector
     */
    Section(std::string_view _name, std::vector<KV> _options);

    /**
     * @brief Copy constructor
     * @param section l-value reference to another struct
     */
    Section(const Section& section);

    /**
     * @brief Copy operator =
     * @param section const l-value reference to another struct
     * @return *this
     */
    Section& operator=(const Section& section);

    /// @brief Name
    std::string name;

    /// @brief KV structs vector
    std::vector<KV> options;

    /**
     * @brief Insert KV with given key
     * @details Creates KV struct with given key and empty value then returns l-value reference to
     * value string. Throws exception if key param is empty
     * @param key key
     * @return l-value reference to value of created KV struct
     */
    std::string& insert(std::string_view key);

    /**
     * @brief Operator [] for the struct
     * @details Tries to find KV struct with given key in options vector. If found, returns l-value
     * reference to the value string of this KV struct. If not, calls insert()
     * @param key key of the searched struct
     * @return l-value reference to value of found or created KV struct
     */
    std::string& operator[](const std::string_view key);

    /// Empty destructor
    ~Section();
};

/**
 * @brief Overloaded operator << to output section content in std::ostream
 * @param os std::ostream l-value reference
 * @param section section l-value reference
 * @return std::ostream l-value reference
 */
std::ostream& operator<<(std::ostream& os, const Section& section);

}  // namespace ES
