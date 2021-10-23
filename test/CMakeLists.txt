set(INTEREST_INI_EXAMPLES_DIR   "ini")
set(INTEREST_CMAKE_EXAMPLE      "cmake/InstallationTest.cmake")
set(INTEREST_README_EXAMPLE     "example")
set(INTEREST_TEST_DIR           "${CMAKE_CURRENT_BINARY_DIR}")
set(INTEREST_CMAKE_TEST_FILE    "${INTEREST_TEST_DIR}/cmake/CMakeLists.txt")

file(
    COPY ${INTEREST_INI_EXAMPLES_DIR}
    DESTINATION ${INTEREST_TEST_DIR})

file(
    COPY ${INTEREST_README_EXAMPLE}
    DESTINATION ${INTEREST_TEST_DIR}
)

configure_file(
        ${INTEREST_CMAKE_EXAMPLE}
        ${INTEREST_CMAKE_TEST_FILE}
        COPYONLY)

set(INTEREST_TESTS_LIST
        unit-Utils.cpp

        unit-KV.cpp

        unit-Section.cpp
        unit-Ini.cpp
    )

add_library(doctest_main OBJECT unit.cpp)

find_package(doctest REQUIRED)

foreach(filename ${INTEREST_TESTS_LIST})
    string(REGEX REPLACE "unit-([^_]+).cpp" "test-\\1" testcase ${filename})

    add_executable(${testcase} $<TARGET_OBJECTS:doctest_main> ${filename})

    add_test(
            NAME "${testcase}"
            COMMAND ${testcase} ${DOCTEST_TEST_FILTER} --no-skip)

    target_include_directories(${testcase} PUBLIC ${DOCTEST_INCLUDE_DIR})
    target_link_libraries(${testcase} Interest)
endforeach()