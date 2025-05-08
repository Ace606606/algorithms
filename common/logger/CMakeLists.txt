# CMakeLists.txt.logger
# lib logger

add_library(logger logger.cpp logger.hpp log_macros.hpp)

# link spdlog
target_link_libraries(logger PUBLIC spdlog::spdlog)

# include
target_include_directories(logger PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})