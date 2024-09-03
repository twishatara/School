//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// Twisha Sharma
// Cruz ID: tvsharma
// CSE 101-01 Tantalo
// Programming Assignment 3
// Graph.c
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Graph.h"
#include "List.h"

// structs ---------------------------------------------------------------------------------------------

// private GraphObj type
typedef struct GraphObj {
    List *neighbors;
    int *colors;
    int *parent;
    int *discover;
    int *finish;
    int verticies;
    int edges;
    int time;
    bool check; 
} GraphObj;

// Constructors-Destructors ---------------------------------------------------------------------------

Graph newGraph(int n) {
    Graph G = calloc(1, sizeof(GraphObj));
    if (G == NULL) {
        return NULL;
    }
    // all are allocated with n+1 to account for the tree starting at node 1 instead of node 0
    G->neighbors = (List *) calloc(n + 1, sizeof(List)); // allocate memory for an array of lists
    G->colors = calloc (n + 1, sizeof(int)); // allocate array of colors
    G->parent = calloc(n + 1, sizeof(int)); // allocate array of parents
    G->discover = calloc(n + 1, sizeof(int)); // allocate array of discover times
    G->finish = calloc(n + 1, sizeof(int)); // allocate array for the finish times
    for (int i = 0; i < n + 1; i += 1) { 
        G->neighbors[i] = newList(); // allocate memory for the list in each index of the neighbors array
    }
    G->verticies = n; // number of unique verticies 
    G->edges = 0; // number of edges
    G->check = false; // test case var
    return G;
}

void freeGraph(Graph* pG) {
    if (pG != NULL && *pG != NULL) { // if the graph exists 
        for (int i = 0; i <= (*pG)->verticies; i ++){ // iterate through every list in the neighbor array
            freeList(&((*pG)->neighbors[i])); // free everything inside every list in the neighbor array
        }
	free((*pG)->finish); // free finish array
        (*pG)->finish = NULL;
        free((*pG)->discover); // free discover array
        (*pG)->discover = NULL;
	free((*pG)->parent); // free parent array
        (*pG)->parent = NULL;
	free((*pG)->colors); // free colors array
        (*pG)->colors = NULL;
	free((*pG)->neighbors); // free neighbors array
        (*pG)->neighbors = NULL;
	free(*pG); // free graph
        *pG = NULL;
    }
}

// Access functions ---------------------------------------------------------------------------------- 

// pre: Graph exists
int getOrder(Graph G) {
    if (G == NULL) { // if the graph does not exists
        printf("Graph Error: calling getOrder() on a NULL graph reference\n");
        exit(EXIT_FAILURE); 
    }
    return G->verticies;
}

// pre: Graph exists
int getSize(Graph G) {
    if (G == NULL) { // if the graph does not exists
        printf("Graph Error: calling getSize() on a NULL graph reference\n");
        exit(EXIT_FAILURE); 
    }
    return G->edges;
}

// pre : Graph exists, DFS has been called, 1 < u < getOder(G)
int getParent(Graph G, int u) {
    if (G == NULL) { // if the graph does not exist
        printf("Graph Error: calling getParent() on a NULL graph reference\n");
        exit(EXIT_FAILURE); 
    }
    if (G->check == false) { // if DFS has not been called
        return NIL;
    }
    if (u < 1 || u > getOrder(G)) { // if vertex is not in range
        printf("Graph Error: calling getParent() on out of range vertex \n");
        exit(EXIT_FAILURE);
    }
    return G->parent[u];
}

// pre: 1 <= u <= n=getOrder(G)
int getDiscover(Graph G, int u) {
    if (G->check == false) { // if dfs has not been called
        return UNDEF;
    }
    if (u < 1 || u > getOrder(G)) { // if vertex is not in range
        printf("Graph Error: calling getDiscover() on out of range vertex \n");
        exit(EXIT_FAILURE);
    }
    return G->discover[u];
}

// pre: 1 <= u <= n = getOrder(G)
int getFinish(Graph G, int u) {
    if (G->check == false) { // if dfs has not been called
        return UNDEF;
    }
    if (u < 1 || u > getOrder(G)) { // if vertex is not in range
        printf("Graph Error: calling getFinish() on out of range vertex \n");
        exit(EXIT_FAILURE);
    }
    return G->finish[u];
}

// Manipulation procedures ---------------------------------------------------------------------------------- 

// inserts a new vertex into the specified list and sorts
bool listSort(List L, int x) {
    moveFront(L);
    while (index(L) >= 0){
        int val = get(L); // save the cursor value to "val"
        if (x == val) {
            return false;
        }
        if (x < val) {
            insertBefore(L, x);
            return true;
        }
        moveNext(L);
    }
    append(L, x);
    return true;
}

