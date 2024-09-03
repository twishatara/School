//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// Twisha Sharma
// Cruz ID: tvsharma
// CSE 101-01 Tantalo
// Programming Assignment 4
// Matrix.c
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
#include "Matrix.h"
#include "List.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// structs ---------------------------------------------------------------------------------------------

// private EntryObj type
typedef struct EntryObj {
    double data;
    int col;
} EntryObj;

// private MatrixObj type
typedef struct MatrixObj{
    List *arr;
    int size; 
    int NNZ;
} MatrixObj;

// Constructors-Destructors ---------------------------------------------------------------------------

Entry newEntry(double data, int col) {
    Entry E = malloc(sizeof(EntryObj));
    if (E == NULL) {
        return NULL;
    }
    E->data = data;
    E->col = col;
    return E;
}

// Returns a reference to a new nXn Matrix object in the zero state.
Matrix newMatrix(int n) {
    Matrix M = calloc(1, sizeof(MatrixObj));
    if (M == NULL) {
        return NULL;
    }
    M->arr = (List *) calloc(n + 1, sizeof(List));
    for (int i = 0; i <= n; i ++) {
        M->arr[i] = newList();
    }
    // One too many times
    M->size = n;
    M->NNZ = 0;
    return M;
}

void freeEntry(Entry *pE) {
    if (pE != NULL && *pE != NULL) {
        free(*pE);
        *pE = NULL;
    }
}

// Frees heap memory associated with *pM, sets *pM to NULL.
void freeMatrix(Matrix* pM) {
    if (pM != NULL && *pM != NULL) {
        makeZero(*pM);
        for (int i = 0; i <= (*pM)->size; i++) {
            freeList(&((*pM)->arr[i])); // free everything inside the array
        }
        free((*pM)->arr); // free list container
        (*pM)->arr = NULL;
        free(*pM); // free matrix container
        *pM = NULL;
    }
}

// Access functions ---------------------------------------------------------------------------------- 

// Return the size of square Matrix M.
int size(Matrix M) {
    if (M == NULL) {
        printf("Matrix Error: calling size() on a NULL matrix refrence\n");
        exit(EXIT_FAILURE);
    }
    return (M->size);
}

// Return the number of non-zero elements in M.
int NNZ(Matrix M) {
    if (M == NULL) {
        printf("Matrix Error: calling NNZ() on a NULL matrix refrence\n");
        exit(EXIT_FAILURE);
    }
    return (M->NNZ);
}

// Return true (1) if matrices A and B are equal, false (0) otherwise.
int equals(Matrix A, Matrix B) {
    if (A == NULL) {
        printf("Matrix Error: calling equals() on a NULL matrix A refrence\n");
        exit(EXIT_FAILURE);
    }
    if (B == NULL) {
        printf("Matrix Error: calling equals() on a NULL matrix B refrence\n");
        exit(EXIT_FAILURE);
    }
    if (A == B) {
        return (1);
    }
    if (A->size != B->size || A->NNZ != B->NNZ) {
        return (0); // return false
    }
    for (int i = 1; i <= A->size; i++) {
        moveFront(A->arr[i]);
        moveFront(B->arr[i]);
        while (index(A->arr[i]) >= 0 || index(B->arr[i]) >= 0) {
            if (length(A->arr[i]) != length(B->arr[i])) {
                return (0);
            }
            Entry x = (Entry) get(A->arr[i]);
            Entry y = (Entry) get(B->arr[i]);
            if (x->data != y->data) {
                return (0); // return false
            }
            if (x->col != y->col) {
                return (0); // return false
            }
            moveNext(A->arr[i]);
            moveNext(B->arr[i]);
        }
    }
    return (1); // return true
}

// Manipulation procedures -----------------------------------------------------------------------------

