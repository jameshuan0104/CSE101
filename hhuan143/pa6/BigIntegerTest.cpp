/*
*James Huang, hhuan143
*2023 spring CSE101 PA#6
*BigIntegerTest.cpp
*simple test for BigInteger.cpp 
*/

#include <iostream>
#include "BigInteger.h"

using namespace std;

int main() {
    BigInteger a = BigInteger("12345678901234567890");
    BigInteger b = BigInteger("98765432109876543210");

    // Equality
    cout << "Equality: " << (a == b ? "True" : "False") << endl;

    // Less than
    cout << "Less than: " << (a < b ? "True" : "False") << endl;

    // Less than or equal to
    cout << "Less than or equal to: " << (a <= b ? "True" : "False") << endl;

    // Greater than
    cout << "Greater than: " << (a > b ? "True" : "False") << endl;

    // Greater than or equal to
    cout << "Greater than or equal to: " << (a >= b ? "True" : "False") << endl;

    // Compound assignment: addition
    a += b;
    cout << "Addition: " << a << endl;

    // Compound assignment: subtraction
    b -= a;
    cout << "Subtraction: " << b << endl;

    // Compound assignment: multiplication
    a *= b;
    cout << "Multiplication: " << a << endl;

    return 0;
}
