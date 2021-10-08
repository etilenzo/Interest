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
inline constexpr char QUOTATION_MARKS[2] = {'\'', '"'};
inline constexpr char EMPTY_STRING[1] = "";


/////////////////////////////////////////////////////////////////////


/// @brief Delete everything after # or ! from  the line
void delComment(std::string& line);

/// @brief Delete all quotation marks
void delQuotationMarks(std::string& line);

/// @brief Delete space symbols from the line prefix
void prefixDelSpaces(std::string& line);

/// @brief Delete space symbols from the line suffix
void suffixDelSpaces(std::string& line);

/// @brief Delete line breakers carriage return and space symbols from the line suffix
void suffixDelBreakers(std::string& line);

/// @brief Trim brackets for Section name
void trimBrackets(std::string& line);


}  // namespace ES
