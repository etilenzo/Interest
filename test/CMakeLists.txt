set(TEST_SRC_LIST
    main.cpp

    Utils_test.cpp

    KV_test.cpp

    Section_test.cpp
    Ini_test.cpp

    )

add_library(doctest_main ${TEST_SRC_LIST})
target_link_libraries(doctest_main ${PROJECT_NAME})
add_test(${PROJECT_NAME} doctest_main)