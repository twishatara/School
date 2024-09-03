//-----------------------------------------------------------------------------------------------------    -
//-----------------------------------------------------------------------------------------------------    -
// Twisha Sharma
// Cruz ID: tvsharma
// CSE 101-01 Tantalo
// Programming Assignment 5
// Shuffle.cpp
//-----------------------------------------------------------------------------------------------------    -
//-----------------------------------------------------------------------------------------------------    -
#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"

using namespace std;

void shuffle(List& D) {
    int l = D.length();
    int split = l / 2;
    int num = 0;
    int flag = 0;
    int val1 = 0;
    int val2 = 0;
    List one;
    List two;
    D.moveFront();
    if (l % 2 == 0) {
        for (int i = 1; D.position() != split; i ++) {
            num = D.moveNext();
            one.insertBefore(num);
        }
        for (int i = 1; D.position() != l; i++) {
            flag = D.moveNext();
            two.insertBefore(flag);
        }
        D.moveFront();
        D.clear();
        one.moveFront();
        two.moveFront();
        while ((one.position() != one.length()) && (two.position() != two.length())) {
            val1 = two.moveNext();
            D.insertBefore(val1);
            val2 = one.moveNext();
            D.insertBefore(val2);
        }
    }
    else {
        for (int i = 1; D.position() != split; i ++) {
            num = D.moveNext();
            one.insertBefore(num);
        }
        for (int i = 1; D.position() < l; i++) {
            flag = D.moveNext();
            two.insertBefore(flag);
        }
        D.moveFront();
        D.clear();
        one.moveFront();
        two.moveFront();
        while (two.position() != two.length()) {
            val1 = two.moveNext();
            D.insertBefore(val1);
            if (one.position() != one.length()) {
                val2 = one.moveNext();
                D.insertBefore(val2);
            }
        }
    }
}


// split the list in half
// move the cursor to the font
// append first half to one list and other half to another
// take both those lists and append the original list in alternating order

int main(int argc, char *argv[]) {
    int count = 0;
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <decksize number> " << endl;
        return(EXIT_FAILURE);
    }
    int decksize = stoi(argv[1]);
    cout << "deck size       shuffle count" << endl;
    cout << "------------------------------" << endl;
    for (int j = 1; j <= decksize; j++) {
        List D;
        count = 0;
        for (int i = 0; i < j; i++) {
            D.insertBefore(i);
        }
        List A = D;
        shuffle(D);
        count ++;
        while (!(A==D)) {
            shuffle(D);
            count ++;
        }
        cout << j << "               " << count << endl;
    }
}
