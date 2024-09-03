//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// Twisha Sharma
// Cruz ID: tvsharma
// CSE 101-01 Tantalo
// Programming Assignment 2
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
    int *distance;
    int verticies; // **** THIS IS ORDER ****
    int edges; // **** THIS IS SIZE ****
    int source; // THIS IS LABEL FOR WHEN VICTOR EXPLAINS : recent source vertex on a bfs call
} GraphObj;

// Constructors-Destructors ---------------------------------------------------------------------------

Graph newGraph(int n) {
    Graph G = calloc(1, sizeof(GraphObj));
    if (G == NULL) {
        return NULL;
    }
    // all are allocated with n+1 to account for the tree starting at node 1 instead of node 0
    G->neighbors = (List *) calloc(n + 1, sizeof(List)); // allocate memory for an array of lists
    G->colors = (int) calloc (n + 1, sizeof(int)); // allocate array of colors
    G->parent = (int) calloc(n + 1, sizeof(int)); // allocate array of parents
    G->distance = (int) calloc(n + 1, sizeof(int)); // allocate array of distances
    for (int i = 0; i < n + 1; i += 1) { 
        G->neighbors[i] = newList(); // allocate memory for the list in each index of the neighbors array
        G->parent[i] = NIL; 
        G->distance[i] = INF;
        G->colors[i] = white; // set all to white
    }
    G->verticies = n; // number of unique verticies 
    G->edges = 0; // number of edges
    G->source = 0; // source vertex (THIS IS LABEL)
    return G;
}

void freeGraph(Graph* pG) {
    if (pG != NULL && *pG != NULL) { // if the graph exists 
        for (int i = 1; i <= getOrder(*pG); i ++){ // iterate through every list in the neighbor array
            freeList(&((*pG)->neighbors[i])); // free everything inside every list in the neighbor array
        }
        free((*pG)->neighbors); // free neighbors array
        (*pG)->neighbors = NULL;
        free((*pG)->colors); // free colors array
        (*pG)->colors = NULL;
        free((*pG)->parent); // free parent array
        (*pG)->parent = NULL; 
        free((*pG)->distance); // free distance array
        (*pG)->distance = NULL; 
        free(*pG); // free graph
        *pG = NULL;
    }
}

// Access functions ---------------------------------------------------------------------------------- 

// pre: Graph exists
int getOrder(Graph G) {
    if (G == NULL) { // if the graph does not exists
        printf("Graph Error: calling getOrder() on a NULL graph refrence\n");
        exit(EXIT_FAILURE); 
    }
    return G->verticies;
}

// pre: Graph exists
int getSize(Graph G) {
    if (G == NULL) { // if the graph does not exists
        printf("Graph Error: calling getSize() on a NULL graph refrence\n");
        exit(EXIT_FAILURE); 
    }
    return G->edges;
}

// pre : Graph exists and BFS has been called
int getSource(Graph G){
    if (G == NULL) { // if the graph does not exist
        printf("Graph Error: calling getSource() on a NULL graph refrence\n");
        exit(EXIT_FAILURE); 
    }
    if (!G->source) { // if BFS has not been called 
        return NIL;
    }
    return G->source;
}

// pre : Graph exists, BFS has been called, 1 < u < getOder(G)
int getParent(Graph G, int u) {
    if (G == NULL) { // if the graph does not exist
        printf("Graph Error: calling getParent() on a NULL graph refrence\n");
        exit(EXIT_FAILURE); 
    }
    if(!G->source){ // if BFS has not been called
        return NIL;
    }
    if (u < 1 || u > getOrder(G)) { // if vertex is not in range
        printf("Graph Error: calling getParent() on out of range vertex \n");
        exit(EXIT_FAILURE);
    }
    return G->parent[u];
}

// pre : Graph exists, BFS has been called, 1 < u < getOder(G)
int getDist(Graph G, int u) {
    if (G == NULL) { // if the graph does not exist
        printf("Graph Error: calling getDist() on a NULL graph refrence\n");
        exit(EXIT_FAILURE); 
    }
    if(!G->source) { // if BFS has not been called
        return INF;
    }
    if (u < 1 || u > getOrder(G)) { // if vertex is not in range
        printf("Graph Error: calling getDist() on out of range vertex \n");
        exit(EXIT_FAILURE);
    }
    return G->distance[u];
}

