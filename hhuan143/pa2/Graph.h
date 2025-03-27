/*
*James Huang, hhuan143
*2023 spring CSE101 PA#2
*Graph.h
*defines the functions 
*/
// #ifndef LIST_H_INCLUDE_
// #define LIST_H_INCLUDE_
#include <stdbool.h>
#include "List.h"

#define INF -1
#define NIL 0
#define white -10
#define grey -20
#define black -30


// Exported types -------------------------------------------------------------
typedef int GraphElement;
typedef struct GraphObj* Graph;

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
void addEdge(Graph G, int u, int v);
void addArc(Graph G, int u, int v);
void BFS(Graph G, int s);
/*** Other operations ***/
void printGraph(FILE* out, Graph G);