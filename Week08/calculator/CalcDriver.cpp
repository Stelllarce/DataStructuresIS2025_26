#include "calculator.hpp"
#include <iostream>
#include <stack>
#include <string>
#include <vector>

int getPrecedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}

bool isRightAssociative(char op) {
    return op == '^';
}

long long calculate(const std::string& expression) {
    
    return 0; 
}
