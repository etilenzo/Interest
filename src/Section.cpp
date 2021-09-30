#include "Section.hpp"

namespace ES {


/////////////////////////////////////////////////////////////////////


void uncommentLine(std::string& line) {
    std::size_t comment_pos = line.find_first_of(COMMENT_SYMBOLS);

    if (comment_pos != std::string::npos) line.erase(comment_pos);
}

std::string beautifyPrefix(std::string_view line) {
    while (line.starts_with(CARRIAGE_RETURN) || line.starts_with(LINE_BREAKER) ||
           line.starts_with(SPACE_SYMBOL)) {
        line.remove_prefix(1);
    }

    return std::string(line);
}

std::string beautifySuffix(std::string_view line) {
    while (line.ends_with(CARRIAGE_RETURN) || line.ends_with(LINE_BREAKER) ||
           line.ends_with(SPACE_SYMBOL)) {
        line.remove_suffix(1);
    }

    return std::string(line);
}

std::string parseBrackets(std::string_view line) {
    std::size_t opening_bracket_pos = line.find(OPENING_BRACKET);
    std::size_t closing_bracket_pos = line.find(CLOSING_BRACKET);

    if (opening_bracket_pos != std::string::npos) {
        if (closing_bracket_pos != std::string::npos) {
            return std::string(line.substr(opening_bracket_pos + 1, closing_bracket_pos - 1));
        } else {
            throw std::runtime_error("Missing closing bracket");
        }
    } else {
        throw std::runtime_error("Missing opening bracket");
    }
}


/////////////////////////////////////////////////////////////////////


KV::KV() {}

KV::KV(const std::string_view key, const std::string_view value) : m_key(key), m_value(value) {}

// KV::KV(std::string_view line) { fromString(line); }

KV::KV(const KV& kv) {
    m_key = kv.m_key;
    m_value = kv.m_value;
}

KV& KV::operator=(const KV& kv) {
    if (this == &kv) return *this;

    m_key = kv.m_key;
    m_value = kv.m_value;

    return *this;
}

/*void KV::fromString(std::string_view line) {
    std::string temp = beautifySuffix(uncommentLine(line));

    if (!temp.empty()) {
        std::size_t equal_pos = temp.find(EQUAL_SYMBOL);

        if (equal_pos != std::string::npos) {
            std::string _key = beautifySuffix(temp.substr(0, equal_pos));

            if (!_key.empty()) {
                m_key = _key;
                m_value = beautifyPrefix(temp.substr(equal_pos + 1, line.length() - 1));
            } else {
                throw std::runtime_error("Incorrect line. Key must not be empty");
            }
        } else {
            throw std::runtime_error("Incorrect line. Missing '=' symbol");
        }
    } else {
        throw std::runtime_error("Incorrect line. Beautifiers returned empty string");
    }
}

KV::~KV() {}


/////////////////////////////////////////////////////////////////////


Section::Section() {}

Section::Section(std::string_view _name, std::vector<KV> _options)
    : name(_name), options(_options) {}

Section::Section(const Section& section) {
    name = section.name;
    options = section.options;
}

Section& Section::operator=(const Section& section) {
    if (this == &section) return *this;

    name = section.name;
    options = section.options;

    return *this;
}

std::string& Section::insert(std::string_view key) {
    if (!key.empty()) {
        KV temp(key, EMPTY_STRING);
        options.push_back(temp);
        return options.back().m_value;
    } else {
        throw std::runtime_error("Empty key");
    }
}

std::string& Section::operator[](const std::string_view key) {
    if (!options.empty()) {
        auto temp = std::find_if(options.begin(), options.end(),
                                 [key](const KV& i) { return i.m_key == key; });
        return temp->m_key == key ? temp->m_value : insert(key);
    } else {
        return insert(key);
    }
}

Section::~Section() {}

std::ostream& operator<<(std::ostream& os, const Section& section) {
    os << std::accumulate(section.options.begin(), section.options.end(),
                          OPENING_BRACKET + section.name + CLOSING_BRACKET,
                          [](const std::string& a, const KV& b) {
                              return a + LINE_BREAKER + b.m_key + EQUAL_SYMBOL + b.m_value;
                          });
    return os;
}*/


/////////////////////////////////////////////////////////////////////


}  // namespace ES
