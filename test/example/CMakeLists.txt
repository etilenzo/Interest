cmake_minimum_required(VERSION 3.5)

project(MyProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Interest REQUIRED)

add_executable(MyProject main.cpp)

target_link_libraries(MyProject Interest)