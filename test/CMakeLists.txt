set(INTEREST_INI_EXAMPLES_DIR   "ini")
set(INTEREST_TEST_DIR           "${CMAKE_CURRENT_BINARY_DIR}")

file(
    COPY ${INTEREST_INI_EXAMPLES_DIR}
    DESTINATION ${INTEREST_TEST_DIR})


set(INTEREST_TESTS_LIST
        unit-Utils.cpp

        unit-KV.cpp

        unit-Section.cpp
        unit-Ini.cpp
    )

add_library(doctest_main OBJECT unit.cpp)

find_package(doctest)

if (${DOCTEST_FOUND})
    target_link_libraries(doctest_main doctest)
else()
    include(ExternalProject)
    find_package(Git REQUIRED)

    ExternalProject_Add(
            doctest
            PREFIX ${CMAKE_BINARY_DIR}/doctest
            GIT_REPOSITORY https://github.com/onqtam/doctest.git
            TIMEOUT 10
            UPDATE_COMMAND ${GIT_EXECUTABLE} pull
            CONFIGURE_COMMAND ""
            BUILD_COMMAND ""
            INSTALL_COMMAND ""
            LOG_DOWNLOAD ON
    )

    ExternalProject_Get_Property(doctest source_dir)
    set(DOCTEST_INCLUDE_DIR ${source_dir}/doctest CACHE INTERNAL "Path to include folder for doctest")

    target_include_directories(doctest_main PUBLIC ${DOCTEST_INCLUDE_DIR})
endif()

foreach(filename ${INTEREST_TESTS_LIST})
    string(REGEX REPLACE "unit-([^_]+).cpp" "test-\\1" testcase ${filename})

    add_executable(${testcase} $<TARGET_OBJECTS:doctest_main> ${filename})

    add_test(
            NAME "${testcase}"
            COMMAND ${testcase} ${DOCTEST_TEST_FILTER} --no-skip)

    target_link_libraries(${testcase} PRIVATE ${INTEREST_TARGET_NAME})
endforeach()