set(INTEREST_INI_EXAMPLES_DIR   "ini")
set(INTEREST_TEST_DIR           "${CMAKE_CURRENT_BINARY_DIR}")

find_package(doctest REQUIRED)

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
target_link_libraries(doctest_main doctest::doctest)

foreach(filename ${INTEREST_TESTS_LIST})
    string(REGEX REPLACE "unit-(^[^_]+).cpp" "test-\\1" testcase ${filename})

    add_executable(${testcase} $<TARGET_OBJECTS:doctest_main> ${filename})

    add_test(
            NAME "${testcase}"
            COMMAND ${testcase} ${DOCTEST_TEST_FILTER} --no-skip)

    target_link_libraries(${testcase} PRIVATE ${INTEREST_TARGET_NAME})
endforeach()