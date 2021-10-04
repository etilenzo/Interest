/**
 * @file
 * @brief This file contains declarations of string beautify functions and symbol constants
 * @author Evilenzo
 * @version 0.1
 */

#pragma once

#include <iostream>
#include <string>
#include <variant>

namespace ES {


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
void removeComment(std::string& line);

/// @brief Remove space symbols from the line prefix
void beautifyPrefix(std::string& line);

/// @brief Remove space symbols from the line suffix
void beautifySuffix(std::string& line);

/// @brief Remove line breaker, carriage return and space symbols from the line suffix
void removeBreakers(std::string& line);

/// @brief Parce brackets for Section name
void trimBrackets(std::string& line);


}  // namespace ES
