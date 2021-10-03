#include "Ini.hpp"

using std::literals::operator""s;

namespace ES {


/////////////////////////////////////////////////////////////////////


Ini::Ini() {}

Ini::Ini(std::istream& is) { parseFromStream(is); }

Ini::Ini(const Ini& ini) : m_sections(ini.m_sections) {}

Ini::Ini(Ini&& ini) : m_sections(std::move(ini.m_sections)) {
    ini.m_sections.erase(ini.m_sections.begin(), ini.m_sections.end());
}

Ini& Ini::operator=(const Ini& ini) {
    if (this == &ini) return *this;

    m_sections = ini.m_sections;

    return *this;
}

Ini& Ini::operator=(Ini&& ini) {
    if (this == &ini) return *this;

    m_sections = std::move(ini.m_sections);
    ini.m_sections.erase(ini.m_sections.begin(), ini.m_sections.end());

    return *this;
}

Section& Ini::operator[](const std::string& name) {
    if (m_sections.size() != 0) {
        auto temp = std::find_if(m_sections.begin(), m_sections.end(),
                                 [name](const Section& i) { return i.m_name == name; });
        return temp->name == name ? *temp : insert(name);
    } else
        return insert(name);
}

Section& Ini::insert(std::string_view name) {
    // BUG : Функция не ищет, существует ли такая структура уже, а создаёт в любом случае
    Section temp(name, std::vector<KV>());
    m_sections.push_back(temp);
    return m_sections.back();
}

void Ini::parseFromStream(std::istream& is) {
    if (is) {
        m_sections.clear();

        std::string line;
        std::size_t num = 0;
        std::string name;

        while (getline(is, line)) {
            ++num;

            try {
                parseBrackets(line);
                std::string temp = line;

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
                // operator[](name).options.push_back(child);
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
    for (const Section& temp : m_sections) {
        os << OPENING_BRACKET << temp.m_name << CLOSING_BRACKET << std::endl;

        for (auto& line : temp.m_options) {
            os << line.m_key << EQUAL_SYMBOL << line.m_value << std::endl;
        }
    }
}

void Ini::removeEmpty() {
    m_sections.erase(std::remove_if(m_sections.begin(), m_sections.end(),
                                    [](const Section& i) { return i.m_options.empty(); }),
                     m_sections.end());
}

void Ini::clear() { m_sections.clear(); }

std::ostream& operator<<(std::ostream& os, const ES::Ini& container) {
    container.dumpToStream(os);

    return os;
}

Ini::~Ini() {}

/////////////////////////////////////////////////////////////////////


}  // namespace ES
