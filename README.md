# DISCLAIMER - This is an interview project, no need in review/comments

# Interest


[![Ubuntu](https://github.com/evilenzo/ini/actions/workflows/ubuntu.yml/badge.svg?branch=master)](https://github.com/evilenzo/ini/actions/workflows/ubuntu.yml)
[![macOS](https://github.com/evilenzo/ini/actions/workflows/macos.yml/badge.svg)](https://github.com/evilenzo/ini/actions/workflows/macos.yml)

[![Issues](https://img.shields.io/github/issues/evilenzo/ini)](https://github.com/evilenzo/ini/issues)
[![Last commit](https://img.shields.io/github/last-commit/evilenzo/ini)](https://github.com/evilenzo/ini/commit/master)
[![Licence](https://img.shields.io/badge/licence-MIT-blue)](https://github.com/evilenzo/ini/blob/master/LICENSE)
[![Language](https://img.shields.io/github/languages/top/evilenzo/ini)](https://img.shields.io/github/languages/top/evilenzo/ini)
[![Release](https://img.shields.io/github/v/release/evilenzo/ini)](https://github.com/evilenzo/ini/releases)


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
