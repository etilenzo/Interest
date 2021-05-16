#include "Section.hpp"

namespace ES {


/////////////////////////////////////////////////////////////////////


std::string uncommentLine(std::string_view line) {
    std::size_t comment_pos = line.find_first_of(COMMENT_SYMBOLS);

    if (comment_pos != std::string::npos) {
        line = line.substr(0, comment_pos);
    }

    return std::string(line);
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


/////////////////////////////////////////////////////////////////////


KV::KV() {}

KV::KV(std::string_view _key, std::string_view _value) : key(_key), value(_value) {}

KV::KV(std::string_view line) { fromString(line); }

KV::KV(const KV& kv) {
    key = kv.key;
    value = kv.value;
}

KV& KV::operator=(const KV& kv) {
    if (this == &kv) return *this;

    key = kv.key;
    value = kv.value;

    return *this;
}

void KV::fromString(std::string_view line) {
    std::string temp = beautifySuffix(uncommentLine(line));

    if (!temp.empty()) {
        std::size_t equal_pos = temp.find(EQUAL_SYMBOL);

        if (equal_pos != std::string::npos) {
            std::string _key = beautifySuffix(temp.substr(0, equal_pos));

            if (!_key.empty()) {
                key = _key;
                value = beautifyPrefix(temp.substr(equal_pos + 1, line.length() - 1));
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
        return options.back().value;
    } else {
        throw std::runtime_error("Empty key");
    }
}

std::string& Section::operator[](const std::string_view key) {
    if (!options.empty()) {
        auto temp = std::find_if(options.begin(), options.end(),
                                 [key](const KV& i) { return i.key == key; });
        return temp->key == key ? temp->value : insert(key);
    } else {
        return insert(key);
    }
}

Section::~Section() {}

std::ostream& operator<<(std::ostream& os, const Section& sect) {
    os << std::accumulate(sect.options.begin(), sect.options.end(),
                          OPENING_BRACKET + sect.name + CLOSING_BRACKET,
                          [](const std::string& a, const KV& b) {
                              return a + LINE_BREAKER + b.key + EQUAL_SYMBOL + b.value;
                          });
    return os;
}


/////////////////////////////////////////////////////////////////////


}  // namespace ES
