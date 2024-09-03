//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// Twisha Sharma
// Cruz ID: tvsharma
// CSE 101-01 Tantalo
// Programming Assignment 3
// FindComponents.c
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "List.h"
#include "Graph.h"

int main(int argc, char* argv[]) {
    int a, b, c;
    int comp = 0, scc = 0;
    if (argv[1] == NULL || argv[2] == NULL) {
        printf("User Input Error: Please specify input and output file\n");
        exit(EXIT_FAILURE);
    }
    FILE *in = fopen(argv[1], "r");
    FILE *out = fopen(argv[2], "w");
    fscanf(in, "%d", &a);
    Graph G = newGraph(a);
    List L = newList();
    List I = newList();
    fscanf(in, "%d %d", &b, &c); 
    while (b != 0 && c != 0) {
        addArc(G, b, c);
	fscanf(in, "%d %d", &b, &c);
    }
    fprintf(out, "Adjacency list representation of G: \n");
    printGraph(out, G);
    for (int x = 1; x < getOrder(G) + 1; x++) {
        append(L, x);
    }
    DFS(G, L); 
    Graph T = transpose(G);
    DFS(T, L);
    moveBack(L);
    for (int i = 1; i <= getOrder(T); i++) {
        if (getParent(T, i) == NIL) {
	     scc ++;
	}
    } 
    fprintf(out,"G contains %d strongly connected components:\n", scc); 
    while (index(L) >= 0) {
        prepend(I, get(L));
	if (getParent(T, get(L)) == NIL) {  
	    comp ++;
	    fprintf(out,"\n");
	    fprintf(out,"Component %i: ",comp);
	    printList(out, I);
	    clear(I);
	}
	movePrev(L);
    }
    return 0;
}

