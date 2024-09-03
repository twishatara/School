//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// Twisha Sharma
// Cruz ID: tvsharma
// CSE 101-01 Tantalo
// Programming Assignment 4
// ListTest.c
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#include "List.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(void) {
    printf("---------- testing newList() ----------\n");
    List A = newList();
    List B = newList();
    // test isEmpty
    if (L != NULL) {
        printf("The list has been made!\n");
    }
    else{
        printf("The created list was not made\n");
    }

    printf("---------- testing append() and prepend() and printList() ----------\n");
    int X[] = {0, 1, 2, 3}; 
    for( int i = 1; i <= 4; i++) {
        append(A, &X[i]);
        prepend(B, &X[i]);
    }
    printf("List A: ");
    printList(stdout, A);
    printf("List B: ");
    printList(stdout, B);

    printf("---------- testing length() ----------\n");
    printf("the length of the list is : %d\n", length(L));

    printf("---------- testing index() ----------\n");
    printf("the index of the cursor element is : %d\n", index(L));

    printf("---------- testing front() ----------\n");
    printf("the front element is : %d\n", front(L));

    printf("---------- testing back() ----------\n");
    printf("the back element is : %d\n", back(L));

    printf("---------- testing moveFront() and get() ----------\n");
    moveFront(L);
    printf("the cursor element is : %d\n", *(int*)get(L));
    if (index(L) == 0) {
        printf("moveFront moved the cursor to the front of the list!\n");
    }
    else {
        printf("moveFront did not move the cursor to the front of the list\n");
    }
    printf("---------- testing equals() ----------\n");
    if (equals(A, L) == true) {
        printf("The lists are in the same state\n");
    }
    else {
        printf("The lists are not in the same state\n");
    }

    printf("---------- testing clear() ----------\n");
    printf("List A: ");
    clear(A); 
    printList(stdout, A);

    printf("---------- testing set() ----------\n"); 
    set(L, 3); 
    if (*(int*)get(L) == 3) {
        printf("the cursor element data is now set to %d\n", *(int*)get(L));
    }

    printf("---------- testing moveBack() ----------\n");
    moveBack(L);
    printf("the cursor element is : %d\n", *(int*)get(L));
    if (index(L) == length(L) - 1) {
        printf("moveBack moved the cursor to the back of the list!\n");
    }
    else {
        printf("moveBack did not move the cursor to the front of the list\n");
    }

    printf("---------- testing movePrev() and moveNext() ----------\n");
    printf("cursor index before movePrev: %d\n", index(L));
    movePrev(L); 
    printf("cursor index after movePrev: %d\n", index(L));
    printf("cursor index before moveNext: %d\n", index(L));
    moveNext(L);
    printf("cursor index after moveNext: %d\n", index(L));

    printf("---------- testing insertBefore() and insertAfter() ----------\n");
    printList(stdout, L);
    printf("Now inserting 35 before the cursor\n");
    insertBefore(L, 35);
    printList(stdout, L);
    printf("Now inserting 45 after the cursor\n");
    insertAfter(L, 45);
    printList(stdout, L);
    
    printf("---------- testing deleteFront() deleteBack() ----------\n");
    printList(stdout, L);
    printf("Now deleting the front of the list\n");
    deleteFront(L);
    printList(stdout, L);
    printf("Now deleting the back of the list\n");
    deleteBack(L);
    printList(stdout, L);

    printf("---------- testing delete() ----------\n");
    printf("this is the cursor element: %d\n", *(int*)get(L));
    printf("Now deleting the cursor element\n");
    delete(L);
    printList(stdout, L);

    return 0;
}
