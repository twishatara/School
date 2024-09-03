//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// Twisha Sharma
// Cruz ID: tvsharma
// CSE 101-01 Tantalo
// Programming Assignment 3
// GraphTest.c
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include "List.h"
#include "Graph.h"

int main(void) {
    printf("---------- testing newGraph() ----------\n");
    Graph G = newGraph();
    if (G != NULL) {
        printf("The graph has been made!\n");
    }
    else{
        printf("The created grapht was not made\n");
    }

    printf("---------- testing addArc() and addEdge() and printGraph() ----------\n");
    addArc(G, 1,2);
    addArc(G, 1,5);
    addArc(G, 2,5);
    addArc(G, 2,6);
    addArc(G, 3,2);
    addArc(G, 3,4);
    addArc(G, 3,6);
    addArc(G, 3,7);
    addArc(G, 3,8);
    addEdge(G, 6,5);
    addEdge(G, 6,7);
    addEdge(G, 8,4);
    addEdge(G, 8,7);
    
    printf("Graph G: ");
    printGraph(stdout, G);

    printf("---------- testing getOrder() ----------\n");
    printf("the order of the graph is : %d\n", getOrder(G));

    printf("---------- testing getSize() ----------\n");
    printf("the size of the graph is : %d\n", getSize(G));

    printf("---------- testing getParent() ----------\n");
    printf("the parent is : %d\n", getParent(G));

    printf("---------- testing getDiscover() and DFS() ----------\n");
    int u = 5;
    printf("the discover times is : %d\n", getDiscover(G, u));

    printf("---------- testing getFinish() and DFS() ----------\n");
    printf("the finish time is : %d\n", getFinish(G, u));
    

    printf("---------- testing transpose() ----------\n");
    printf("Graph G: ");
    printGraph(stdout, G);
    printf("Graph Transpose: ");
    Graph T = transpose(G);
    printGraph(stdout, T);

    printf("---------- testing copyGraph() ----------\n");
    printf("Graph G: ");
    printGraph(stdout, G);
    Graph C = copyGraph(G);
    printf("Graph Copy: ");
    printGraph(stdout, C);

    return 0;
}

