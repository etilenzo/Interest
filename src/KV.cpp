/**
 * @file
 * @brief This file contains definitions of KV class
 * @author Evilenzo
 * @version 0.1
 */

#include "KV.hpp"

namespace ES {


bool KV::operator==(const std::string& key) const noexcept { return m_key == key; }

void KV::fromString(std::string line) {
    delComment(line);

    if (!line.empty()) {
        std::size_t equal_pos = line.find(EQUAL_SYMBOL);

        if (equal_pos != std::string::npos) {
            std::string&& key = line.substr(0, equal_pos);
            prefixDelSpaces(key);
            suffixDelSpaces(key);

            if (!key.empty()) {
                m_key = std::move(key);

                line.erase(0, equal_pos + 1);
                prefixDelSpaces(line);
                suffixDelBreakers(line);

                m_value = std::move(line);
            }
        }
    }
}

bool KV::empty() const noexcept { return m_key.empty() && m_value.empty(); }

std::ostream& operator<<(std::ostream& os, const KV& kv) {
    os << kv.m_key << EQUAL_SYMBOL << kv.m_value << std::endl;
    return os;
}


}  // namespace ES
