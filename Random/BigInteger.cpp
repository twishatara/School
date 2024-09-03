//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// Twisha Sharma
// Cruz ID: tvsharma
// CSE 101-01 Tantalo
// Programming Assignment 5
// BigInteger.cpp
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#include <iostream>
#include <string>
#include <stdexcept>
#include <cstddef>
//#include "List.h"
#include "BigInteger.h"

#define power 9
#define base 1000000000

// Class Constructors & Destructors ----------------------------------------

// BigInteger()
// Constructor that creates a new BigInteger in the zero state:·
// signum=0, digits=().
BigInteger::BigInteger() {
    signum = 0;
    List digits;
}

// BigInteger()
// Constructor that creates a new BigInteger from the string s.
// Pre: s is a non-empty string consisting of (at least one) base 10 digit
// {0,1,2,3,4,5,6,7,8,9}, and an optional sign {+,-} prefix.
BigInteger::BigInteger(std::string s) {
    std::string mini;
    size_t incomp = (s.length() % power);
    size_t index = 0;
    if (s == "") {
        throw std::invalid_argument("BigInteger: Constructor: empty string");
    }
    std::size_t found = s.find_first_not_of("+-0123456789");
    if (found != std::string::npos) {
        throw std::invalid_argument("BigInteger: Constructor: non-numeric string");
    }
    //std::cout << "index 0 " << s[0] << std::endl;
    if (s[0] == '-') {
        signum = -1;
        index = 1;
        incomp = ((s.length() - 1) % power);
    }
    else if (s[0] == '+') {
        signum = 1;
        index = 1;
        incomp = ((s.length() - 1) % power);
    }
    else {
        signum = 1;
        //std::cout << "string length: " << s.length() << std::endl;
        incomp = ((s.length() - 1) % power);
        //std::cout << "incomp: " << incomp << std::endl;
    }
    for (size_t i = index; i <= s.length() - 1; i = i) {
        if (digits.position() == (int) s.length()) {
            mini = s.substr(i, incomp);
            long v = std::stol(mini);
            digits.insertBefore(v);
            i += incomp;
        }
        else {
            mini = s.substr(i, power);
            long v = std::stol(mini);
            digits.insertBefore(v);
            i += power;
        }
    }
}

// BigInteger()
// Constructor that creates a copy of N.
BigInteger::BigInteger(const BigInteger& N) {
    digits = N.digits;
    signum = N.signum;
}

// Optional Destuctor
// ~BigInteger()
// ~BigInteger();


// Access functions --------------------------------------------------------

// sign()
// Returns -1, 1 or 0 according to whether this BigInteger is positive,·
// negative or 0, respectively.
int BigInteger::sign() const {
    return signum;
}

// compare()
// Returns -1, 1 or 0 according to whether this BigInteger is less than N,
// greater than N or equal to N, respectively.
int BigInteger::compare(const BigInteger& N) const {
    //std::cout << "signum: " << signum << std::endl;
    //std::cout << "N.signum: " << N.signum << std::endl;
    if (signum != N.signum) { // check sign
        if (signum > N.signum) {
            return 1;
        }
        else {
            return -1;
        }
    }
    else {
        if (digits.length() != N.digits.length()) { // check length
            if (digits.length() > N.digits.length()) {
                return 1;
            }
            else {
                return -1;
            }
        }
        else if ((signum != N.signum) && (digits.length() == N.digits.length())) {
            for (int i = 0; i <= digits.length(); i++) {
                for (int j = 0; j <= N.digits.length(); j++) {
                    if (i > j) {
                        return 1;
                    }
                    else if (i < j) {
                        return -1;
                    }
                }
            }
        }
    }
    return 0;
}

// Manipulation procedures -------------------------------------------------

// makeZero()
// Re-sets this BigInteger to the zero state.
void BigInteger::makeZero() {
    digits.moveFront();
    while (digits.length() > 0) {
        digits.eraseAfter();
    }
}

// negate()
// If this BigInteger is zero, does nothing, otherwise reverses the sign of·
// this BigInteger positive <--> negative.·
void BigInteger::negate() {
    if (signum == -1) {
        signum = 1;
    }
    if (signum == 1) {
        signum = -1;
    }
}


// BigInteger Arithmetic operations ----------------------------------------

void sumList(List& res, List A, List B, int sgn) {
    A.moveBack();
    B.moveBack();
    ListElement i;
    ListElement j;
    ListElement k;
    while (A.position() > 0 || B.position() > 0) { // parse through the longest list
        if (sgn == 1) {
            if (A.position() == 0) {
                k = B.movePrev();
            }
            else if (B.position() == 0) {
                k = A.movePrev();
            }
            else {
                i = A.movePrev();
                j = B.movePrev();
                k = i + j;
            }
            res.insertAfter(k);
        }
        else if (sgn == -1) {
            if (A.position() == 0) {
                k = B.movePrev();
                k = -k;
            }
            else if (B.position() == 0) {
                k = A.movePrev();
            }
            else {
                i = A.movePrev();
                j = B.movePrev();
                k = i - j;
            }
            res.insertAfter(k);
        }
    }
}

