cmake_minimum_required(VERSION 3.10)
project(BST)

# BST library
add_library(bst
    include/bst/bst.hpp
    src/bst.cpp
)

# Тесты
if(ENABLE_TESTS)
    add_subdirectory(test/gtest)
endif()
