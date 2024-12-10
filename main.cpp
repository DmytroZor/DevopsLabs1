#include <iostream>
#include "FuncA.h"

int main() {
    Func func;
  
    double x = 3.14; 
    int n = 5;  

    std::cout << "FuncA result: " << func.FuncA(x, n) << std::endl;
    return 0;
}