// Re-sets M to the zero Matrix state.
void makeZero(Matrix M) {
    if (M == NULL) {
        printf("Matrix Error: calling makeZero() on a NULL matrix refrence\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 1; i <= M->size; i++) {
        while(index(M->arr[i]) >= 0) {
            Entry k = (Entry) get(M->arr[i]); 
            freeEntry(&k);
            moveNext(M->arr[i]);
        }
        clear(M->arr[i]);
    }
    M->NNZ = 0;
}

// Changes the ith row, jth column of M to the value x.
// Pre: 1<=i<=size(M), 1<=j<=size(M)
void changeEntry(Matrix M, int i, int j, double x) {
    if (M == NULL) {
        printf("Matrix Error: calling changeEntry() on a NULL matrix refrence\n");
        exit(EXIT_FAILURE);
    }
    if (i < 1 || i > size(M)) { // if ith row is not in range
        printf("Matrix Error: calling changeEntry() on out of range row \n");
        exit(EXIT_FAILURE);
    }
    if (j < 1 || j > size(M)) { // if jth col is not in range
        printf("Matrix Error: calling changeEntry() on out of range col \n");
        exit(EXIT_FAILURE);
    }
    moveFront(M->arr[i]);
    while (index(M->arr[i]) >= 0) {
        Entry r = (Entry) get(M->arr[i]);
        if ((r->col == j) && (x == 0)) {
            freeEntry(&r);
            delete(M->arr[i]);
            M->NNZ --;
            return;
        }
        if ((r->col > j) && (x != 0)) {
            Entry e = newEntry(x, j);
            insertBefore(M->arr[i], e);
            M->NNZ ++;
            return;
        }
        if ((x != 0) && (r->col == j)) {
            r->data = x;
            return; 
        }
        moveNext(M->arr[i]);
    }
    if (x != 0) {
        Entry u = newEntry(x, j);
        append(M->arr[i], u); 
        M->NNZ ++;
    }
    return;
}

// Matrix Arithmetic operations ------------------------------------------------------------------------

// Returns a reference to a new Matrix object having the same entries as A.
Matrix copy(Matrix A) {
    if (A == NULL) {
        printf("Matrix Error: calling copy() on a NULL matrix refrence\n");
        exit(EXIT_FAILURE);
    }
    int n = size(A);
    Matrix B = newMatrix(n);
    B->NNZ = NNZ(A);
    for (int i = 1; i < A->size; i++) {
        moveFront(A->arr[i]);
        while (index(A->arr[i]) >= 0) {
            Entry y = (Entry) get(A->arr[i]);
            Entry k = newEntry(y->data, y->col);
            //insertBefore(B->arr[i], k);
            append(B->arr[i], k);
            moveNext(A->arr[i]);
        }
    }
    return (B);
}

// Returns a reference to a new Matrix object representing the transpose
// of A.
Matrix transpose(Matrix A) {
    if (A == NULL) {
        printf("Matrix Error: calling transpose() on a NULL matrix refrence\n");
        exit(EXIT_FAILURE);
    }
    int n = size(A);
    Matrix B = newMatrix(n);
    for (int i = 1; i <= A->size; i++) {
        moveFront(A->arr[i]);
        while (index(A->arr[i]) >= 0) {
            Entry v = (Entry) get(A->arr[i]);
            changeEntry(B, v->col, i, v->data);
            moveNext(A->arr[i]);
        }
    }
    return B;
}

// Returns a reference to a new Matrix object representing xA.
Matrix scalarMult(double x, Matrix A) {
    if (A == NULL) {
        printf("Matrix Error: calling scalarMult() on a NULL matrix refrence\n");
        exit(EXIT_FAILURE);
    }
    int n = size(A);
    Matrix B = newMatrix(n);
    for (int i = 1; i <= A->size; i++) {
        moveFront(A->arr[i]);
        while (index(A->arr[i]) >= 0) {
            Entry v = (Entry) get(A->arr[i]);
            double mul = v->data * x;
            changeEntry(B, i, v->col, mul);
            moveNext(A->arr[i]);
        }
    }
    return B;
}

// Returns a reference to a new Matrix object representing A+B.
// pre: size(A)==size(B)
Matrix sum(Matrix A, Matrix B) {
    if (A == NULL) {
        printf("Matrix Error: calling sum() on a NULL matrix A refrence\n");
        exit(EXIT_FAILURE);
    }
    if (B == NULL) {
        printf("Matrix Error: calling sum() on a NULL matrix B refrence\n");
    }
    if (A->size != B->size) {
        printf("Matrix Error: calling sum() on a matricies that are not the same size\n");
        exit(EXIT_FAILURE);
    }
    if (A == B) {
        Matrix temp = scalarMult(2, A);
        return temp;
    }
    Matrix new = newMatrix(size(A));
    for (int i = 1; i <= A->size; i++) {
        moveFront(A->arr[i]);
        moveFront(B->arr[i]);
        while(index(A->arr[i]) >= 0 && index(B->arr[i]) >= 0) {
            Entry a = (Entry) get(A->arr[i]);
            Entry b = (Entry) get(B->arr[i]);
            if (a->col < b->col) {
                changeEntry(new, i, a->col, a->data);
                moveNext(A->arr[i]);
            }
            if (a->col > b->col) {
                changeEntry(new, i, b->col, b->data);
                moveNext(B->arr[i]); 
            }
            if (a->col == b->col) {
                changeEntry(new, i, a->col, (a->data + b->data));
                moveNext(A->arr[i]);
                moveNext(B->arr[i]);
            }
        }
        while (index(A->arr[i]) >= 0 && index(B->arr[i]) < 0) {
            Entry a = (Entry) get(A->arr[i]);
            changeEntry(new, i, a->col, a->data);
            moveNext(A->arr[i]);
        }
        while (index(B->arr[i]) >= 0 && index(A->arr[i]) < 0) {
            Entry b = (Entry) get(B->arr[i]);
            changeEntry(new, i, b->col, b->data);
            moveNext(B->arr[i]);
        }
    }
    return new;
}

// Returns a reference to a new Matrix object representing A-B.
// pre: size(A)==size(B)
Matrix diff(Matrix A, Matrix B) {
    if (A == NULL) {
        printf("Matrix Error: calling diff() on a NULL matrix A refrence\n");
        exit(EXIT_FAILURE);
    }
    if (B == NULL) {
        printf("Matrix Error: calling diff() on a NULL matrix B refrence\n");
    }
    if (A->size != B->size) {
        printf("Matrix Error: calling diff() on a matricies that are not the same size\n");
        exit(EXIT_FAILURE);
    }
    if (A == B) {
        Matrix temp = newMatrix(size(A));
        return temp;
    }
    Matrix new = newMatrix(A->size);
    for (int i = 1; i <= A->size; i++) {
        moveFront(A->arr[i]);
        moveFront(B->arr[i]);
        while(index(A->arr[i]) >= 0 && index(B->arr[i]) >= 0) {
            Entry a = (Entry) get(A->arr[i]);
            Entry b = (Entry) get(B->arr[i]);
            if (a->col < b->col) {
                changeEntry(new, i, a->col, a->data);
                moveNext(A->arr[i]);
            }
            if (a->col > b->col) {
                changeEntry(new, i, b->col, -b->data);
                moveNext(B->arr[i]);
            }
            if (a->col == b->col) {
                changeEntry(new, i, a->col, (a->data - b->data));
                moveNext(A->arr[i]);
                moveNext(B->arr[i]);
            }
        }
        while (index(A->arr[i]) >= 0 && index(B->arr[i]) < 0) {
            Entry a = (Entry) get(A->arr[i]);
            changeEntry(new, i, a->col, a->data);
            moveNext(A->arr[i]);
        }
        while (index(B->arr[i]) >= 0 && index(A->arr[i]) < 0) {
            Entry b = (Entry) get(B->arr[i]);
            changeEntry(new, i, b->col, -b->data);
            moveNext(B->arr[i]);
        }
    }
    return new;
}

double dot(List A, List B, int i) {
    moveFront(A);
    moveFront(B);
    double total = 0;
    while ((index(A) >= 0) && (index(B) >= 0)) {
        Entry a = (Entry) get(A);
        Entry b = (Entry) get(B);
        if (a->col > b->col) {
            moveNext(B);
            continue;
        }
        if (a->col < b->col) {
            moveNext(A);
            continue;
        }
        if (a->col == b->col) {
            total += (a->data * b->data);
        }
        moveNext(A);
        moveNext(B);
    }
    return total;
}

// Returns a reference to a new Matrix object representing AB
// pre: size(A)==size(B)
Matrix product(Matrix A, Matrix B) {
    if (A == NULL) {
        printf("Matrix Error: calling product() on a NULL matrix A refrence\n");
        exit(EXIT_FAILURE);
    }
    if (B == NULL) {
        printf("Matrix Error: calling product() on a NULL matrix B refrence\n");
    }
    if (A->size != B->size) {
        printf("Matrix Error: calling product() on a matricies that are not the same size\n");
        exit(EXIT_FAILURE);
    }
    Matrix P = newMatrix(A->size);
    Matrix BNew = transpose(B);
    double p;
    for (int i = 1; i <= A->size; i++) {
        if (length(A->arr[i]) == 0) {
            continue;
        }
        for (int j = 1; j <= A->size; j++) {
            if (length(BNew->arr[j]) == 0) {
                continue;
            }
            p = dot(A->arr[i], BNew->arr[j], i);
            if (p != 0) {
                changeEntry(P, i, j, p);
            }
        }
    }
    return (P);
}

// Prints a string representation of Matrix M to filestream out.
// Zero rows are not printed. Each non-zero row is represented as one line consisting
// of the row number, followed by a colon, a space, then a space separated
// list of pairs "(col, val)" giving the column numbers and non-zero values
// in that row. The double val will be rounded to 1 decimal point.
void printMatrix(FILE* out, Matrix M) {
    if (M == NULL) {
        printf("Matrix Error: calling printMatrix() on a NULL matrix refrence\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 1; i <= M->size; i++) {
        if (length(M->arr[i]) == 0) {
            continue;
        }
        moveFront(M->arr[i]);
        fprintf(out, "%d: ", i);
        while (index(M->arr[i]) >= 0) {
            Entry k = (Entry) get(M->arr[i]);
            fprintf(out, "(%d, %.1f) ", k->col, k->data);
            moveNext(M->arr[i]);
        }
        fprintf(out, "\n");
    }
}
