//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// Twisha Sharma
// Cruz ID: tvsharma
// CSE 101-01 Tantalo
// Programming Assignment 4
// MatrixTest.c
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include"Matrix.h"
     
int main(void){
    int n = 5;
    Matrix A = newMatrix(n);
    Matrix B = newMatrix(n);
    Matrix C, D, E, F, G, H;
    printf("testing printMatrix()\n");
    printMatrix(stdout, A);
    printf("\n");
    printMatrix(stdout, B);
    printf("\n");
    printf("testing changeEntry()\n");
    changeEntry(A, 1,1,1);
    changeEntry(A, 1,2,2);
    changeEntry(A, 1,3,3);
    changeEntry(A, 2,1,4);
    changeEntry(A, 2,2,5);
    changeEntry(B, 1,1,1);
    changeEntry(B, 1,2,0);
    changeEntry(B, 1,3,1);
    changeEntry(B, 2,1,0);
    changeEntry(B, 2,2,1);
    printMatrix(stdout, A); 
    printMatrix(stdout, B);
    printf("testing scalarMult()\n");
    C = scalarMult(3, A);
    printMatrix(stdout, C);
    printf("\n");
    printf("tesing sum()\n");
    D = sum(A, B);
    printMatrix(stdout, D);
    printf("\n");
    printf("testing diff()\n");
    E = diff(A, B);
    printMatrix(stdout, E);
    printf("\n");
    printf("testing transpose()\n");
    F = transpose(B);
    printMatrix(stdout, F);
    printf("\n");
    printf("testing product()\n");
    G = product(B, B);
    printMatrix(stdout, G);
    printf("\n");
    printf("testing copy()\n");
    H = copy(A);
    printMatrix(stdout, H);
    printf("\n");
    printf("testing equals()");
    if (equals(A, A) == 1)  {
        printf("Matrix A is the same as Matrix A\n");
    }
    else {
        printf("Matrix A is not the same as Matrix A\n");
    }
    printf("testing makeZero()\n");
    makeZero(A);
    printMatrix(stdout, A);
    printf("\n");
    freeMatrix(&A);
    freeMatrix(&B);
    freeMatrix(&C);
    freeMatrix(&D);
    freeMatrix(&E);
    freeMatrix(&F);
    freeMatrix(&G);
    freeMatrix(&H);
    return 0;
}
