cmake_minimum_required(VERSION 3.10)
project(DataStructuresAndAlgorithms)

find_package(spdlog REQUIRED)

# options
option(BUILD_BST "Build Binary Search Tree" ON)
option(BUILD_SORTING "Build Sorting Algorithms" OFF)
option(ENABLE_TESTS "Build tests" OFF)

# utils build always
add_library(utils utils/parser_file.cpp utils/parser_file.hpp)
target_include_directories(utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/utils)

# logs
add_subdirectory(common/logger)

# connection components by options [-DBUILD_BST=ON]
if(BUILD_BST)
    message(STATUS "Building BST")
    add_subdirectory(data_structures/tree)
endif()

if(BUILD_SORTING)
    message(STATUS "Building sorting algorithms")
    add_subdirectory(algorithms/sorting)
endif()

#cmake --build . -DCMAKE_TOOLCHAIN_FILE=/path/to/vcpkg/scripts/buildsystems/vcpkg.cmake  [-DENABLE_TESTS=ON] 
if(ENABLE_TESTS)
    enable_testing()
    # connecting tests from subdirectories
    if(BUILD_BST)
        add_subdirectory(data_structures/tree/test/gtest)
    endif()
    if(BUILD_SORTING)
        add_subdirectory(algorithms/sorting/test)
    endif()
endif()