// pre : Graph exists, BFS has been called, 1 < u < getOder(G)
void getPath(List L, Graph G, int u) {
    if (getSource(G) == NIL) { // if graph does not exist
        return NIL;
    }
    if(!G->source) { // if BFS has not been called
        return NIL;
    }
    if (u < 1 || u > getOrder(G)) { // if vertex is not in range
        printf("Graph Error: calling getPath() on out of range vertex \n");
        exit(EXIT_FAILURE);
    }
    if (getParent(G,u) == NIL) { // if no path exists 
        append(L, NIL); // append NIL
    }
    if (u == getSource(G)) { // if the vertex is the source node from BFS
        append(L, u); // append the vertex to the list
    }
    else {
        int p = NULL;
        prepend(L, u); // add the vertex to the front of the list
        p = getParent(G, u); // get the parent of the vertex
        while( p != getSource(G) && p != NIL) { // until the parent node == NIL and is not the source node 
            prepend(L, p); // add the parent node to the front of the list
            p = getParent(G, p); // assign the new parent node
        }
        prepend(L, p);  
    } 
    return;
}

// Manipulation procedures ---------------------------------------------------------------------------------- 

void makeNull(Graph G) {
    G->source = NIL;
    G->edges = 0;
    for(int i = 1; i <= getOrder(G); i ++) { 
        clear(G->neighbors[i]);
        G->distance[i] = INF;
        G->parent[i] = NIL;
        G->colors[i] = white; // set the color to white
    }
    return;
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
    addArc(G, u, v); // adding v to the adj list of u
    addArc(G, v, u); // adding u to the adj list of v
    G->edges --; // because addArc increments the number of edges, decrement by one since the 2 calls are for the same edge
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
    int cur = -1;
    // adding v to adj list of u 
    moveTo(G->neighbors[u], 0); // set the cursor of list at the neighbor "u" index to 0
    if (index(G->neighbors[u]) != -1) {// if the cursor of the list at index "u" is not undefined
        cur = get(G->neighbors[u]); // cur = the cursor of thelost at index "u"
    }
    //if (index(G->neighbors[u]) != -1) { //the index of the cursor for the list at index "u" is defined
    while (v > cur && index(G->neighbors[u]) != -1) { // while v is greater than the cur and the index of the cursor for the list at index "u" is still defined
        moveNext(G->neighbors[u]); // move the cursor one step to the back of the list at the index "u"
        if (index(G->neighbors[u]) != -1) { // if the index of the cursor is still defined 
            cur = get(G->neighbors[u]);// set cur to the element at the cursor
        }
    }
    if (index(G->neighbors[u]) != -1) {// if the cursor of the list at index "u" is not undefined
        insertBefore(G->neighbors[u], v); // insert v before the cursor in the list at index "u"
    }
    else{
        append(G->neighbors[u],v); // add v to the back of the list at index "u"
    }
    G->edges ++;
}

// credit: Professor Tantalo, BFS psuedocode in python
// pre : Graph exists and 1 < s < getOder(G)
void BFS(Graph G, int s) {
    if (G == NULL) { // if the graph does not exist
        printf("Graph Error: calling BFS() on a NULL graph refrence\n");
        exit(EXIT_FAILURE);
    }
    if (s < 1 || s > getOrder(G)) { // if source is not in range
        printf("Graph Error: calling BFS() on out of range source \n");
        exit(EXIT_FAILURE);
    }
    for (int i = 1; i <= getOrder(G); i ++) {
        G->distance[i] = INF;
        G->parent[i] = NIL;
        G->colors[i] = white;
   }
    G->colors[s] = gray; // discover the source s
    G->distance[s] = 0;
    G->parent[s] = NIL;
    List Q = newList(); // construct a new empty list
    append(Q,s); // enqueue the source to the list
    while (!isEmpty(Q)) { // while the list isnt empty
        int x = front(Q); // x = the front node in the list
        deleteFront(Q); // delete the front of the list 
        moveTo(G->neighbors[x], 0); // set the cursor of list at the neghibor "x" index to 0
        while (index(G->neighbors[x]) != -1){ // while the index of neighbors[x] != -1?? (until the index is undefined)
            int y = get(G->neighbors[x]); // y = the cursor of the path/list on the neghibors array "x" index 
            if (G->colors[y] == white) { // y is undiscovered
                  G->colors[y] = gray; // discover y
                  G->distance[y] = getDist(G, x); // set the correct distance
                         G->parent[y] = x; // set the parent
                  append(Q,y);
             }
        G->colors[x] = black; // finish x
        }
    freeList(&Q); // free the list
    }
}


// Other operations ---------------------------------------------------------------------------------- 

void printGraph(FILE* out, Graph G) {
   if(getSource(G) == NIL) {
       return NIL;
   }
   for (int x = 0; x < G->neighbors[x]; x ++) {
       if (x == G->source){
           printf("%i\n", G->source);
       }
       else if (G->parent[x] == NIL) {
           printf("%i\n, is not reachable from, %i\n", x, G->source);
       }
       else {
        PrintPath(G, G->source, G->parent[x]);
        printf("%i\n", x);
       }
   }
}