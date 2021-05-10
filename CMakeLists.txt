cmake_minimum_required(VERSION 3.5)

###
### Project
###
set(INTEREST_VERSION_MAJOR 0)
set(INTEREST_VERSION_MINOR 1)
set(INTEREST_VERSION ${INTEREST_VERSION_MAJOR}.${INTEREST_VERSION_MINOR})
project(Interest VERSION ${INTEREST_VERSION} LANGUAGES CXX)

###
### Options
###
option(ENABLE_TESTS OFF)
option(BUILD_SHARED_LIBS "Build as shared/static library." OFF)

###
### Sources
###
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(HEADER_LIST
    include/Section.hpp
    include/Ini.hpp)

set(SRC_LIST
    src/Section.cpp
    src/Ini.cpp)

###
### Build the project
###
add_library(${PROJECT_NAME} "${SRC_LIST}")
target_include_directories(${PROJECT_NAME} PUBLIC "include")

if (${ENABLE_TESTS})
    find_package(GTest REQUIRED)
    target_include_directories(${PROJECT_NAME} PRIVATE ${GTEST_INCLUDE_DIRS})
endif()

target_link_libraries(${PROJECT_NAME} ${GTEST_LIBRARIES})
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "${HEADER_LIST}")
set_property(TARGET ${PROJECT_NAME} PROPERTY VERSION "${INTEREST_VERSION}")

###
### Install the project
###
include(GNUInstallDirs)
install(TARGETS "${PROJECT_NAME}"
    EXPORT "${PROJECT_NAME}Targets"
    LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    PUBLIC_HEADER DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${PROJECT_NAME}")

###
### Configs for find_package()
###
include(CMakePackageConfigHelpers)
export(EXPORT "${PROJECT_NAME}Targets"
    FILE "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}/${PROJECT_NAME}Targets.cmake")
configure_file("cmake/${PROJECT_NAME}Config.cmake"
         "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}/${PROJECT_NAME}Config.cmake"
    COPYONLY)
install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}/${PROJECT_NAME}Config.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}/${PROJECT_NAME}Targets.cmake"
    DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/${PROJECT_NAME}")

###
### Tests
###

if (${ENABLE_TESTS})
    message(STATUS "Building of tests is enabled")
    enable_testing()
    add_subdirectory(test)
    configure_file("test/Ini/test_stream.ini"
        "${CMAKE_CURRENT_BINARY_DIR}/test/")
endif()
