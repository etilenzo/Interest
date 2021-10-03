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
#include <memory>
#include <string>
#include <vector>


namespace ES {


/////////////////////////////////////////////////////////////////////


inline constexpr char OPENING_BRACKET = '[';
inline constexpr char CLOSING_BRACKET = ']';
inline constexpr char EQUAL_SYMBOL = '=';
inline constexpr char LINE_BREAKER = '\n';
inline constexpr char CARRIAGE_RETURN = '\r';
inline constexpr char SPACE_SYMBOL = ' ';
inline constexpr char COMMENT_SYMBOLS[3] = {'#', ';'};
inline constexpr char EMPTY_STRING[1] = "";


/////////////////////////////////////////////////////////////////////


/// @brief Remove everything after # or ! from  the line
void uncommentLine(std::string& line);

/// @brief Remove line breaker, carriage return and space symbols from the line prefix
void beautifyPrefix(std::string& line);

/// @brief Remove line breaker, carriage return and space symbols from the line suffix
void beautifySuffix(std::string& line);

/// @brief Parce brackets for Section name
void parseBrackets(std::string& line);


/////////////////////////////////////////////////////////////////////


/// @brief Key-Value struct
struct KV {
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


/////////////////////////////////////////////////////////////////////


/// @brief Ini section struct
struct Section {
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
