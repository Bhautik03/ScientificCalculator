cmake_minimum_required(VERSION 3.10)
project(ScientificCalculator)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

# Main Application
add_executable(calculator src/main.cpp src/calculator.cpp)

# Testing
enable_testing()

find_package(GTest REQUIRED)

add_executable(test_calculator
    tests/test_calculator.cpp
    src/calculator.cpp
)

target_link_libraries(test_calculator
    GTest::gtest
    GTest::gtest_main
)

add_test(NAME CalculatorTest COMMAND test_calculator)
