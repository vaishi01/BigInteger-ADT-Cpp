

# BigInteger-ADT-Cpp


Welcome to **BigInteger-ADT-Cpp**, a C++ implementation of a BigInteger Abstract Data Type (ADT) designed to perform arithmetic operations on arbitrarily large signed integers. The BigInteger ADT handles integers far beyond the limits of built-in data types, making it ideal for projects involving extremely large numbers. Using custom base-10 digit manipulation, this ADT offers precise arithmetic for numbers as large as you can imagine!

## Features

- **Arbitrary Precision Arithmetic**: Supports large signed integers that can’t be handled by built-in types like `int` or `long`.
- **Efficient List-Based Representation**: Digits of the number are stored in a `List` of longs, allowing for high-performance arithmetic operations.
- **Base-10 Grouping**: Leverages base-100 up to base-1,000,000,000 for efficient calculations and seamless base conversion.
- **Operations**:
  - Addition and subtraction with carry and borrow normalization
  - Multiplication using vector-like operations
  - Full suite of comparison operators (`==`, `<`, `<=`, `>`, `>=`)
  - Overloaded operators (`+`, `-`, `*`, `+=`, `-=`, `*=`)
- **String Conversion**: Easily converts between `BigInteger` and human-readable string format.




## Installation

1. Clone the repository:
   ```bash
   git clone git@github.com:vaishi01/BigInteger-ADT-Cpp.git
   cd BigInteger-ADT-Cpp
   ```

2. Compile the project:
   ```bash
   make
   ```

3. Run the client:
   ```bash
   ./Arithmetic input.txt output.txt
   ```

Make sure you have a C++11 (or later) compatible compiler installed on your machine.

## Usage

### BigInteger Representation

The `BigInteger` class encapsulates two main pieces of data:
- **Sign**: An `int` representing the sign (1 for positive, -1 for negative, and 0 for zero).
- **Magnitude**: A `List` of non-negative long integers representing the digits in a base `b`, where `b = 10^p`, and `1 <= p <= 9`.

## Functionality

Here’s a breakdown of the available operations and how they work:

- **Addition/Subtraction**: Handles carry and borrow in base-10 (or base-b) arithmetic. A borrow in subtraction is treated as a negative carry.
- **Multiplication**: Multiplies each digit of one `BigInteger` with each digit of another and uses carry to normalize the result.
- **Comparison**: Uses the `compare()` function to implement comparison operators, allowing `BigInteger` objects to be compared like regular integers.
- **Conversion**: Converts a `BigInteger` to and from its string representation, making it easy to work with in human-readable formats.

## Helper Functions

The following helper functions operate directly on the `List` structure to handle the underlying arithmetic:

- **negateList(List& L)**: Changes the sign of each integer in the list.
- **sumList(List& S, List A, List B, int sgn)**: Adds or subtracts lists `A` and `B`, depending on the sign.
- **normalizeList(List& L)**: Normalizes the list by carrying and borrowing digits, ensuring all elements are valid base-b digits.
- **shiftList(List& L, int p)**: Multiplies the list by `base^p` by prepending zero digits.
- **scalarMultList(List& L, ListElement m)**: Multiplies each element of the list by a scalar value.

These functions help perform core arithmetic operations while keeping the code modular and maintainable.

## Testing

A suite of unit tests is included in `BigIntegerTest.cpp` and `ListTest.cpp`. To run the tests:

```bash
make test
```

You can add your own test cases to ensure that all edge cases are handled effectively.

## License

This project is licensed under the MIT License. 
