# define project settings
cmake_minimum_required(VERSION 3.14)
project(gtestbox)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_SOURCE_DIR}/../../cpp/data_structures/graph/inc)


# hook and configure dependencies
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
add_subdirectory(${CMAKE_SOURCE_DIR}/../../googletest googletest EXCLUDE_FROM_ALL)
enable_testing()

# add; link; and catalog test_hello tests
add_executable(weigthed_graph_test weigthed_graph_test.cpp)

target_include_directories(weigthed_graph_test PUBLIC ${CMAKE_SOURCE_DIR}/../../googletest)
target_link_libraries(weigthed_graph_test gtest gtest_main)
