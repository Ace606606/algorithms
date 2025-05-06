# lib BST
add_library(bst src/bst.cpp)
# includes
target_include_directories(bst PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
# links
target_link_libraries(bst PRIVATE utils logger)

# manual tests (ALWAYS build)
add_executable(bst_manual test/manual/main.cpp)
target_link_libraries(bst_manual PRIVATE bst utils logger)