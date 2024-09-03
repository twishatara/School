//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// Twisha Sharma
// Cruz ID: tvsharma
// CSE 101-01 Tantalo
// Programming Assignment 2
// Graph.h
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
#pragma once

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "List.h" 

#define NIL -420
#define INF -5020
#define black 'B'
#define white 'W'
#define gray 'G'
#define UNDEF -14

typedef struct GraphObj *Graph;

/*** Constructors-Destructors ***/
Graph newGraph(int n);
void freeGraph(Graph* pG);

/*** Access functions ***/
int getOrder(Graph G);
int getSize(Graph G);
int getParent(Graph G, int u);
int getDiscover(Graph G, int u);
int getFinish(Graph G, int u);

/*** Manipulation procedures ***/
bool listSort(List L, int x);
void addArc(Graph G, int u, int v);
void addEdge(Graph G, int u, int v);
void Visit(Graph G, List L, int v);
void DFS(Graph G, List S);

/*** Other operations ***/
Graph transpose(Graph G);
Graph copyGraph(Graph G);
void printGraph(FILE* out, Graph G);

