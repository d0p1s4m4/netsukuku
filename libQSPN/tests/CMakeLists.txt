project(libQSPN_tests)

add_executable(test_dummy
    test_dummy.c
)

target_link_libraries(test_dummy
    PRIVATE
        libQSPN cmocka::cmocka
)
target_include_directories(test_dummy PUBLIC "${CMOCKA_INCLUDE_DIRS}")

add_test(${PROJECT_NAME} test_dummy)