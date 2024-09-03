//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// Twisha Sharma
// Cruz ID: tvsharma
// CSE 101-01 Tantalo
// Programming Assignment 4
// Sparse.c
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "List.h"
#include "Matrix.h"

int main(int argc, char* argv[]) {
    int a, b, c, e, f;
    double g;
    Matrix C, D, E, F, G, H, I, J;
    if (argv[1] == NULL || argv[2] == NULL) {
        printf("User Input Error: Please specify input and output file\n");
        exit(EXIT_FAILURE);
    }
    FILE *in = fopen(argv[1], "r");
    FILE *out = fopen(argv[2], "w");
    fscanf(in, "%d %d %d", &a, &b, &c); 
    Matrix A = newMatrix(a);
    Matrix B = newMatrix(a);
    for (int i = 1; i <= b; i++) {
        fscanf(in, "%d %d %lf", &e, &f, &g);
        changeEntry(A, e, f, g);
    }
    for (int i = 1; i <= c; i++) {
        fscanf(in, "%d %d %lf", &e, &f, &g);
        changeEntry(B, e, f, g);
    }
    // A
    fprintf(out,"A has %d non-zero entries:\n", NNZ(A));
    printMatrix(out, A);
    fprintf(out, "\n");
    // B
    fprintf(out,"B has %d non-zero entries:\n", NNZ(B));
    printMatrix(out, B);
    fprintf(out, "\n");
    // 1.5 * A
    fprintf(out,"(1.5)*A =\n");
    C = scalarMult(1.5, A);
    printMatrix(out, C);
    fprintf(out, "\n");
    // A + B
    fprintf(out, "A+B =\n");
    D = sum(A, B);
    printMatrix(out, D);
    fprintf(out, "\n");
    // A + A
    fprintf(out, "A+A =\n");
    E = sum(A, A);
    printMatrix(out, E);
    fprintf(out, "\n");
    // B - A
    fprintf(out, "B-A =\n");
    F = diff(B, A);
    printMatrix(out, F);
    fprintf(out, "\n");
    // A - A
    fprintf(out, "A-A =\n");
    G = diff(A, A);
    printMatrix(out, G);
    fprintf(out, "\n");
    // Transpose(A)
    fprintf(out, "Transpose(A) =\n");
    H = transpose(A);
    printMatrix(out, H);
    fprintf(out, "\n");
    // A * B
    fprintf(out, "A*B = \n");
    I = product(A, B);
    printMatrix(out, I); 
    fprintf(out, "\n");
    // B * B
    fprintf(out, "B*B = \n");
    J = product(B, B);
    printMatrix(out, J);
    fprintf(out, "\n");
    freeMatrix(&A);
    freeMatrix(&B);
    freeMatrix(&C);
    freeMatrix(&D);
    freeMatrix(&E);
    freeMatrix(&F);
    freeMatrix(&G);
    freeMatrix(&H);
    freeMatrix(&I);
    freeMatrix(&J);
    fclose(in);
    fclose(out);
    return 0;
}
