#pragma once

#include <fstream>
#include <iostream>

#include "Section.hpp"

namespace ES {

std::optional<std::string> parseBraces(std::string_view line);

class Ini {
public:
    Ini() {}
    explicit Ini(std::istream& is) { parseFromStream(is); }

    std::vector<Section> sections;

    std::string parseBrackets(std::string_view line);

    void parseFromStream(std::istream& is);
    void dumpToStream(std::ostream& os);

    void removeEmpty();
    /* Удалить пустые секции
     */

    void clear();
    /* Очистить контейнер
     */

    Section& operator[](const std::string& name);
    friend std::ostream& operator<<(std::ostream& os, const Ini& container);

private:
    Section& insert(std::string_view name);
    void parseOrigin(std::istream& is);
};

}  // namespace ES
