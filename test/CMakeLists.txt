set(TEST_SRC_LIST
    main.cpp

    Section/uncommentLine.cpp
    Section/beautifyPrefix.cpp
    Section/beautifySuffix.cpp
    Section/KV.cpp
    Section/Section.cpp

    Ini/parceBrackets.cpp
    Ini/CommonTest.cpp

    )

add_executable(${PROJECT_NAME}_test ${TEST_SRC_LIST})
target_link_libraries(${PROJECT_NAME}_test ${PROJECT_NAME})
add_test(${PROJECT_NAME} ${PROJECT_NAME}_test)
