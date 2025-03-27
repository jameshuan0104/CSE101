/*
*James Huang, hhuan143
*2023 spring CSE101 PA#2
*Graph.c
*defines and make the functions in Graph.h 
*/
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>
#include "List.h"
#include "Graph.h"


typedef struct GraphObj{
	List* adj;
	char* color;  // array of color of vertex "i"
    int* parent; // array of parent of vertex "i"
    int* distance;   // array of distance from source to vertex "i"
    int source;  //label for recent vertex used as source
    int order;   // stores #vertices = n
    int size;    // # of edges
	

}GraphObj;


/*** Constructors-Destructors ***/

Graph newGraph(int n){
	if(n < 1){
		printf("Graph Empty: calling newGraph() on empty graph\n");
        exit(EXIT_FAILURE);
	}
	Graph G;
	G = malloc(sizeof(GraphObj));
	assert(G != NULL);
	G->order = n;
	G->size = 0;
	//G->source = NIL;
	G->adj = malloc(sizeof(List) * (n+1));
	G->color = malloc(sizeof(int) * (n+1));
	assert(G->color != NULL);
	G->parent = malloc(sizeof(int) * (n+1));
	assert(G->parent != NULL);
	G->distance = malloc(sizeof(int) * (n+1));
	assert(G->distance != NULL);

	for (int i = 1; i <= n; i++){
		G->adj[i] = newList();
		G->color[i] = white;
		G->parent[i] = NIL;
		G->distance[i] = INF; 
	}
	return G;

}
void freeGraph(Graph* pG){
	int i, n;
	if (pG && *pG != NULL){
		n = (*pG)->order; 
		for (i = 1; i <= n; i++){
			freeList(&((*pG)->adj[i]));
		}
		free((*pG)->adj);
		free((*pG)->color);
		free((*pG)->parent);
		free((*pG)->distance);
		free(*pG);
		*pG = NULL;

	}
}

/*** Access functions ***/

int getOrder(Graph G){
	if (G == NULL){
		printf("Graph Empty: calling getOrder() on empty graph\n");
        exit(EXIT_FAILURE);
	}
	return G->order;
}
int getSize(Graph G){
	if (G == NULL){
		printf("Graph Empty: calling getOrder() on empty graph\n");
        exit(EXIT_FAILURE);
	}
	return G->size;
}
int getSource(Graph G){
		if (G == NULL){
		printf("Graph Empty: calling getSource() on empty graph\n");
        exit(EXIT_FAILURE);
	}
	return G->source;
}

int getParent(Graph G, int u){
	if (G == NULL){
		printf("Graph Empty: calling getParent() on empty graph\n");
        exit(EXIT_FAILURE);
	}
	if (u > getOrder(G) || u < 1){
		printf("Calling getParent() on u out of range\n");
        exit(EXIT_FAILURE);
	}
	if (getSource(G) == NIL){
		return NIL;
	}else{
		return G->parent[u];
	}
}
int getDist(Graph G, int u){
	if (G == NULL){
		printf("Graph Empty: calling getDist() on empty graph\n");
        exit(EXIT_FAILURE);
	}
	if (u < 1 || u > G->order){
		printf("Calling getDist() on u out of range\n");
        exit(EXIT_FAILURE);
	}
	if (getSource(G) == NIL){
		return INF;
	}else{
		return G->distance[u];
	}
}
void getPath(List L, Graph G, int u){
	if (G == NULL){
		printf("Graph Empty: calling getPath() on empty graph\n");
        exit(EXIT_FAILURE);
	}
	if (L == NULL){
		printf("List Empty: calling getPath() on empty list\n");
        exit(EXIT_FAILURE);
	}
	if (u < 1 || u > getOrder(G)){
		printf("Calling getPath() on u out of range\n");
        exit(EXIT_FAILURE);
	}
	if (getSource(G) == NIL){
		printf("Calling getPath() before BFS\n");
        exit(EXIT_FAILURE);
	}
	if (u == G->source){
		append(L, G->source);
	}else if(getParent(G, u) == NIL){
		append(L, NIL);
	}else{
		getPath(L, G, getParent(G, u));
		append(L, u);
	}

}

