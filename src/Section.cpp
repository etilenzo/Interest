/**
 * @file
 * @brief This file contains definitions of Section class
 * @author Evilenzo
 * @version 0.1
 */

#include "Section.hpp"

namespace ES {

std::string& Section::operator[](std::string key) { return findOrInsert(std::move(key)).m_value; }

boost::optional<const std::string&> Section::operator[](std::string key) const {
    return boost::optional<const std::string&>(find(std::move(key))->m_value);
}

KV Section::construct(std::string key) { return KV(std::move(key), EMPTY_STRING); }

/*std::ostream& operator<<(std::ostream& os, const Section& section) {
    os << std::accumulate(section.m_options.begin(), section.m_options.end(),
                          OPENING_BRACKET + section.m_name + CLOSING_BRACKET,
                          [](const std::string& a, const KV& b) {
                              return a + LINE_BREAKER + b.m_key + EQUAL_SYMBOL + b.m_value;
                          });
    return os;
}*/


}  // namespace ES
