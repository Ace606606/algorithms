find_package(GTest REQUIRED)  # search Google Test

# create an executable file for tests
add_executable(bst_tests bst_test.cpp test_main.cpp)
# linking with BST and GTest
target_link_libraries(bst_tests PRIVATE bst utils GTest::GTest)

# adding a test to CTest
add_test(NAME bst_tests COMMAND bst_tests)
