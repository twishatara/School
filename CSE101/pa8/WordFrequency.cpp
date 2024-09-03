//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// Twisha Sharma
// Cruz ID: tvsharma
// CSE 101-01 Tantalo
// Programming Assignment 7
// WordFrequency.cpp
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include "Dictionary.h"

using namespace std;

int main(int argc, char* argv[]) {
    ifstream in;
    ofstream out;
    size_t begin, end, len;
    string delim = " \t\\\"\',<.>/?;:[{]}|`~!@#$%^&*()-_=+0123456789";
    string token = "";
    string line = "";
    int val = 0;
    if( argc != 3 ){
        cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
        return(EXIT_FAILURE);
    }
    in.open(argv[1]);
    if( !in.is_open() ){
        cerr << "Unable to open file " << argv[1] << " for reading" << endl;
        return(EXIT_FAILURE);
   }

    out.open(argv[2]);
    if( !out.is_open() ){
        cerr << "Unable to open file " << argv[2] << " for writing" << endl;
        return(EXIT_FAILURE);
    }
    Dictionary A;
    while(getline(in, line) )  {
        len = line.length();
        begin = min(line.find_first_not_of(delim, 0),len);
        end = min(line.find_first_of(delim, begin), len);
        token = line.substr(begin, end-begin);
        while(token != "") {
            for (size_t i = 0; i < token.length(); i++) {
                token[i] = tolower(token[i]);
            }
            if (A.contains(token) == true) {
                val = A.getValue(token);
                val ++;
                A.setValue(token, val);
            }
            else {
                A.setValue(token, 1);
            }
            begin = min(line.find_first_not_of(delim, end+1),len);
            end = min(line.find_first_of(delim, begin), len);
            token = line.substr(begin, end-begin);
        }
    }
    out << A << endl;
    in.close();
    out.close();
    return(EXIT_SUCCESS);
}

