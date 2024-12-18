#include "Func.h"
#include <cmath>

double factorial(int num) {
    double result = 1;
    for (int i = 1; i <= num; ++i) {
        result *= i;
    }
    return result;
}

// Implementation of FuncA using Taylor series for sin(x)
double Func::FuncA(double x, int n) {
    double sum = 0;
    for (int i = 0; i < n; ++i) {
        int power = 2 * i + 1;
        double term = pow(-1, i) * pow(x, power) / factorial(power);
        sum += term;
    }
    return sum;
}




