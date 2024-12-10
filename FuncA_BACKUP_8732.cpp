#include "Func.h"
<<<<<<< HEAD
#include <cmath>

// Helper function to calculate factorial
=======
#include <cmath> // for pow() and factorial()

>>>>>>> branchA
double factorial(int num) {
    double result = 1;
    for (int i = 1; i <= num; ++i) {
        result *= i;
    }
    return result;
<<<<<<< HEAD
=======
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
>>>>>>> branchA
}

// Implementation of FuncA using the first 3 terms of the Taylor series
double Func::FuncA(double x, int n = 3) {
    double sum = 0;
    for (int i = 0; i < n; ++i) {
        int power = 2 * i + 1;
        double term = pow(-1, i) * pow(x, power) / factorial(power);
        sum += term;
    }
    return sum;
}



