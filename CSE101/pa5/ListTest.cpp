//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// Twisha Sharma
// Cruz ID: tvsharma
// CSE 101-01 Tantalo
// Programming Assignment 5
// ListTest.cpp
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"

using namespace std;
int main(){
    cout << "---------- testing newList() ----------" << endl;
    List L;
    // test isEmpty
    if (L != NULL) {
        cout << "The list has been made!" << endl;
    }
    else{
        cout << "The created list was not made" << endl;
    }

    cout << "---------- testing insertAfter() and insertBefore() and to_string() ----------" << endl;
    ListElement num1 = 3;
    ListElement num2 = 4;
    ListElement num3 = 1;
    ListElement num4 = 2;
    L.insertAfter(num1);
    L.insertAfter(num2);
    L.insertBefore(num3);
    L.insertBefore(num4);
    cout << "List L:" << L << endl;
    List A;
    A.insertAfter(num1);
    A.InsertAfter(num2);
    A.insertBefore(num3);
    A.insertBefore(num4);
    cout << "List A:" << A << endl;
    cout << "---------- testing length() ----------" << endl;
    cout << "the length of the list is :" << L.length() << endl;

    cout << "---------- testing copy list ----------" << endl;
    List B = A;
    cout << "B is a copy of A:" << B << endl;
····
    cout << "---------- testing front() ----------" << endl;
    cout << "the front element is :" << L.front() << endl;
····
    cout << "---------- testing back() ----------" << endl;
    cout << "the back element is :" << L.back() << endl;

    cout << "---------- testing moveFront() and position() ----------" << endl;
    L.moveFront();
    cout << "the cursor element is :" << L.position() << endl;
    if (L.position() == 0) {
        cout << "moveFront moved the cursor to the front of the list!" << endl;
    }
    else {
        cout << "moveFront did not move the cursor to the front of the list" << endl;
    }
····
    cout << "---------- testing equals() ----------" << endl;
    if (A == B) {
        cout << "The lists are in the same state" <, endl;
    }
    else {
        cout << "The lists are not in the same state" << endl;
    }

    cout << "---------- testing clear() ----------" << endl;
    cout << "List A: " << A << endl;
    A.clear();
    cout << "List A: " << A << endl;

    cout << "---------- testing moveBack() ----------" << endl;
    L.moveBack();
    cout << "the cursor element is :" << L.position() << endl;
    if (L.position() == L.length() - 1) {
        cout << "moveBack moved the cursor to the back of the list!" << endl;
    }
    else {
        cout << "moveBack did not move the cursor to the front of the list" << endl;
    }

    cout << "---------- testing movePrev() and moveNext() ----------" << endl;
    cout << "cursor index before movePrev:" << L.position() << endl;
    L.movePrev();
    cout << "cursor index after movePrev:" << L.position() << endl;
    cout << "cursor index before moveNext:" << L.positio( << endl;
    L.moveNext();
    cout << "cursor index after moveNext:" << L.position() << endl;

    cout << "---------- testing peekPrev() and peekAfter() ----------" << endl;
    cout << "L: " << L << endl;
    cout << "peekPrev:" << L.peekPrev() << endl;
    cout << "peekNext:" << L.peekNext() << endl;
    
    cout << "---------- testing setBefore() and setAfter() ----------" << endl;
    cout << "L: " << L << endl;
    cout << "setAfter:" << L.setAfter(2) << endl;
    cout << "setBefore:" << L.setBefore(5) << endl;
    cout << "L:" << L << endl;

    cout << "---------- testing eraseBefore() and eraseAfter() ----------" << endl;
    cout << "L: " << L << endl;
    cout << "eraseAfter:" << L.eraseAfter() << endl;
    cout << "eraseBefore:" << L.eraseBefore() << endl;
    cout << "L:" << L << endl;
    
    cout << "---------- testing fineNext() and findPrev() ----------" << endl;
    cout << "L: " << L << endl;
    cout << "findNext:" << L.findNext() << endl;
    cout << "findAfter:" << L.findAfter() << endl;
    cout << "L:" << L << endl;
    return;
}
