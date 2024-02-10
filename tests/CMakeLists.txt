# define project settings
cmake_minimum_required(VERSION 3.14)
project(gtestbox)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_SOURCE_DIR}/../cpp/data_structures/nodes/inc)

add_library(${PROJECT_NAME} STATIC
    ${CMAKE_SOURCE_DIR}/../cpp/data_structures/nodes/src/test.cpp
)

# hook and configure dependencies
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
add_subdirectory(${CMAKE_SOURCE_DIR}/../googletest ${CMAKE_SOURCE_DIR}/build/googletest EXCLUDE_FROM_ALL)
enable_testing()

# add; link; and catalog test_hello tests
add_executable(test_defaults test_defaults.cpp)

target_include_directories(test_defaults PUBLIC ${CMAKE_SOURCE_DIR}/../googletest)
target_link_libraries(test_defaults gtest gtest_main ${PROJECT_NAME})
#add_test(NAME test_defaults COMMAND test_defaults)
