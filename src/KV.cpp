/**
 * @file
 * @brief This file contains definitions of KV class
 * @author Evilenzo
 * @version 0.1
 */

#include "KV.hpp"

namespace ES {


KV& KV::operator=(const KV& kv) {
    if (this == &kv) {
        return *this;
    }

    m_key = kv.m_key;
    m_value = kv.m_value;

    return *this;
}

KV& KV::operator=(KV&& kv) noexcept {
    if (this == &kv) {
        return *this;
    }

    m_key = std::move(kv.m_key);
    m_value = std::move(kv.m_value);

    kv.m_key.clear();
    kv.m_value.clear();

    return *this;
}

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

                return;
            }
        }
    }
}

bool KV::empty() const noexcept { return m_key.empty() && m_value.empty(); }


}  // namespace ES
