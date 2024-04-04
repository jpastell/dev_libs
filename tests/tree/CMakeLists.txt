# define project settings
cmake_minimum_required(VERSION 3.14)
project(gtestbox)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_SOURCE_DIR}/../../cpp/data_structures/bin_tree/inc)


# hook and configure dependencies
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
add_subdirectory(${CMAKE_SOURCE_DIR}/../../googletest googletest EXCLUDE_FROM_ALL)
enable_testing()

# add; link; and catalog test_hello tests
add_executable(tree_test tree_test.cpp)

target_include_directories(tree_test PUBLIC ${CMAKE_SOURCE_DIR}/../../googletest)
target_link_libraries(tree_test gtest gtest_main)
