#include <iostream>
#include <sstream>

#include <Ini.hpp>

int main() {
    std::stringstream ini_stream;
    ini_stream << "[Greeting.1]" << std::endl
               << "name   = World" << std::endl
               << "phrase = Hello" << std::endl;

    ES::Ini my_ini;
    boost::optional<ES::Error> error = my_ini.parseFromStream(ini_stream);

    if (!error) {
        std::cout << my_ini["Greeting.1"]["phrase"] << ", " << my_ini["Greeting.1"]["name"]
                  << std::endl;
    }

    return 0;
}