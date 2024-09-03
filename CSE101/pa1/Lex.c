//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// Twisha Sharma
// Cruz ID: tvsharma
// CSE 101-01 Tantalo
// Programming Assignment 1
// Lex.c
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
#include "List.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int main(int argc, char **argv) {
    if (argc != 3) {
        printf("User Input Error: Please specify input and output file\n");
        exit(EXIT_FAILURE);
    }
    FILE *in = fopen(argv[1], "r");
    FILE *out = fopen(argv[2], "w");
    char buf[500];
    int linecount = 0;
    while(fgets(buf, 500, in) != NULL) { // loop through fgets(), fill the buffer from infile char when the buffer is full to 500 (random big num)
        linecount ++; // increase linecount
    }
    fseek(in, 0, SEEK_SET);
    char **A = (char **) malloc(linecount * sizeof(char *)); //create and set aside memory for an array
    for (int count = 0; count < linecount; count ++) {
        fgets(buf, 500, in);
        A[count] = (char *) malloc((strlen(buf) + 1) *  sizeof(char));
        strncpy(A[count], buf, strlen(buf) + 1); // copys the char from the buf to the destination 'A' array
    }
    List L = newList();
    for (int i = 0; i < linecount; i++) {
        bool cb = false;
        moveFront(L);
        while(index(L) >= 0) {
            int x = get(L);
            if (strcmp(A[i], A[x]) < 0) {
                cb = true;
                insertBefore(L, i);
                break;
            }
            moveNext(L);
        }
        if (cb == false) {
            append(L, i);
        }
    }
    moveFront(L);
    while (index(L) >= 0) {
        int x = get(L);
        fprintf(out, "%s", A[x]);
        moveNext(L);
    }
    for (int num = 0; num < linecount; num ++) {
        free(A[num]);
        A[num] = NULL;
    }
    free(A);
    A = NULL;
    freeList(&L);
}
