//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// Twisha Sharma
// Cruz ID: tvsharma
// CSE 101-01 Tantalo
// Programming Assignment 1
// List.c
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "List.h"

// structs ---------------------------------------------------------------------------------------------

// private Node type
typedef struct NodeObj *Node;

// private NodeObj type
typedef struct NodeObj{
    ListElement data;
    Node next;
    Node prev;
} NodeObj;

// private ListObj type
typedef struct ListObj{
    Node front;
    Node back;
    Node cursor;
    int length;
    int ind;
} ListObj;


// Constructors-Destructors ---------------------------------------------------------------------------

// Creates and returns a new empty List
Node newNode(ListElement data) {
    Node N = malloc(sizeof(NodeObj));
    if (N == NULL) {
        return NULL;
    }
    N->data = data;
    N->next = NULL;
    N->prev = NULL;
    return N;
}

// Frees all heap memory associated with *pN, and sets *pN to NULL
void freeNode(Node *pN) {
    if (pN != NULL && *pN != NULL) {
        free(*pN);
        *pN = NULL;
    }
}

// Creates and returns a new empty List
List newList(void) {
    List L;
    L = malloc(sizeof(ListObj));
    if (L == NULL) {
        return NULL;
    }
    L->front = NULL;
    L->back = NULL;
    L->cursor = NULL;
    L->ind = -1;
    L->length = 0;
    return L;
}

// Frees all heap memory associated with *pL, and sets *pL to NULL
void freeList(List *pL) {
    if (pL != NULL && *pL != NULL) {
        clear(*pL);
        free(*pL);
        *pL = NULL;
    }
}

// Access functions ---------------------------------------------------------------------------------- 

