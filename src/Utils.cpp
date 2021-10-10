/**
 * @file
 * @brief This file contains definitions of string beautify functions
 * @author Evilenzo
 * @version 0.1
 */

#include "Utils.hpp"

namespace ES {


void delComment(std::string& line) {
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

void delQuotationMarks(std::string& line) {
    line.erase(std::remove_if(line.begin(), line.end(),
                              [](const char& i) {
                                  return i == QUOTATION_MARKS[0] || i == QUOTATION_MARKS[1];
                              }),
               line.end());
}

void prefixDelSpaces(std::string& line) {
    std::size_t not_space = line.find_first_not_of(SPACE_SYMBOL);

    if (not_space == std::string::npos) {
        line.clear();
    } else if (not_space != 0) {
        line.erase(0, not_space);
    }
}

void suffixDelSpaces(std::string& line) {
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

void suffixDelBreakers(std::string& line) {
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

void trimBrackets(std::string& line) {
    if (line.starts_with(OPENING_BRACKET)) {
        if (line.ends_with(CLOSING_BRACKET)) {
            line = line.substr(1, line.size() - 2);

            return;
        }
    }

    line.clear();
}

}  // namespace ES
