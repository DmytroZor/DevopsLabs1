#include "FuncA.h"
#include <cassert>
#include <cmath>

void testFuncA() {
    Func func;
    assert(abs(func.FuncA(0, 5)) < 1e-6);  // sin(0) = 0
    assert(abs(func.FuncA(M_PI / 2, 5) - 1) < 1e-6);  // sin(π/2) = 1
}

int main() {
    testFuncA();
    return 0;
}

