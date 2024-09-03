//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// Twisha Sharma
// Cruz ID: tvsharma
// CSE 101-01 Tantalo
// Programming Assignment 7
// DictionaryTest.cpp
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#include <iostream>
#include <string>
#include <stdexcept>
#include <cstddef>
#include "Dictionary.h"

using namespace std:

int main() {
    string s;
    int x;
    string S[] = {"one", "two", "three", "four", "five"}
    Dictionary A;

    // testing Dictionary constructor
    if (A != NULL) {
        cout << "The dictionary has been made!" << endl;
    }
    else{
        cout << "The dictionary was not made" << endl;
    }

    // testing setValue()
    for (int i = 0; i < 5; i ++) {
        A.setValue(S[i], i + 1);
    }

    // testing operator=
    B = A;
    cout << A << endl;
    cout << b << endl;

    // testing equals()
    if (A.equals(B) == true) {
        cout << "it works!" << endl;
    }
    else {
        cout << "it didnt work" << endl;
    }

    // testing copy constructor
        Dictionary C = B;

    // testing size()
    cout << "Dictionary A size" << A.size() << endl;

    // testing contains
    if (contains("one") == true) {
        cout << "contains works!" << endl;
    }
    else {
        cout << "contains does not work" << endl;
    }

    // testing getValue()
    cout << "the value at the key is" << A.getValue("one") << endl;

    // testing hasCurrent()
    if (A.hasCurrent() == true) {
        cout << "the current iterator is defined" << endl;
    }
    else {
        cout << "the current iterator is not defined" << endl;
    }

    // testing curentKey()
    cout << "this is the current key of the A dictionary" << A.currentKey() << endl;

    // testing currentVal()
    cout << "this is the current value of the A dictionary" << A.currentVal() << endl;

    // tesing remove()
    cout << "This is the A dictionary" << A << endl;
    A.remove("one");
    cout << "This is the new A dictionary" << A << endl;

    // testing begin()
    cout << "A current key:" << A.currentKey() << endl;
    A.begin();
    cout << "A current key:" << A.currentKey() << endl;

    // testing end()
    cout << "A current key:" << A.currentKey() << endl;
    A.end();
    cout << "A curremt key:" << A.currentKey() << endl;

    // testing next()
    cout << "A current key:" << A.currentKey() << endl;
    A.next();
    cout << "A curremt key:" << A.currentKey() << endl;

    // testing prev()
    cout << "A current key:" << A.currentKey() << endl;
    A.prev();
    cout << "A curremt key:" << A.currentKey() << endl;
    return;
}