void normalizeList(List& L) {
    int t = 0;
    int c = 0;
    bool carry = false;
    List newList;
    L.moveBack();
    for (int i = L.length(); i != ((L.length() - 1) % power); i--) { //while ((L.position()) > 0) {
        t = L.movePrev();
        if (carry == true) {
            c = t / base; // carryover number
            t += c;
            carry = false;
        }
        if (t > base) { // carry is nonzero
            t = t % base;
            carry = true;
            //newList.insertBefore(t);
        }
        newList.insertAfter(t);
    }
    if (c > 0) {
        newList.insertAfter(c);
    }
}

// add()
// Returns a BigInteger representing the sum of this and N.
BigInteger BigInteger::add(const BigInteger& N) const {
    BigInteger A;
    bool copycheck = false;
    bool Ncopycheck = false;
    BigInteger copy = *this;
    copy.digits = this->digits;
    BigInteger Ncopy = N;
    Ncopy.digits = N.digits;
    copy.signum = this->signum;
    Ncopy.signum = N.signum;
    // check if the signs of the lists are the same
    if (Ncopy.signum == copy.signum) {
        A.signum = copy.signum;
    }
    else {
        if (copy.signum < Ncopy.signum) { // if copy needs to be negated
            copy.negate();
            copycheck = true;
        }
        else if (copy.signum > Ncopy.signum) { // if Ncopy needs to be negated
            Ncopy.negate();
            Ncopycheck = true;
        }
        if (copy < Ncopy) { // if a is less than b
            A.signum = Ncopy.signum;
        }
        else if (copy > Ncopy) { // if a is greater than b
            A.signum = copy.signum;
        }
        else { // if a equals b
            A.signum = 0;
            return A;
        }
        if (copycheck == true) {
            copy.negate();
            copycheck = false;
        }
        else if (Ncopycheck == true) {
            Ncopy.negate();
            Ncopycheck = false;
        }
    }
    List sum;
    sumList(sum, copy.digits, Ncopy.digits, 1);
    normalizeList(sum);
    A.digits = sum;
    return A;
}

/*

// sub()
// Returns a BigInteger representing the difference of this and N.
BigInteger BigInteger::sub(const BigInteger& N) const {
    BigInteger A;
    bool copycheck = false;
    bool Ncopycheck = false;
    BigInteger copy = *this;
    copy.digits = this->digits;
    BigInteger Ncopy = N;
    Ncopy.digits = N.digits;
    copy.signum = this->signum;
    Ncopy.signum = N.signum;
    // check if the signs of the lists are the same
    if (Ncopy.signum == copy.signum) {
        A.signum = copy.signum;
    }
    else {
        if (copy.signum < Ncopy.signum) { // if copy needs to be negated
            copy.negate();
            copycheck = true;
        }
        else if (copy.signum > Ncopy.signum) { // if Ncopy needs to be negated
            Ncopy.negate();
            Ncopycheck = true;
        }
        if (copy < Ncopy) { // if a is less than b
            A.signum = Ncopy.signum;
        }
        else if (copy > Ncopy) { // if a is greater than b
            A.signum = copy.signum;
        }
        else { // if a equals b
            A.signum = 0;
            return A;
        }
        if (copycheck == true) {
            copy.negate();
            copycheck = false;
        }
        else if (Ncopycheck == true) {
            Ncopy.negate();
            Ncopycheck = false;
        }
    }
    List sum;
    sumList(sum, copy.digits, Ncopy.digits, 1);
    //std::cout << "sum list" << sum  << std::endl;
    normalizeList(sum);
    //std::cout << "post normalize sum" << sum << std::endl;
    //std::cout << "test add" << std::endl;
    A.digits = sum;
    return A;
}


old add func: 
    BigInteger A;
    bool copycheck = false;
    bool Ncopycheck = false;
    BigInteger copy = *this;
    BigInteger Ncopy = N;
    if (Ncopy.signum == copy.signum) {
        A.signum = copy.signum;
        sumList(A.digits, copy.digits, Ncopy.digits, 1); // 1 because either way the num value "increases" e                        ven if neg
    }
    else {
        if (copy.signum < Ncopy.signum) { // if copy needs to be negated
            copy.negate();
            copycheck = true;
        }
        else if (copy.signum > Ncopy.signum) { // if Ncopy needs to be negated
            Ncopy.negate();
            Ncopycheck = true;
        }
        if (copy < Ncopy) { // if a is less than b
            A.signum = Ncopy.signum;
            sumList(A.digits, copy.digits, Ncopy.digits, -1);
        }
        else if (copy > Ncopy) { // if a is greater than b
            A.signum = copy.signum;
            sumList(A.digits, copy.digits, Ncopy.digits, -1);
        }
        else { // if a equals b
            A.signum = 0;
            return A;
        }
        if (copycheck == true) {
            copy.negate();
        }
        else if (Ncopycheck == true) {
            Ncopy.negate();
        }
    }
    normalizeList(A.digits);
    return A;


// mult()
// Returns a BigInteger representing the product of this and N.·
BigInteger BigInteger::mult(const BigInteger& N) const {
    size_t m = 0;
    BigInteger mull;
    BigInteger copy = *this;
    BigInteger Ncopy = N;
    ListElement i = copy.digits.movePrev();
    ListElement j = Ncopy.digits.movePrev();
    m = i * j;
    mull.digits.insertBefore(m);
    if (N.signum == signum) {
        mull.signum = signum;
    }
    if (signum > N.signum) {
        mull.signum = -1;
    }
    if (N.signum > signum) {
        mull.signum = -1;
    }
    return mull;
}
*/

