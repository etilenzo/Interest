#pragma once

#include <iostream>
#include <algorithm>
#include <numeric>
#include <string>
#include <string_view>
#include <vector>

namespace ES {

inline constexpr char OPENING_BRACKET = '[';
inline constexpr char CLOSING_BRACKET = ']';
inline constexpr char EQUAL_SYMBOL = '=';
inline constexpr char LINE_BREAKER = '\n';
inline constexpr char CARRIAGE_RETURN = '\r';
inline constexpr char SPACE_SYMBOL = ' ';
inline constexpr char COMMENT_SYMBOLS[3] = "#;";
inline constexpr char EMPTY_STRING[1] = "";

std::string uncommentLine(std::string_view line);
std::string beautifyPrefix(std::string_view line);
std::string beautifySuffix(std::string_view line);

struct KV {
    KV() {}
    KV(std::string_view _key, std::string_view _value) : key(_key), value(_value) {}
    explicit KV(std::string_view line) { fromString(line); }

    std::string key;
    std::string value;

    void fromString(std::string_view line);
};

struct Section {
    Section() {}
    Section(std::string_view _name, std::vector<KV> _options) : name(_name), options(_options) {}

    std::string name;
    std::vector<KV> options;

    std::string& insert(std::string_view key);

    std::string& operator[](const std::string& key);
};

std::ostream& operator<<(std::ostream& os, const Section& sect);

}  // namespace ES
