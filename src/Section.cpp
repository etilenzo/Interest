/**
 * @file
 * @brief This file contains definitions of Section class
 * @author Evilenzo
 * @version 0.1
 */

#include "Section.hpp"

namespace ES {


Section::Section(std::string name, std::vector<KV> options) noexcept : Container(name, options) {}

Section::Section(const Section& section) noexcept : Container(section) {}

Section::Section(Section&& section) noexcept : Container(section) {}

bool Section::comparator(const KV& i, std::string line) const noexcept { return i.m_key == line; }

KV Section::construct(std::string line) { return KV(std::move(line), EMPTY_STRING); }


/*std::ostream& operator<<(std::ostream& os, const Section& section) {
    os << std::accumulate(section.m_options.begin(), section.m_options.end(),
                          OPENING_BRACKET + section.m_name + CLOSING_BRACKET,
                          [](const std::string& a, const KV& b) {
                              return a + LINE_BREAKER + b.m_key + EQUAL_SYMBOL + b.m_value;
                          });
    return os;
}*/


}  // namespace ES
