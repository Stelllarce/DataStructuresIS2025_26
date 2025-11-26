#include <catch2/catch_test_macros.hpp>
#include "calculator.hpp"

TEST_CASE("Basic arithmetic operations", "[basic]") {
    REQUIRE(calculate("1 + 1") == 2);
    REQUIRE(calculate("10 - 4") == 6);
    REQUIRE(calculate("3 * 4") == 12);
    REQUIRE(calculate("20 / 5") == 4);
}

TEST_CASE("Operator precedence", "[precedence]") {
    REQUIRE(calculate("2 + 3 * 4") == 14);
    REQUIRE(calculate("2 * 3 + 4") == 10);
    REQUIRE(calculate("10 + 20 / 5") == 14);
}

TEST_CASE("Braces", "[braces]") {
    REQUIRE(calculate("(2 + 3) * 4") == 20);
    REQUIRE(calculate("2 * (3 + 4)") == 14);
    REQUIRE(calculate("((1 + 2) * (3 + 4))") == 21);
}

TEST_CASE("Unary operators inside braces", "[unary]") {
    REQUIRE(calculate("(-5)") == -5);
    REQUIRE(calculate("5 + (-3)") == 2);
    REQUIRE(calculate("(-2) * (-3)") == 6);
    REQUIRE(calculate("(+5)") == 5);
}

TEST_CASE("Right-to-left associativity (Power operator ^)", "[rtl]") {
    REQUIRE(calculate("2 ^ 3") == 8);
    
    // Right-to-left associativity: 2^3^2 should be 2^(3^2) = 2^9 = 512
    // If it were left-to-right: (2^3)^2 = 8^2 = 64
    REQUIRE(calculate("2 ^ 3 ^ 2") == 512); 
}

TEST_CASE("Complex expressions", "[complex]") {
    REQUIRE(calculate("3 + 4 * 2 / ( 1 - 5 )") == 1); // 3 + 8 / -4 = 3 - 2 = 1
    REQUIRE(calculate("5 ^ 2 + 2 ^ 3 ^ 2 * ( 2 ^ 3 ) ^ 2") == 32793); // 25 + 512 * 64 = 25 + 32768 = 32793 
}

TEST_CASE("Error handling: Unbalanced braces", "[error]") {
    REQUIRE_THROWS(calculate("(1 + 2"));
    REQUIRE_THROWS(calculate("1 + 2)"));
    REQUIRE_THROWS(calculate("((1 + 2)"));
    REQUIRE_THROWS(calculate("(1 + 2))"));
}

TEST_CASE("Error handling: Invalid characters", "[error]") {
    REQUIRE_THROWS(calculate("1 + a"));
    REQUIRE_THROWS(calculate("1 + 2 * x"));
    REQUIRE_THROWS(calculate("1 $ 2"));
}

TEST_CASE("Error handling: Malformed expressions", "[error]") {
    REQUIRE_THROWS(calculate("1 + + 2")); 
    REQUIRE_THROWS(calculate("1 + * 2"));
    REQUIRE_THROWS(calculate("* 1"));
    REQUIRE_THROWS(calculate("()"));      
    REQUIRE_THROWS(calculate(""));        
}

TEST_CASE("Edge cases: Whitespace handling", "[edge]") {
    REQUIRE(calculate("  1   +   2  ") == 3);
    REQUIRE(calculate("\t1\t+\t2\t") == 3);
}

TEST_CASE("Edge cases: Large numbers and results", "[edge]") {
    // Assuming long long is used
    REQUIRE(calculate("1000000 + 2000000") == 3000000);
    REQUIRE(calculate("0 * 1000") == 0);
}

TEST_CASE("Edge cases: Division by zero", "[edge]") {
    REQUIRE_THROWS(calculate("1 / 0"));
    REQUIRE_THROWS(calculate("1 / (5 - 5)"));
}
