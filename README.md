# Interest


[![Build Status](https://app.travis-ci.com/etilenzo/Interest.svg?branch=master)](https://app.travis-ci.com/etilenzo/Interest)
[![Ubuntu](https://github.com/etilenzo/Interest/actions/workflows/ubuntu.yml/badge.svg)](https://github.com/etilenzo/Interest/actions/workflows/ubuntu.yml)
[![Issues](https://img.shields.io/github/issues/etilenzo/Interest)](https://github.com/etilenzo/Interest/issues)
[![Last commit](https://img.shields.io/github/last-commit/etilenzo/Interest)](https://github.com/etilenzo/Interest/commit/master)
[![Licence](https://img.shields.io/badge/licence-MIT-blue)](https://gitlab.com/Evilenzo/interest/-/blob/master/LICENSE)
[![Language](https://img.shields.io/github/languages/top/etilenzo/Interest)](https://img.shields.io/github/languages/top/etilenzo/Interest)
[![Release](https://img.shields.io/github/v/release/etilenzo/Interest)](https://github.com/etilenzo/Interest/releases)


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
