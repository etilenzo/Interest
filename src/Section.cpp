/**
 * @file
 * @brief This file contains definition of Section class
 * @author Evilenzo
 * @version 0.1
 */

#include "Section.hpp"

namespace ES {


Section::Section() {}

Section::Section(const std::string& name, const std::vector<KV>& options)
    : m_name(name), m_options(options) {}

Section::Section(std::string&& name, std::vector<KV>&& options)
    : m_name(std::move(name)), m_options(std::move(options)) {}

Section::Section(const Section& section) {
    m_name = section.m_name;
    m_options = section.m_options;
}

Section::Section(Section&& section)
    : m_name(std::move(section.m_name)), m_options(std::move(section.m_options)) {
    section.m_name.clear();
    section.m_options.clear();
}

Section& Section::operator=(const Section& section) {
    if (this == &section) return *this;

    m_name = section.m_name;
    m_options = section.m_options;

    return *this;
}

Section& Section::operator=(Section&& section) {
    if (this == &section) return *this;

    m_name = std::move(section.m_name);
    m_options = std::move(section.m_options);
    section.m_name.clear();
    section.m_options.clear();

    return *this;
}

std::string& Section::operator[](const std::string& key) { return find(key); }

std::string& Section::operator[](std::string&& key) { return find(key); }

void Section::clear() { m_options.clear(); }

template <typename T>
std::string& Section::find(T key) {
    if (!m_options.empty()) {
        auto temp = std::find_if(m_options.begin(), m_options.end(),
                                 [key](const KV& i) { return i.m_key == key; });
        return temp != m_options.end() ? temp->m_value : insert(key);
    } else
        return insert(key);
}

template <typename T>
std::string& Section::insert(T key) {
    if (!key.empty()) {
        m_options.push_back(KV(key, EMPTY_STRING));
        return m_options.back().m_value;
    } else
        throw std::runtime_error("Empty key");
}

Section::~Section() {}


std::ostream& operator<<(std::ostream& os, const Section& section) {
    os << std::accumulate(section.m_options.begin(), section.m_options.end(),
                          OPENING_BRACKET + section.m_name + CLOSING_BRACKET,
                          [](const std::string& a, const KV& b) {
                              return a + LINE_BREAKER + b.m_key + EQUAL_SYMBOL + b.m_value;
                          });
    return os;
}


}  // namespace ES
