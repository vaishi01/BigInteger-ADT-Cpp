/*
 Name - Vaishnavi Jaligama
 Student Id- 1936593
 Cruz id - vjaligam
 Course - CSE101
 Quarter - Winter 2024
 Professor - Mr. Patrick Tantalo
 Programming assignment - 6
 Due date - March 4th, 2024
 File name - BigIntegerTest.cpp
*/

#include<iostream>
#include<string>
#include<stdexcept>
#include"BigInteger.h"

using namespace std;

int main() {

    cout << "Testing BigInteger implementation:" << endl;

    // Test Constructors
    cout << "Test Constructors:" << endl;
    BigInteger zero;
    cout << "Zero: " << zero << endl;

    BigInteger num1 = BigInteger(123456789);
    cout << "num1: " << num1 << endl;

    BigInteger num2 = BigInteger("-987654321");
    cout << "num2: " << num2 << endl;

    BigInteger num3 = BigInteger("123456789012345678901234567890");
    cout << "num3: " << num3 << endl;

    // Test Copy Constructor
    cout << "Test Copy Constructor:" << endl;
    BigInteger copyNum1 = num1;
    cout << "Copy of num1: " << copyNum1 << endl;

    // Test Access Functions
    cout << "Test Access Functions:" << endl;
    cout << "Sign of num1: " << num1.sign() << endl;
    cout << "Comparison of num1 and num2: " << num1.compare(num2) << endl;

    // Test Manipulation Procedures
    cout << "Test Manipulation Procedures:" << endl;
    num1.makeZero();
    cout << "Zeroed num1: " << num1 << endl;
    num2.negate();
    cout << "Negated num2: " << num2 << endl;

    // Test Arithmetic Operations
    cout << "Test Arithmetic Operations:" << endl;
    BigInteger sum = num1.add(num2);
    cout << "Sum of num1 and num2: " << sum << endl;

    BigInteger diff = num1.sub(num2);
    cout << "Difference of num1 and num2: " << diff << endl;

    BigInteger product = num1.mult(num2);
    cout << "Product of num1 and num2: " << product << endl;

    // Test Other Functions
    cout << "Test Other Functions:" << endl;
    cout << "String representation of num1: " << num1.to_string() << endl;

    // Test Overridden Operators
    cout << "Test Overridden Operators:" << endl;
    cout << "Output using << operator: " << num1 << endl;
    cout << "Comparison using == operator: " << (num1 == copyNum1 ? "True" : "False") << endl;
    cout << "Comparison using < operator: " << (num1 < copyNum1 ? "True" : "False") << endl;
    cout << "Comparison using <= operator: " << (num1 <= copyNum1 ? "True" : "False") << endl;
    cout << "Comparison using > operator: " << (num1 > copyNum1 ? "True" : "False") << endl;
    cout << "Comparison using >= operator: " << (num1 >= copyNum1 ? "True" : "False") << endl;

    cout << "Test completed." << endl;

    return EXIT_SUCCESS;
}

/*Expected output:
Testing BigInteger implementation:
Test Constructors:
Zero: 0
num1: 123456789
num2: -987654321
num3: 123456789012345678901234567890
Test Copy Constructor:
Copy of num1: 123456789
Test Access Functions:
Sign of num1: 1
Comparison of num1 and num2: 1
Test Manipulation Procedures:
Zeroed num1: 0
Negated num2: 987654321
Test Arithmetic Operations:
Sum of num1 and num2: 987654321
Difference of num1 and num2: -987654321
Product of num1 and num2: 0
Test Other Functions:
String representation of num1: 0
Test Overridden Operators:
Output using << operator: 0
Comparison using == operator: False
Comparison using < operator: True
Comparison using <= operator: True
Comparison using > operator: False
Comparison using >= operator: False
Test completed.
*/