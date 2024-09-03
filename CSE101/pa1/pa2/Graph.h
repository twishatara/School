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
#include <List.h> 

#define NIL -420
#define INF -5020
#define black 'B'
#define white 'W'
#define gray 'G'

typedef struct GraphObj *Graph;

/*** Constructors-Destructors ***/
Graph newGraph(int n);
void freeGraph(Graph* pG);

/*** Access functions ***/
int getOrder(Graph G);
int getSize(Graph G);
int getSource(Graph G);
int getParent(Graph G, int u);
int getDist(Graph G, int u);
void getPath(List L, Graph G, int u);

/*** Manipulation procedures ***/
void makeNull(Graph G);
void addArc(Graph G, int u, int v);
void addEdge(Graph G, int u, int v);
void BFS(Graph G, int s);

/*** Other operations ***/
void printGraph(FILE* out, Graph G);