// Other Functions ---------------------------------------------------------

// to_string()
// Returns a string representation of this BigInteger consisting of its
// base 10 digits. If this BigInteger is negative, the returned string·
// will begin with a negative sign '-'. If this BigInteger is zero, the
// returned string will consist of the character '0' only.
std::string BigInteger::to_string() {
    std::string s;
    std::string s1 = "";
    std::string s2 = "";
    std::string z = "";
    digits.moveFront();
    if (signum == -1) {
        s += '-';
    }
    for (int i = 1; i <= power; i++) {
        z += "0";
    }
    while (digits.position() != digits.length()) {
        ListElement pass = digits.moveNext();
        if (pass == 0 && digits.position() != 1) {
            s += z;
            continue;
        }
        s1 = std::to_string(pass); // converts from long to string·
        if (s1.length() < power && digits.position() != 1) {
            for (size_t i = 0; i < power - s1.length(); i++) {
                s2 += "0";
            }
            s += s2;
        }
        s += std::to_string(pass);
    }
    return s;
}

// Overriden Operators -----------------------------------------------------

// operator<<()
// Inserts string representation of N into stream.
std::ostream& operator<<( std::ostream& stream, BigInteger N ) {
    return stream << N.BigInteger::to_string();
}

// operator==()
// Returns true if and only if A equals B. 
bool operator==( const BigInteger& A, const BigInteger& B ) {
    if (A.compare(B) == 0) {
        return true;
    }
    return false;
}

// operator<()
// Returns true if and only if A is less than B. 
bool operator<( const BigInteger& A, const BigInteger& B ) {
    if (A.compare(B) == -1) {
        return true;
    }
    return false;
}

// operator<=()
// Returns true if and only if A is less than or equal to B. 
bool operator<=( const BigInteger& A, const BigInteger& B ) {
    if (A.compare(B) == -1 || 0) {
        return true;
    }
    return false;
}

// operator>()
// Returns true if and only if A is greater than B. 
bool operator>( const BigInteger& A, const BigInteger& B ) {
    if (A.compare(B) == 1) {
        return true;
    }
    return false;
}

// operator>=()
// Returns true if and only if A is greater than or equal to B. 
bool operator>=( const BigInteger& A, const BigInteger& B ) {
    if (A.compare(B) == 1 || 0) {
        return true;
    }
    return false;
}

// operator+()
// Returns the sum A+B. 
BigInteger operator+( const BigInteger& A, const BigInteger& B ) {
    return A.add(B);
}

// operator+=()
// Overwrites A with the sum A+B. 
BigInteger operator+=( BigInteger& A, const BigInteger& B ) {
    A = A.add(B);
    return A;
}
/*
// operator-()
// Returns the difference A-B. 
BigInteger operator-( const BigInteger& A, const BigInteger& B ) {
    return A.sub(B);
}

// operator-=()
// Overwrites A with the difference A-B. 
BigInteger operator-=( BigInteger& A, const BigInteger& B ) {
    A = A.sub(B);
    return A;
}

// operator*()
// Returns the product A*B. 
BigInteger operator*( const BigInteger& A, const BigInteger& B ) {
    return A.mult(B);
}

// operator*=()
// Overwrites A with the product A*B. 
BigInteger operator*=( BigInteger& A, const BigInteger& B ) {
    A = A.mult(B);
    return A;
}
*/
