/**
 * @file
 * @brief This file contains declarations of string util functions and symbol constants
 * @author Evilenzo
 * @version 1.0
 */

#pragma once

#include <iostream>
#include <string>

namespace ES {


inline constexpr char OPENING_BRACKET = '[';
inline constexpr char CLOSING_BRACKET = ']';
inline constexpr char EQUAL_SYMBOL = '=';
inline constexpr char LINE_BREAKER = '\n';
inline constexpr char CARRIAGE_RETURN = '\r';
inline constexpr char SPACE_SYMBOL = ' ';
inline constexpr char COMMENT_SYMBOLS[2] = {'#', ';'};
inline constexpr char QUOTATION_MARKS[2] = {'\'', '"'};
inline constexpr char EMPTY_STRING[1] = "";


/////////////////////////////////////////////////////////////////////


/// @brief Delete everything after # or ! from  the line
inline auto delComment(std::string& line) -> void {
    if (!line.empty()) {
        std::size_t comment_pos = std::string::npos;

        for (std::size_t i = 0, j = line.size() - 1; i <= j; ++i, --j) {
            if (line[i] == COMMENT_SYMBOLS[0] || line[i] == COMMENT_SYMBOLS[1]) {
                comment_pos = i;
                break;
            }

            if (line[j] == COMMENT_SYMBOLS[0] || line[j] == COMMENT_SYMBOLS[1]) {
                comment_pos = j;
            }
        }

        if (comment_pos != std::string::npos) {
            line.erase(comment_pos);
        }
    }
}

/// @brief Delete all quotation marks
inline auto delQuotationMarks(std::string& line) -> void {
    line.erase(std::remove_if(line.begin(), line.end(),
                              [](const char& i) {
                                  return i == QUOTATION_MARKS[0] || i == QUOTATION_MARKS[1];
                              }),
               line.end());
}


/// @brief Delete space symbols from the line prefix
inline auto prefixDelSpaces(std::string& line) -> void {
    std::size_t not_space = line.find_first_not_of(SPACE_SYMBOL);

    if (not_space == std::string::npos) {
        line.clear();
    } else if (not_space != 0) {
        line.erase(0, not_space);
    }
}

/// @brief Delete space symbols from the line suffix
inline auto suffixDelSpaces(std::string& line) -> void {
    std::string::reverse_iterator iter = line.rbegin();
    bool cycled = false;

    while (iter != line.rend()) {
        if (*iter == SPACE_SYMBOL) {
            ++iter;
            cycled = true;
        } else {
            break;
        }
    }

    if (cycled) {
        line.erase(iter.base(), line.end());
    }
}

/// @brief Delete line breakers carriage return and space symbols from the line suffix
inline auto suffixDelBreakers(std::string& line) -> void {
    std::string::reverse_iterator iter = line.rbegin();
    bool cycled = false;

    while (iter != line.rend()) {
        if (*iter == CARRIAGE_RETURN || *iter == LINE_BREAKER || *iter == SPACE_SYMBOL) {
            ++iter;
            cycled = true;
        } else {
            break;
        }
    }

    if (cycled) {
        line.erase(iter.base(), line.end());
    }
}

/// @brief Trim brackets for Section name
inline auto trimBrackets(std::string& line) -> void {
    if (line.starts_with(OPENING_BRACKET)) {
        if (line.ends_with(CLOSING_BRACKET)) {
            line = line.substr(1, line.size() - 2);

            return;
        }
    }

    line.clear();
}


}  // namespace ES
