/*
 Name - Vaishnavi Jaligama
 Student Id- 1936593
 Cruz id - vjaligam
 Course - CSE101
 Quarter - Winter 2024
 Professor - Mr. Patrick Tantalo
 Programming assignment - 6
 Due date - March 4th, 2024
 File name - Arithmetic.cpp
*/
#include <fstream>
#include <iostream>
#include <string>
#include "BigInteger.h"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <input file> <output file>\n";
        return 1;
    }

    std::ifstream inputFile(argv[1]);
    if (!inputFile.is_open()) {
        std::cerr << "Error: Cannot open input file " << argv[1] << std::endl;
        return 1;
    }

    std::ofstream outputFile(argv[2]);
    if (!outputFile.is_open()) {
        std::cerr << "Error: Cannot open output file " << argv[2] << std::endl;
        inputFile.close();
        return 1;
    }

    std::string lineA, lineB;

    // Read the first number (A)
    std::getline(inputFile, lineA);
    // Skip the blank line
    std::getline(inputFile, lineB);
    // Read the second number (B)
    std::getline(inputFile, lineB);

    inputFile.close();

    BigInteger A(lineA), B(lineB);

    BigInteger sum = A + B;
    BigInteger diff = A - B;
    BigInteger tripleA = 3 * A;
    BigInteger subA = A - A;
    BigInteger doubleB = 2 * B;
    BigInteger tripleAminusDoubleB = tripleA - doubleB;
    BigInteger product = A * B;
    BigInteger ASquared = A * A;
    BigInteger BSquared = B * B;
    BigInteger complexOperation = (9 * (A * A * A * A)) + (16 * (B * B * B * B * B));

    outputFile << A.to_string() << "\n\n";
    outputFile << B.to_string() << "\n\n";
    outputFile << sum.to_string() << "\n\n";
    outputFile << diff.to_string() << "\n\n";
    outputFile << subA.to_string() << "\n\n";
    outputFile << tripleAminusDoubleB.to_string() << "\n\n";
    outputFile << product.to_string() << "\n\n";
    outputFile << ASquared.to_string() << "\n\n";
    outputFile << BSquared.to_string() << "\n\n";
    outputFile << complexOperation.to_string() << std::endl;

    outputFile.close();

    return 0;
}
