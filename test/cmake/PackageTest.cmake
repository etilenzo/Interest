### This file contains only test of find_package() 
### and target_link_libraries() for shared Interest lib

cmake_minimum_required(VERSION 3.12)

project(test LANGUAGES CXX)

find_package(Interest REQUIRED)

if(Interest_FOUND)
	message("-- Library found successfully!")
endif()

add_library(test INTERFACE)

target_link_libraries(test INTERFACE Interest)
