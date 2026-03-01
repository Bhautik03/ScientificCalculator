#include <gtest/gtest.h>
#include <cmath> 
#include "../include/calculator.h"

TEST(CalculatorTest, SquareRootTest) {
    EXPECT_DOUBLE_EQ(squareRoot(25), 5);
}

TEST(CalculatorTest, FactorialTest) {
    EXPECT_EQ(factorial(5), 120);
}

TEST(CalculatorTest, NaturalLogTest) {
    EXPECT_DOUBLE_EQ(naturalLog(exp(1)), 1);
}

TEST(CalculatorTest, PowerTest) {
    EXPECT_DOUBLE_EQ(power(2, 3), 8);
}
