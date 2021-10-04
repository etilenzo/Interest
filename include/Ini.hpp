/**
 * @file
 * @brief This file contains declaration of Ini class
 * @author Evilenzo
 * @version 0.1
 */

#pragma once

#include <fstream>
#include <optional>

#include "Section.hpp"

namespace ES {


enum Code {
    BROKEN_INPUT_STREAM,    // Input stream is broken
    MISSING_FIRST_SECTION,  // First section is missing
    WRONG_STRING
};

struct Error {
    Error(Code _code, std::size_t _line) : code(_code), line(_line) {}

    Code code;
    std::size_t line;
};

/// @brief Ini container class
class Ini {
public:
    /// @brief Sections vector
    std::vector<Section> m_sections;

    /// @brief Empty constructor
    Ini();

    /**
     * @brief Create Ini container from input stream
     * @param is input stream l-value reference
     */
    Ini(std::istream& is);

    /**
     * @brief Copy constructor
     * @param ini const l-value reference to another class
     */
    Ini(const Ini& ini);

    /**
     * @brief Move constructor
     * @param ini r-value reference to another class
     */
    Ini(Ini&& ini);

    /**
     * @brief Copy assignment operator
     * @param ini const l-value reference to another class
     * @return *this
     */
    Ini& operator=(const Ini& ini);

    /**
     * @brief Move assignment operator
     * @param ini r-value reference to another class
     * @return *this
     */
    Ini& operator=(Ini&& ini);

    /**
     * @brief Operator [] for the class
     * @details Tries to find Section struct with the given name in sections vector. If found,
     * returns l-value reference to it. If not, calls insert()
     * @param name name of the searched struct
     * @return l-value reference to value of found or created Section struct
     */
    Section& operator[](const std::string& name);

    /**
     * @brief Operator [] for the class
     * @details Tries to find Section struct with the given name in sections vector. If found,
     * returns l-value reference to it. If not, calls insert()
     * @param name name of the searched struct
     * @return l-value reference to value of found or created Section struct
     */
    Section& operator[](std::string&& name);

    /**
     * @brief Parse Ini from input stream
     * @details Parse std::istream line by line beautifiing every string. Throws exceptions if
     * stream contains wrong ini formatting
     * @param is std::istream l-value reference
     */
    std::optional<Error> parseFromStream(std::istream& is);

    /**
     * @brief Dump Ini to output stream
     * @details Writes Ini contents to std::ostream with standard ini formatting
     * @param os std::ostream l-value reference
     * @see uncommentLine()
     * @see beautifyPrefix()
     * @see beautifySuffix()
     * @see parceBrackets()
     */
    void dumpToStream(std::ostream& os) const;

    /**
     * @brief Remove empty Section entries
     */
    void removeEmpty();

    /**
     * @brief Clear container
     */
    void clear();

    /**
     * @brief Operator << for std::ostream
     * @details Same as dumpToStream() but nice
     * @param os std::ostream l-value reference
     * @param container Ini container const reference
     * @return std::ostream l-value reference
     */
    friend std::ostream& operator<<(std::ostream& os, const Ini& container);

    /// Empty destructor
    ~Ini();

private:
    template <typename T>
    Section& find(T name);

    template <typename T>
    Section& insert(T name);
};


}  // namespace ES
