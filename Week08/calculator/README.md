# Calculator Project

## Overview

This project involves implementing a C++ calculator capable of evaluating mathematical expressions given as strings. The calculator supports standard arithmetic operations, operator precedence, parentheses, unary operators, and a special right-associative operator.

## Features to Implement

Your task is to implement the `calculate` function in `CalcDriver.cpp`. The calculator must support the following:

1.  **Data Types**: Whole numbers (integers).
2.  **Binary Operators**:
    *   Addition (`+`)
    *   Subtraction (`-`)
    *   Multiplication (`*`)
    *   Division (`/`)
    *   **Power (`^`)**: This operator has higher precedence than `*` and `/` and is **right-associative** (e.g., `2^3^2` is evaluated as `2^(3^2)`).
3.  **Unary Operators**:
    *   Unary Plus (`+`)
    *   Unary Minus (`-`)
    *   *Note*: These should be handled correctly, especially inside braces (e.g., `(-5)`).
4.  **Grouping**: Parentheses `()` to alter operation order.
5.  **Whitespace**: The calculator should ignore whitespace (spaces, tabs).
6.  **Error Handling**:
    *   Throw an exception for **division by zero**.
    *   Throw an exception for **unbalanced braces**.
    *   Throw an exception for **invalid characters** or **malformed expressions**.

## Implementation Guide

### Files

*   `calculator.hpp`: Header file declaring the `calculate` function.
*   `CalcDriver.cpp`: The implementation file where you will write your code.
*   `tests.cpp`: Contains unit tests using the Catch2 framework to verify your implementation.
*   `CMakeLists.txt`: Build configuration.

### Suggested Approach

The **Shunting-yard algorithm** by Edsger Dijkstra is a classic method for parsing mathematical expressions. It typically involves:

1.  **Two Stacks**: One for operators and one for operands (numbers).
2.  **Parsing**: Iterate through the expression string.
    *   If it's a number, push it to the operand stack.
    *   If it's an operator, handle precedence and associativity by popping operators from the stack and applying them until the correct position is found.
    *   If it's an opening brace `(`, push it.
    *   If it's a closing brace `)`, process everything until the matching `(`.

### Building and Running Tests

This project uses CMake and Catch2.

1.  **Create a build directory**:
    ```bash
    mkdir build
    cd build
    ```

2.  **Generate build files**:
    ```bash
    cmake ..
    ```

3.  **Build the project**:
    ```bash
    make
    ```

4.  **Run the tests**:
    ```bash
    ./tests
    ```

## Example Expressions

*   `"1 + 1"` -> `2`
*   `"2 * (3 + 4)"` -> `14`
*   `"(-5) * 3"` -> `-15`
*   `"2 ^ 3 ^ 2"` -> `512`
