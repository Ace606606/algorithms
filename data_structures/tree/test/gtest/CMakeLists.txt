# test/gtest/CMakeLists.txt
find_package(GTest REQUIRED)

add_executable(bst_tests
    bst_test.cpp
    test_main.cpp
)
target_link_libraries(bst_tests
    PRIVATE
    bst
    GTest::GTest
)
enable_testing()
add_test(NAME bst_tests COMMAND bst_tests)
