# Interest


[![pipeline status](https://gitlab.com/Evilenzo/interest/badges/master/pipeline.svg)](https://gitlab.com/Evilenzo/interest/-/commits/master)
[![Codacy Badge](https://app.codacy.com/project/badge/Grade/30632a4762e14ac8ab376c10d18ee73c)](https://www.codacy.com/gl/Evilenzo/interest/dashboard?utm_source=gitlab.com&amp;utm_medium=referral&amp;utm_content=Evilenzo/interest&amp;utm_campaign=Badge_Grade)

#### Example library written in C++ using last standards features for parsing ini formatted streams

> Requires C++ 20 standard

### Example:
```cmake
### CMakeLists.txt

cmake_minimum_required(VERSION 3.5)

project(MyProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Interest REQUIRED)

add_executable(MyProject main.cpp)

target_link_libraries(MyProject Interest)

```


```c++
/// main.cpp

#include <iostream>
#include <sstream>

#include <Ini.hpp>

int main() {
  std::stringstream ini_stream;
  ini_stream << "[Greeting.1]"   << std::endl
             << "name   = World" << std::endl
             << "phrase = Hello" << std::endl;

  ES::Ini my_ini;
  boost::optional<ES::Error> error = my_ini.parseFromStream(ini_stream);

  if (!error) {
    std::cout << my_ini["Greeting.1"]["phrase"] << ", "
              << my_ini["Greeting.1"]["name"] << std::endl;
  }

  return 0;
}

```