/*** Manipulation procedures ***/
void makeNull(Graph G){
	if (G == NULL){
		printf("Graph Empty: calling makeNULL() on empty graph\n");
        exit(EXIT_FAILURE);
	}
	G->source = NIL;
	G->size = 0;
	//G->order = 0;
	for (int i = 1;i <= getOrder(G); i++){
		G->color[i] = white;
		G->parent[i] = NIL;
		G->distance[i] = INF; 
		clear(G->adj[i]);
	}
}
void addEdge(Graph G, int u, int v){
	if (G == NULL){
		printf("Graph Empty: calling addEdge() on empty graph\n");
        exit(EXIT_FAILURE);
	}
	if (u < 1 || u > G->order){
		printf("Calling addEdge() on u out of range\n");
        exit(EXIT_FAILURE);
	}


	List U = G->adj[u];
	List V = G->adj[v];
	moveFront(U);
	if (length(U) == 0){
		append(U, v);
	}else{
		moveFront(U);
		while(get(U) < v){
			moveNext(U);
			if (index(U) == -1){
				break;
			}
		}
		if (index(U) == -1){
			append(U, v);
		}else{
			insertBefore(U, v);
		}
	}

	moveFront(V);
	if (length(V) == 0){
		append(V, u);
	}else{
		moveFront(V);
		while(get(V) < u){
			moveNext(V);
			if (index(V) == -1){
				break;
			}
		}
		if (index(V) == -1){
			append(V, u);
		}else{
			insertBefore(V, u);
		}
	}
	G->size++;
}
void addArc(Graph G, int u, int v){
	if (G == NULL){
		printf("Graph Empty: calling addArc() on empty graph\n");
        exit(EXIT_FAILURE);
	}
	if (u < 1 || u > G->order){
		printf("Calling addEdge() on u out of range\n");
        exit(EXIT_FAILURE);
	}

	List U = G->adj[u];
	if (length(U) == 0){
		append(U, v);
	}else{
		moveFront(U);
		while(get(U) < v){
			moveNext(U);
			if (index(U) == -1){
				break;
			}
		}
		if (index(U) == -1){
			append(U, v);
		}else{
			insertBefore(U, v);
		}
	}
	G->size++;

}
void BFS(Graph G, int s){
	if (G == NULL){
		printf("Graph Empty: calling BFS() on empty graph\n");
        exit(EXIT_FAILURE);
	}
	for (int i = 1;i <= G->order; i++){
		G->color[i] = white;
		G->distance[i] = INF;
		G->parent[i] = NIL;
	}
	G->source = s;
	G->color[s] = grey;
	G->distance[s] = 0;
	G->parent[s] = NIL;
	List queue = newList();
	moveFront(G->adj[s]);
	append(queue, s);
	while(length(queue) != 0){
		int x = front(queue);
		deleteFront(queue);
		for (moveFront(G->adj[x]); index(G->adj[x]) >= 0; moveNext(G->adj[x])){
			int y = get(G->adj[x]);
			if (G->color[y] == white){
				G->color[y] = grey;
				G->distance[y] = G->distance[x] + 1;
				G->parent[y] = x;
				append(queue, y);	
			}
		}
		G->color[x] = black;
	}
	freeList(&queue);

}
/*** Other operations ***/
void printGraph(FILE* out, Graph G){
	if (G == NULL){
		printf("Graph Empty: calling printGraph() on empty graph\n");
        exit(EXIT_FAILURE);
	}
	for(int i = 1; i <= getOrder(G); i++){
		List L = G->adj[i];
        moveFront(L);
        fprintf(out, "%d: ", i);
        while(index(L) > -1){
            fprintf(out, "%d ", get(L));
            moveNext(L);
        }
        fprintf(out, "\n");
    }

}




