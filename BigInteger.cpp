/*
 Name - Vaishnavi Jaligama
 Student Id- 1936593
 Cruz id - vjaligam
 Course - CSE101
 Quarter - Winter 2024
 Professor - Mr. Patrick Tantalo
 Programming assignment - 6
 Due date - March 4th, 2024
 File name - BigInteger.cpp
*/
#include "BigInteger.h"
#include "List.h"

#include <cctype>
#include <cmath>
#include <stdexcept>

using namespace std;

const ListElement BASE  = 1000000000;  
const int         POWER = 9;           

void delZero(List* L) {
    for (L->moveFront(); L->length() > 0 && !L->peekNext(); L->eraseAfter()) {}
}


List tempMult(long s, List *b, int* ctr) {
    List L;
    long carry = 0;
    long temp = 0;
    
    b->moveBack();
    if (b->position() > 0) {
        do {
            temp = (b->peekPrev() * s) + carry;
            carry = temp / BASE;
            temp %= BASE;
            L.insertAfter(temp);
            b->movePrev();
        } while (b->position() > 0);
    }

    if (carry > 0) {
        L.insertAfter(carry);
    }

    L.moveBack();
    int i = 0;
    if (*ctr > 0) {
        do {
            L.insertAfter(0);
            i++;
        } while (i < *ctr);
    }

    return L;
}

void BigInteger::makeZero() {
    digits.clear();
    signum = 0;
}

void BigInteger::negate() {
    signum *= -1;
}

BigInteger::BigInteger() {
    signum = 0;
    digits = List();
}

BigInteger::BigInteger(long x) {
    signum = (x < 0) ? -1 : (x > 0) ? 1 : 0;
    if (x == 0) {
        digits.insertAfter(0);
    } else {
        if (x < 0) x = -x;
        do {
            digits.insertBefore(x % BASE);
            x /= BASE;
        } while (x > 0);
    }
}

BigInteger::BigInteger(std::string s) {
    if (s.empty()) {
        throw std::invalid_argument("BigInteger: Constructor: empty string");
    }

    signum = 1; 
    size_t start = 0; 
    if (s[0] == '+' || s[0] == '-') {
        signum = (s[0] == '-') ? -1 : 1;
        start = 1; 
        if (s.length() == 1) { 
            throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
        }
    }

    for (size_t i = start; i < s.length(); i++) {
        if (!isdigit(s[i])) {
            throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
        }
    }

    for (int i = s.length(); i > static_cast<int>(start); i -= POWER) {
        int len = (i - static_cast<int>(start) < POWER) ? i - static_cast<int>(start) : POWER;
        std::string numStr = s.substr(i - len, len);
        long num = std::stol(numStr, nullptr, 10);
        digits.insertAfter(num);
    }

    delZero(&digits); 
}



BigInteger::BigInteger(const BigInteger& N) {
    this->signum = N.signum;
    this->digits = N.digits;
}


int BigInteger::sign() const{
    return this->signum;
}

int BigInteger::compare(const BigInteger& N) const {
    if (signum != N.signum) {
        return signum > N.signum ? 1 : -1;
    } else if (signum == 0) {
        return 0;
    }
    
    const List& A = digits;
    const List& B = N.digits;
    int lengthDifference = A.length() - B.length();
    if (lengthDifference != 0) {
        return (lengthDifference > 0) ? signum : -signum;
    }
    
    List A_copy = A;
    List B_copy = B;
    A_copy.moveFront();
    B_copy.moveFront();
    
    while (A_copy.position() < A_copy.length() && B_copy.position() < B_copy.length()) {
        long aDigit = A_copy.peekNext();
        long bDigit = B_copy.peekNext();
        if (aDigit != bDigit) {
            return (aDigit > bDigit) ? signum : -signum;
        }
        A_copy.moveNext();
        B_copy.moveNext();
    }
    
    return 0;
}

BigInteger BigInteger::add(const BigInteger& N) const {
    BigInteger X = *this;
    BigInteger Y = N;
    BigInteger Z;

    // Handle cases where signs differ
    if (X.sign() > 0 && Y.sign() < 0) {
        Y.negate();
        return X.sub(Y);
    } else if (X.sign() < 0 && Y.sign() > 0) {
        X.negate();
        return Y.sub(X);
    } else if (X.sign() < 0 && Y.sign() < 0) {
        X.negate();
        Y.negate();
        Z = X.add(Y);
        Z.negate();
        return Z;
    }

    if (X > Y) {
        return Y.add(X);
    }

    List x = X.digits;
    List y = Y.digits;
    List z = Z.digits;

    long carry = 0;
    long temp = 0;

    x.moveBack();
    y.moveBack();
    for (; x.position() > 0 && y.position() > 0; x.movePrev(), y.movePrev()) {
    temp = carry + x.peekPrev() + y.peekPrev();
    carry = temp / BASE;
    temp %= BASE;
    z.insertAfter(temp);
}

    for (; y.position() > 0; y.movePrev()) {
    temp = carry + y.peekPrev();
    carry = temp / BASE;
    temp %= BASE;
    z.insertAfter(temp);
}
    if (carry > 0) {
        z.insertAfter(carry);
    }

    Z.signum = 1;
    Z.digits = z;
    return Z;
}

