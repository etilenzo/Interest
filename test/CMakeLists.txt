set(TEST_SRC_LIST
    main.cpp

    Utils_test.cpp

    KV_test.cpp

    Section_test.cpp
    #Ini_test.cpp

    )

add_executable(${PROJECT_NAME}_test ${TEST_SRC_LIST})
target_link_libraries(${PROJECT_NAME}_test ${PROJECT_NAME})
add_test(${PROJECT_NAME} ${PROJECT_NAME}_test)
