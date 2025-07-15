cmake_minimum_required(VERSION 3.14)
project(bf_compiler)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GTest REQUIRED)
enable_testing()

add_executable(bf src/main.cpp src/lexer.cpp src/parser.cpp src/codegen.cpp)
target_include_directories(bf PRIVATE include)

add_executable(run_tests tests/test_main.cpp 
    tests/test_lexer.cpp src/lexer.cpp
)
target_include_directories(run_tests PRIVATE include)

target_link_libraries(run_tests
    GTest::gtest
    GTest::gtest_main
    pthread
)

enable_testing()
add_test(NAME all_tests COMMAND run_tests)
