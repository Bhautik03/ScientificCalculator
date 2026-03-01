#include <iostream>
#include <cmath>
#include "../include/calculator.h"

using namespace std;

double squareRoot(double x) {
    if (x < 0) {
        throw invalid_argument("Cannot calculate square root of negative number");
    }
    return sqrt(x);
}

long long factorial(int x) {
    if (x < 0) {
        throw invalid_argument("Factorial not defined for negative numbers");
    }
    long long result = 1;
    for (int i = 1; i <= x; i++) {
        result *= i;
    }
    return result;
}

double naturalLog(double x) {
    if (x <= 0) {
        throw invalid_argument("Natural Log defined only for positive numbers");
    }
    return log(x);
}

double power(double base, double exponent) {
    return pow(base, exponent);
}