// inserts a new edge joining u to v, i.e. u is added to the adjacency List of v, and v to the adjacency List of u
// pre: Graph exists, 1<u<getOrder(G) and 1<v<getOrder(G)
void addEdge(Graph G, int u, int v) {
    if (G == NULL) { // if the graph does not exist
        printf("Graph Error: calling addEdge() on a NULL graph refrence\n");
        exit(EXIT_FAILURE); 
    }
    if (u < 1 || u > getOrder(G)) { // if u is not in range
        printf("Graph Error: calling addEdge() on out of range u \n");
        exit(EXIT_FAILURE);
    }
    if (v < 1 || v > getOrder(G)) { // if u is not in range
        printf("Graph Error: calling addEdge() on out of range v \n");
        exit(EXIT_FAILURE);
    }
    // adding u to the adj list of v and v to the adj list of u
    if ((listSort(G->neighbors[v], u) == true) && (listSort(G->neighbors[u], v) == true)){ // if the value was inserted correctly and the list was sorted
        G->edges ++; // increment the edges
    }
    return; 
}

// inserts a new directed edge from u to v, i.e. v is added to the adjacency List of u (but not u to the adjacency List of v).
// pre: Graph exists, 1<u<getOrder(G) and 1<v<getOrder(G)
void addArc(Graph G, int u, int v) {
    if (G == NULL) { // if the graph does not exist
        printf("Graph Error: calling addArc() on a NULL graph refrence\n");
        exit(EXIT_FAILURE); 
    }
    if (u < 1 || u > getOrder(G)) { // if u is not in range
        printf("Graph Error: calling addArc() on out of range u \n");
        exit(EXIT_FAILURE);
    }
    if (v < 1 || v > getOrder(G)) { // if u is not in range
        printf("Graph Error: calling addArc() on out of range v \n");
        exit(EXIT_FAILURE);
    }
    // adding v to the adj list of u
    if (listSort(G->neighbors[u], v) == true) { // if the value was inserted correctly
        G->edges ++; // increment the edges
    } 
    return;
}

// credit: Professor Tantalo, Visit() psuedocode in python
void Visit(Graph G, List L, int v) {
    G->discover[v] = ++(G->time); // the discover time at x, ++time increments time and then assigns the value
    G->colors[v] = gray;      
    moveFront(G->neighbors[v]);
    while (index(G->neighbors[v]) >= 0) {
	int u = get(G->neighbors[v]);
	if (G->colors[u] == white) {
            G->parent[u] = v; 
	    Visit(G, L, u);
        }
	moveNext(G->neighbors[v]);
    }
    G->colors[v] = black;
    insertAfter(L, v);
    G->finish[v] = ++(G->time); // finish time of x  
}

// credit: Professor Tantalo, DFS psuedocode in python
//pre: length(S)==getOrder(G)
void DFS(Graph G, List S) {
    if (G == NULL) { // if the graph does not exist
        printf("Graph Error: calling DFS() on a NULL graph refrence\n");
        exit(EXIT_FAILURE);
    }
    G->check = true;
    if (length(S) != getOrder(G)) { // if the length of S is not equal to the size of the graph
        printf("Graph Error: calling DFS() with preconditions not met\n");
	exit(EXIT_FAILURE);
    }
    for (int x = 1; x <= getOrder(G); x++) {
        G->colors[x] = white;
	G->parent[x] = NIL;
    }
    G->time = 0;
    moveBack(S); 
    for (int i = 1; i <= getOrder(G); i ++) {
	if (G->colors[front(S)] == white) {
	    Visit(G, S, front(S));
	}
	deleteFront(S);
    }
}

// Other operations ---------------------------------------------------------------------------------- 

// pre : Graph exists 
Graph transpose(Graph G) {
    if (G == NULL) { // if the graph does not exist
        printf("Graph Error: calling transpose() on a NULL graph refrence\n");
        exit(EXIT_FAILURE);
    }
    int n = getOrder(G);
    Graph transpose = newGraph(n);
    for (int x = 1; x <= getOrder(G); x++) {
        moveFront(G->neighbors[x]);
        while (index(G->neighbors[x]) >= 0) {
	    int y = get(G->neighbors[x]); // get the adj vertex
	    addArc(transpose, y, x); 
	    moveNext(G->neighbors[x]); 
	}
    }
    return transpose;
}

// pre : Graph exists
Graph copyGraph(Graph G) {
    if (G == NULL) { // if the graph does not exist
        printf("Graph Error: calling copyGraph() on a NULL graph refrence\n");
        exit(EXIT_FAILURE);
    }
    int n = getOrder(G);
    Graph newG = newGraph(n);
    for (int i = 1; i <= n; i++) {
	newG->neighbors[i] = G->neighbors[i];
    }
    return newG;
}

void printGraph(FILE* out, Graph G) {
   for (int x = 1; x < getOrder(G) + 1; x ++) {
       fprintf(out, "%d: ", x);
       printList(out, G->neighbors[x]);        
   }
   fprintf(out, "\n");
} 

