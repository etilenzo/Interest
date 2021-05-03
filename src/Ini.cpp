#include "Ini.hpp"

using std::literals::operator""s;

namespace ES {

std::string Ini::parseBrackets(std::string_view line) {
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

Section& Ini::insert(std::string_view name) {
    Section temp(name, std::vector<KV>());
    sections.push_back(temp);
    return sections.back();
}

void Ini::parseFromStream(std::istream& is) {
    if (is) {
        sections.clear();

        std::string line;
        std::size_t num = 0;
        std::string name;

        while (getline(is, line)) {
            ++num;

            try {
                std::string temp = parseBrackets(line);

                if (!temp.empty()) {
                    name = temp;
                    insert(name);
                    continue;
                } else {
                    throw std::runtime_error("Empty section name");
                }
            } catch (const std::runtime_error& err) {
                if (err.what() != "Missing opening bracket"s) {
                    throw std::runtime_error(err.what() + "\nOn line: "s + std::to_string(num));
                } else {
                    if (num == 1) {
                        throw std::runtime_error(
                            "Ini formatting is wrong.\n"
                            "Missing first section");
                    }
                }
            }

            try {
                KV child(line);
                operator[](name).options.push_back(child);
            } catch (const std::runtime_error& err) {
                throw std::runtime_error(err.what() + "\nOn line: "s + std::to_string(num));
            }
        }
    } else {
        throw std::runtime_error("Input stream is broken");
    }
}

void Ini::dumpToStream(std::ostream& os) {
    for (const Section& temp : sections) {
        os << "[" << temp.name << "]\n";

        for (auto& line : temp.options) {
            os << line.key << "=" << line.value << "\n";
        }
    }
}

void Ini::removeEmpty() {
    sections.erase(std::remove_if(sections.begin(), sections.end(),
                                  [](const Section& i) { return i.options.empty(); }),
                   sections.end());
}

void Ini::clear() { sections.clear(); }

Section& Ini::operator[](const std::string& name) {
    if (sections.size() != 0) {
        auto temp = std::find_if(sections.begin(), sections.end(),
                                 [name](const Section& i) { return i.name == name; });
        return temp->name == name ? *temp : insert(name);
    } else {
        return insert(name);
    }
}

std::ostream& operator<<(std::ostream& os, const ES::Ini& container) {
    for (auto i = container.sections.begin(); i != container.sections.end(); ++i) {
        if (++i != container.sections.end()) {
            os << *i << LINE_BREAKER;
        } else {
            os << *i;
        }
    }

    return os;
}

}  // namespace ES
