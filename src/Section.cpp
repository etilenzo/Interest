/**
 * @file
 * @brief This file contains definitions of Section class
 * @author Evilenzo
 * @version 0.1
 */

#include "Section.hpp"

namespace ES {

std::string& Section::operator[](std::string line) {
    boost::optional<KV&> element = find(line);

    if (element) {
        return element->m_value;
    }

    return insert(KV(std::move(line), EMPTY_STRING)).m_value;
}

boost::optional<const std::string&> Section::operator[](std::string line) const {
    return boost::optional<const std::string&>(find(line));
}

/*std::ostream& operator<<(std::ostream& os, const Section& section) {
    os << std::accumulate(section.m_options.begin(), section.m_options.end(),
                          OPENING_BRACKET + section.m_name + CLOSING_BRACKET,
                          [](const std::string& a, const KV& b) {
                              return a + LINE_BREAKER + b.m_key + EQUAL_SYMBOL + b.m_value;
                          });
    return os;
}*/


}  // namespace ES
