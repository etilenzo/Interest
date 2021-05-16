#include "Ini.hpp"

using std::literals::operator""s;

namespace ES {


/////////////////////////////////////////////////////////////////////


Ini::Ini() {}

Ini::Ini(std::istream& is) { parseFromStream(is); }

Ini::Ini(const Ini& ini) { sections = ini.sections; }

Ini& Ini::operator=(const Ini& ini) {
    if (this == &ini) return *this;

    sections = ini.sections;

    return *this;
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
                    throw std::runtime_error(err.what() + LINE_BREAKER + "On line: "s +
                                             std::to_string(num));
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
                throw std::runtime_error(err.what() + LINE_BREAKER + "On line: "s +
                                         std::to_string(num));
            }
        }
    } else {
        throw std::runtime_error("Input stream is broken");
    }
}

void Ini::dumpToStream(std::ostream& os) const {
    for (const Section& temp : sections) {
        os << OPENING_BRACKET << temp.name << CLOSING_BRACKET << std::endl;

        for (auto& line : temp.options) {
            os << line.key << EQUAL_SYMBOL << line.value << std::endl;
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
    container.dumpToStream(os);

    return os;
}

Ini::~Ini() {}


/////////////////////////////////////////////////////////////////////


}  // namespace ES