BigInteger BigInteger::sub(const BigInteger& N) const {
    BigInteger B = *this;
    BigInteger A = N;
    BigInteger C;
    List a = A.digits;
    List b = B.digits;
    List c = C.digits;

    if (A == B) {
        return C; 
    }
    if (A.sign() && !B.sign()) {
        A.negate();
        return A; 
    }
    if (!A.sign() && B.sign()) {
        return B;
    }
    if (A.sign() < 0 && B.sign() > 0) {
        B.negate();
        C = A.add(B);
        C.negate();
        return C;
    }
    if (A.sign() > 0 && B.sign() < 0) {
        A.negate();
        C = A.add(B);
        return C;
    }
    if (A.sign() < 0 && B.sign() < 0) {
        A.negate();
        B.negate();
        C = B.sub(A);
        C.negate();
        return C; 
    }
    if (A < B) {
        C = A.sub(B);
        C.negate();
        return C; 
    }
    a.moveBack();
    b.moveBack();
    long dist = 0;
    long temp = 0;

    for (int i = b.position(); i > 0; a.movePrev(), b.movePrev(), i--) {
        if (a.peekPrev() - dist < b.peekPrev()) {
            temp = a.peekPrev() + BASE - b.peekPrev() - dist;
            dist = 1;
        } else {
            temp = a.peekPrev() - b.peekPrev() - dist;
            dist = (a.peekPrev() - dist <= 0) ? 1 : 0;
        }
        c.insertAfter(temp);
    }

    for (; a.position() > 0; a.movePrev()) {
        if (a.peekPrev() - dist < 0) {
            temp = a.peekPrev() + BASE - dist;
            dist = 1;
        } else {
            temp = a.peekPrev() - dist;
            dist = (a.peekPrev() - dist <= 0) ? 1 : 0;
        }
        c.insertAfter(temp);
    }
    C.digits = c;
    delZero(&(C.digits));  
    C.signum = -1;  
    return C;
}

BigInteger BigInteger::mult(const BigInteger& N) const {
    BigInteger B = *this;
    BigInteger A = N;
    BigInteger C;

    List& a = A.digits;
    List& b = B.digits;
    int ctr = 0;

    a.moveBack();
    b.moveBack();

    if (a.length() > 0) {
        do {
            List temp = tempMult(a.peekPrev(), &b, &ctr);
            BigInteger T;
            T.signum = 1;
            T.digits = temp;
            C = C.add(T);
            a.movePrev();
            ctr++;
        } while (a.position() > 0);
    }

    C.signum = A.signum * B.signum;
    if (C.signum == 0 || (C.digits.length() == 1 && C.digits.front() == 0)) {
        C.signum = 0;
    }

    return C;
}

std::string BigInteger::to_string() {
    if (signum == 0) {
        return "0";
    }

    std::string out = signum == -1 ? "-" : "";
    digits.moveFront();
    while (digits.front() == 0 && digits.length() > 1) {
        digits.eraseAfter();
    }

    bool isFirstDigit = true;
    for (digits.moveFront(); digits.position() < digits.length(); digits.moveNext()) {
        std::string digitStr = std::to_string(digits.peekNext());
        if (!isFirstDigit) {
            digitStr = std::string(POWER - digitStr.length(), '0') + digitStr;
        }
        out += digitStr;
        isFirstDigit = false;
    }

    return out;
}

std::ostream& operator<<( std::ostream& stream, BigInteger N ) {
    return stream<<N.BigInteger::to_string();
}

bool operator==( const BigInteger& A, const BigInteger& B ) {
    int i = A.compare(B);
    return (i == 0) ? true : false;
}

bool operator<( const BigInteger& A, const BigInteger& B ) {
    int i = A.compare(B);
    return (i == -1) ? true : false;
}

bool operator<=( const BigInteger& A, const BigInteger& B ) {
    int i = A.compare(B);
    return ((i == 0) || (i == -1)) ? true : false;
}

bool operator>( const BigInteger& A, const BigInteger& B ) {
    int i = A.compare(B);
    return (i == 1) ? true : false;
}

bool operator>=( const BigInteger& A, const BigInteger& B ) {
    int i = A.compare(B);
    return ((i == 0) || (i == 1)) ? true : false;
}

BigInteger operator+( const BigInteger& A, const BigInteger& B ) {
    return A.add(B);
}

BigInteger operator+=( BigInteger& A, const BigInteger& B ) {
    BigInteger I = A.add(B);
    A.digits = I.digits;
    A.signum = I.signum;
    return A; 
}

BigInteger operator-( const BigInteger& A, const BigInteger& B ) {
    return A.sub(B);
}

BigInteger operator-=( BigInteger& A, const BigInteger& B ) {
    BigInteger I = A.sub(B);
    A.digits = I.digits;
    A.signum = I.signum;
    return A; 
}

BigInteger operator*( const BigInteger& A, const BigInteger& B ) {
    return A.mult(B);
}

BigInteger operator*=( BigInteger& A, const BigInteger& B ) {
    BigInteger I = A.mult(B);
    A.digits = I.digits;
    A.signum = I.signum;
    return A; 
}