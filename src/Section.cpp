/**
 * @file
 * @brief This file contains definitions of Section class
 * @author Evilenzo
 * @version 0.2
 */

#include "Section.hpp"

namespace ES {

std::string& Section::operator[](std::string key) { return findOrInsert(std::move(key)).m_value; }

boost::optional<const std::string&> Section::operator[](std::string key) const {
    return {find(std::move(key))->m_value};
}

KV Section::construct(std::string key) { return {std::move(key), EMPTY_STRING}; }

std::ostream& operator<<(std::ostream& os, const Section& section) {
    os << OPENING_BRACKET << section.m_name << CLOSING_BRACKET << std::endl;

    for (const auto& i : *section.m_elements) {
        os << i;
    }

    return os;
}


}  // namespace ES
