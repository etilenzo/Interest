# Interest

#### Example library written in C++ using last features for parsing ini formatted streams

> Requires C++ 20 standard

### Example:
```c++
#include <iostream>
#include <sstream>

#include <Ini.hpp>

int main()
{
    std::stringstream ini_stream;
    ini_stream << "[Greeting.1]"   << std::endl
               << "name   = World" << std::endl
               << "phrase = Hello" << std::endl;

    ES::Ini my_ini;
    my_ini.parseFromStream(ini_stream);

    std::cout << my_ini["Greeting.1"]["phrase"]
              << ", "
              << my_ini["Greeting.1"]["name"]
              << std::endl;
    return 0;
}

```
