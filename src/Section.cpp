#include "Section.hpp"

namespace ES {


/////////////////////////////////////////////////////////////////////


void uncommentLine(std::string& line) {
    std::size_t comment_pos = line.find_first_of(COMMENT_SYMBOLS);

    if (comment_pos != std::string::npos) line.erase(comment_pos);
}

void beautifyPrefix(std::string& line) {
    std::string::iterator iter = line.begin();
    bool cycled = false;

    while (iter != line.end()) {
        if (*iter == CARRIAGE_RETURN || *iter == LINE_BREAKER || *iter == SPACE_SYMBOL) {
            ++iter;
            cycled = true;
        } else
            break;
    }

    if (cycled) line.erase(line.begin(), iter);
}

void beautifySuffix(std::string& line) {
    std::string::reverse_iterator iter = line.rbegin();
    bool cycled = false;

    while (iter != line.rend()) {
        if (*iter == CARRIAGE_RETURN || *iter == LINE_BREAKER || *iter == SPACE_SYMBOL) {
            ++iter;
            cycled = true;
        } else
            break;
    }

    if (cycled) line.erase(iter.base(), line.end());
}

void parseBrackets(std::string& line) {
    // TODO: Изменить это на for
    std::size_t opening_bracket_pos = line.find(OPENING_BRACKET);
    std::size_t closing_bracket_pos = line.find(CLOSING_BRACKET);

    if (opening_bracket_pos != std::string::npos) {
        if (opening_bracket_pos == 0) {
            if (closing_bracket_pos != std::string::npos) {
                if (closing_bracket_pos == line.size() - 1) {
                    if (opening_bracket_pos < closing_bracket_pos)
                        line = line.substr(opening_bracket_pos + 1,
                                           closing_bracket_pos - opening_bracket_pos - 1);
                    else
                        throw std::runtime_error("[ is going after ]");
                } else
                    throw std::runtime_error("Syntax error: line is not ending with ]");
            } else
                throw std::runtime_error("Missing ]");
        } else
            throw std::runtime_error("Syntax error: line is not staring with [");
    } else
        throw std::runtime_error("Missing [");
}


/////////////////////////////////////////////////////////////////////


KV::KV() {}

KV::KV(const std::string& key, const std::string& value) : m_key(key), m_value(value) {}

KV::KV(std::string&& key, std::string&& value) : m_key(std::move(key)), m_value(std::move(value)) {}

KV::KV(const std::string& line) { fromString(line); }

KV::KV(std::string&& line) { fromString(line); }

KV::KV(const KV& kv) {
    m_key = kv.m_key;
    m_value = kv.m_value;
}

KV::KV(KV&& kv) : m_key(std::move(kv.m_key)), m_value(std::move(kv.m_value)) {
    kv.m_key.erase();
    kv.m_value.erase();
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

    kv.m_key.erase();
    kv.m_value.erase();

    return *this;
}

template <typename T>
void KV::fromString(T line) {
    uncommentLine(line);
    beautifySuffix(line);

    if (!line.empty()) {
        std::size_t equal_pos = line.find(EQUAL_SYMBOL);

        if (equal_pos != std::string::npos) {
            std::string&& key = line.substr(0, equal_pos);
            beautifySuffix(key);

            if (!key.empty()) {
                m_key = std::move(key);
                line.erase(0, equal_pos + 1);
                m_value = std::move(line);
            } else
                throw std::runtime_error("Incorrect line. Key must not be empty");
        } else
            throw std::runtime_error("Incorrect line. Missing '=' symbol");
    } else
        throw std::runtime_error("Empty line");
}

KV::~KV() {}


/////////////////////////////////////////////////////////////////////


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
    section.m_name.erase();
    section.m_options.erase(m_options.begin(), m_options.end());
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
    section.m_name.erase();
    section.m_options.erase(m_options.begin(), m_options.end());

    return *this;
}

std::string& Section::operator[](const std::string& key) { return find(key); }

std::string& Section::operator[](std::string&& key) { return find(key); }

template <typename T>
std::string& Section::find(T key) {
    if (!m_options.empty()) {
        auto temp = std::find_if(m_options.begin(), m_options.end(),
                                 [key](const KV& i) { return i.m_key == key; });
        return temp->m_key == key ? temp->m_value : insert(key);
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


/////////////////////////////////////////////////////////////////////


}  // namespace ES
