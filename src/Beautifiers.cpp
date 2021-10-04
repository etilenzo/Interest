/**
 * @file
 * @brief This file contains definitions of string beautify functions
 * @author Evilenzo
 * @version 0.1
 */

#include "Beautifiers.hpp"

namespace ES {


void removeComment(std::string& line) {
    std::size_t comment_pos = line.find_first_of(COMMENT_SYMBOLS);

    if (comment_pos != std::string::npos) line.erase(comment_pos);
}

void beautifyPrefix(std::string& line) {
    std::string::iterator iter = line.begin();
    bool cycled = false;

    while (iter != line.end()) {
        if (*iter == SPACE_SYMBOL) {
            ++iter;
            cycled = true;
        } else
            break;
    }

    if (cycled) line.erase(line.begin(), iter);
}

void beautifySuffix(std::string& line) {
    std::string::reverse_iterator iter = line.rbegin();
    bool cycled = false;

    while (iter != line.rend()) {
        if (*iter == CARRIAGE_RETURN || *iter == LINE_BREAKER || *iter == SPACE_SYMBOL) {
            ++iter;
            cycled = true;
        } else
            break;
    }

    if (cycled) line.erase(iter.base(), line.end());
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