// Returns true if the list is empty, false otherwise
bool isEmpty(List L) {
    if (L == NULL) {
        printf("List Error: calling isEmpty on a NULL list refrence\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) > 0) {
        return false;
    }
    return true;
}

// Returns the number of elements in L
int length(List L) {
    if (L == NULL) {
        printf("List Error: calling length() on NULL List refrence\n");
        exit(EXIT_FAILURE);
    }
    return (L->length);
}

// Returns index of cursor element if defined, -1 otherwise
int index(List L) {
    if (L == NULL) {
        printf("List Error : calling index() on NULL List refrence\n");
        exit(EXIT_FAILURE);
    }
    return (L->ind);
}

// Returns front element of L
// Pre: length()>0
int front(List L) {
    if (L == NULL) {
        printf("List Error: calling front() on NULL List refrence\n");
        exit(EXIT_FAILURE);
    }
    if (isEmpty(L)) {
        printf("List Error: calling front() on an empty List\n");
        exit(EXIT_FAILURE);
    }
    return (L->front->data);
}

// Returns back element of L
// Pre: length()>0
int back(List L) {
    if (L == NULL) {
        printf("List Error: calling back() on NULL List refrence\n");
        exit(EXIT_FAILURE);
    }
    if (isEmpty(L)) {
        printf("List Error: calling back() on an empty List\n");
        exit(EXIT_FAILURE);
    }
    return (L->back->data);
}

// Returns cursor element of L
// Pre: length()>0, index()>=0
int get(List L) {
    if (L == NULL) {
        printf("List Error: calling get() on NULL List refrence\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) == 0) {
        printf("List Error: calling get() on an empty List\n");
        exit(EXIT_FAILURE);
    }
    return L->cursor->data;
}

// Returns true if Lists A and B are in same state, and returns false otherwise.
bool equals(List A, List B) {
    if (A == NULL) {
        printf("List Error (A): calling equals() on NULL List refrence\n");
        exit(EXIT_FAILURE);
    }
    if (B == NULL) {
        printf("List Error (B): calling equals() on NULL List refrence\n");
        exit(EXIT_FAILURE);
    }
    Node N;
    Node M;
    N = A->front;
    M = B->front;
    if (A->length != B->length) { // if the lists are not the same size
        return false; 
    }
    for (int i = 0; i < length(A); i++) { // itterate through the whole list
        if (N->data != M->data) { // if the node N data isnt the same as the Node M data
            return false;
        }
        N = N->next; // move to the next node
        M = M->next;
    }
    return true;
}

// Manipulation Procedures ---------------------------------------------------------------------------

// Resets L to its original empty state
void clear(List L) {
    while (length(L) > 0) {
        deleteFront(L);
    }
    return;
}

// Overwrites the cursor element’s data with x
// Pre: length()>0, index()>=0
void set(List L, int x) {
    if (length(L) <= 0 || index(L) < 0) {
        printf("List Error: calling set() with length or index preconditions not met\n");
        exit(EXIT_FAILURE);
    }
    L->cursor->data = x;
}

// moves cursor to x element
void moveTo(List L, int x) {
    if (L == NULL) {
        printf("List Error: calling get() on NULL List refrence\n");
        exit(EXIT_FAILURE);
    }
    if (x >= 0 && x <= length(L) - 1) {
        Node c = L->front; // create a cursor node and set it to the front of the lost
        for(int i = 0; i < x; i ++) {
            c = c->next; // parse through until you reach the node you want as a cursorn
        }
        L->cursor = c; // set the cursor
        L->ind = 1; // set the index 
    }
    else {
        L->cursor = NULL; 
        L->ind = -1;
    }
}


// If L is non-empty, sets cursor under the front element, otherwise does nothing.
void moveFront(List L) {
    if (!isEmpty(L)) {
        L->cursor = L->front;
        L->ind = 0;
    }
}

// If L is non-empty, sets cursor under the back element, otherwise does nothing.
void moveBack(List L) {
    if (!isEmpty(L)) {
        L->cursor = L->back;
        L->ind = length(L) - 1; // decrement the index since the cursor is moving back
    }
}

// If cursor is defined and not at front, move cursor one step toward the front of L; if cursor is 
// defined and at front, cursor becomes undefined; if cursor is undefined do nothing
void movePrev(List L) {
    if (L->cursor == NULL) {
        return;
    }
    if (L->cursor != NULL && L->cursor != L->front) {
        L->cursor = L->cursor->prev; 
        L->ind --; // cursor is moving so index must be updated
        return;
    }
    if (L->cursor != NULL && L->cursor == L->front) {
        L->cursor = NULL;
        L->ind = -1;
        return;
    }
}

// If cursor is defined and not at back, move cursor one step toward the back of L; if cursor is 
// defined and at  back, cursor becomes undefined; if cursor is undefined do nothing
void moveNext(List L) {
    if (L->cursor == NULL) {
        return;
    }
    if (L->cursor != NULL && L->cursor != L->back) {
        L->cursor = L->cursor->next;
        L->ind ++; // cursor is moving so index must be updated
        return;
    }
    if (L->cursor != NULL && L->cursor == L->back) {
        L->cursor = NULL;
        L->ind = -1; // set index of cursor to undefined
        return;
    }
}

// Insert new element into L. If L is non-empty, insertion takes place before front element.
void prepend(List L, int x) {

    if (length(L) == 0) {
        Node s = newNode(x);
        L->length += 1;
        L->front = s;
        L->back = s;
        return;
    }
    if (length(L) > 0) {
        Node s = newNode(x); // New node, holding the data
        L->length += 1;
        if (L->ind != -1) { // if the cursor exists
           L->ind += 1; // increment the index, because a node is being added 
        }
        L->front->prev = s; // add the new node to the front of the list
        s->next = L->front; // set the next
        L->front = s; // update the front
        return;
    }
}

// Insert new element into L. If L is non-empty, insertion takes place after back element
void append(List L, int x) {
    if (length(L) == 0) {
        Node s = newNode(x);
        L->length += 1;
        L->back = s;
        L->front = s;
        return;
    }
    if (length(L) > 0) {
        Node s = newNode(x);
        L->length += 1;
        L->back->next = s;
        s->prev = L->back;
        L->back = s;
        return;
    }
}

// Insert new element before cursor
// Pre: length()>0, index()>=0
void insertBefore(List L, int x) {
    if (length(L) <= 0) {
        printf("List Error: calling insertBefore() with length or index preconditions not met\n");
        exit(EXIT_FAILURE);
    }
    if (index(L) < 0) {
        printf("List Error: calling insertBefore() with length or index preconditions not met\n");
        exit(EXIT_FAILURE);
    }
    if (index(L) == 0) {
        prepend(L, x);
        return;
    }
    Node N = newNode(x);
    L->cursor->prev->next = N;
    N->prev = L->cursor->prev;
    L->cursor->prev = N;
    N->next = L->cursor;
    L->length ++;

    L->ind ++;
    return;

}

// Insert new element after cursor
// Pre: length()>0, index()>=0
void insertAfter(List L, int x) {
    if (length(L) <= 0) {
        printf("List Error: calling insertAfter() with length or index preconditions not met\n");
        exit(EXIT_FAILURE);
    }
    if (index(L) < 0) {
        printf("List Error: calling insertBefore() with length or index preconditions not met\n");
        exit(EXIT_FAILURE);
    }
    if (L->cursor == L->back) {
        append(L, x);
        return;
    }
    Node N = newNode(x);
    L->cursor->next->prev = N;
    N->next = L->cursor->next;
    N->prev = L->cursor;
    L->cursor->next = N;
    L->length ++; // increment the length 
    return;
}

// Delete the front element
// Pre: length()>0
void deleteFront(List L) {
    if (L == NULL) {
        printf("List Error: calling deleteFront() with length preconditions not met\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) <= 0) {
        printf("List Error: calling deleteFront() with length preconditions not met\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) == 1) {
        Node F = NULL;
        F = L->front;
        if (L->cursor == L->front) {
            L->ind = -1;
        }
        L->front = NULL;
        L->back = NULL;
        freeNode(&F);
        L->length = 0;
        return;
    }
    else {
        Node N = NULL; // temp node to hold the node after the L->front
        N =  L->front;
        if (L->cursor == L->front) {
            L->ind = -1;
            L->front = L->front->next;
            freeNode(&N);
            L->length --;
            return;
        }
        if (L->cursor != NULL) {
            L->ind --;
        }
        L->front = L->front->next;
        freeNode(&N);
        L->length --;
        return;
    }
}

// Delete the back element
// Pre: length()>0
void deleteBack(List L) {
    Node N = NULL;
    N = L->back;
    if (L == NULL) {
        printf("List Error: calling deleteBack() with length preconditions not met\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) <= 0){
       printf("List Error: calling deleteBack() with lengthpreconditions not met\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) == 1) {
        if (L->cursor != NULL) {
            L->cursor = NULL;
            L->ind = -1;
        }
        freeNode(&L->back);
        L->length = 0;
        return;
    }
    else {
        if (L->cursor == L->back) {
            L->cursor = NULL;
            L->ind = -1;
        }
        L->back = L->back->prev;
        freeNode(&N);
        L->length --;
        return;
    }
}

// Delete cursor element, making cursor undefined
// Pre: length()>0, index()>=0
void delete(List L) {
    if (L->cursor == NULL) {
        printf("List Error : calling delete() on NULL List cursor refrence\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) <= 0 || index(L) < 0) {
        printf("List Error: calling delete() with length or index preconditions not met\n");
        exit(EXIT_FAILURE);
    }
    if (L->cursor == L->front) {
        deleteFront(L);
        return;
    }
    if (L->cursor == L->back) {
        deleteBack(L);
        return;
    }
    L->cursor->prev->next = L->cursor->next;
    L->cursor->next->prev = L->cursor->prev;
    freeNode(&L->cursor);
    L->ind = -1;
    L->length --;
    return;
}

// Helper operations ---------------------------------------------------------------------------

// Prints to the file pointed to by out, a string representation of L consisting
// of a space separated sequence of integers, with front on left.
void printList(FILE *out, List L) {
    for (Node next = L->front; next != NULL; next = next->next) {
        fprintf(out, "%d ", next->data);
    }
    printf("\n");
}

// Returns a new List representing the same integer sequence as L. The cursor in the new 
// list is undefined,regardless of the state of the cursor in L. The state // of L is unchanged.
List copyList(List L) {
    List new = newList();
    moveFront(L);
    for (Node N = L->front; N != NULL; N = N->next) {
       append(new, N->data);
    }
    return new;
}
