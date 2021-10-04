/**
 * @file
 * @brief This file contains definition of KV class
 * @author Evilenzo
 * @version 0.1
 */

#include "KV.hpp"

namespace ES {


KV::KV() {}

KV::KV(const std::string& key, const std::string& value) : m_key(key), m_value(value) {}

KV::KV(std::string&& key, std::string&& value) : m_key(std::move(key)), m_value(std::move(value)) {}

KV::KV(const std::string& line) { fromString<std::string>(line); }

KV::KV(std::string&& line) { fromString<std::string&&>(std::move(line)); }

KV::KV(const KV& kv) {
    m_key = kv.m_key;
    m_value = kv.m_value;
}

KV::KV(KV&& kv) : m_key(std::move(kv.m_key)), m_value(std::move(kv.m_value)) {
    kv.m_key.clear();
    kv.m_value.clear();
}

KV& KV::operator=(const KV& kv) {
    if (this == &kv) return *this;

    m_key = kv.m_key;
    m_value = kv.m_value;

    return *this;
}

KV& KV::operator=(KV&& kv) {
    if (this == &kv) return *this;

    m_key = std::move(kv.m_key);
    m_value = std::move(kv.m_value);

    kv.m_key.clear();
    kv.m_value.clear();

    return *this;
}

template <typename T>
void KV::fromString(T line) {
    uncommentLine(line);

    if (!line.empty()) {
        std::size_t equal_pos = line.find(EQUAL_SYMBOL);

        if (equal_pos != std::string::npos) {
            std::string&& key = line.substr(0, equal_pos);
            beautifyPrefix(key);
            beautifySuffix(key);

            if (!key.empty()) {
                m_key = std::move(key);

                line.erase(0, equal_pos + 1);
                beautifyPrefix(line);
                beautifySuffix(line);

                m_value = std::move(line);

                return;
            }
        }
    }
}

bool KV::empty() {
    if (m_key.empty() && m_value.empty())
        return true;
    else
        return false;
}

KV::~KV() {}


}  // namespace ES
