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

bool is_ws(char c) {
    return c == '\t' || c == ' ';
}

std::string trim_ws(const std::string& expr) {
    std::string trimmed;

    for (size_t i = 0; i < expr.size(); i++)
    {
        if (is_ws(expr[i])) continue;
        trimmed[i] = expr[i];
    }
    return trimmed;
}

bool is_op(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

bool validate(const std::string& expr) {
    if (is_op(expr[expr.length()]))
        return false;

    int braces_counter = 0;
    for (size_t i = 0; i < expr.size() - 1; i++)
    {
        char curr = expr[i];
        if (braces_counter < 0)
            return false;
        if (curr == '(')
            ++braces_counter;
        else if (curr == ')')
            --braces_counter;

        if (curr == '/' && expr[i + 1] == '0') {
            return false;
        }
    }

    return true;
}

long long calculate(const std::string& expression) {
    if (!validate(trim_ws(expression)))
        throw std::runtime_error("Wrong expression.");

    return 0; 
}
