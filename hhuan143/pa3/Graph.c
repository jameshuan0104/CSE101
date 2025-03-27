/*
*James Huang, hhuan143
*2023 spring CSE101 PA#3
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
    int* discover;
    int* done;   
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
	G->color = malloc(sizeof(int*) * (n+1));
	assert(G->color != NULL);
	G->parent = malloc(sizeof(int*) * (n+1));
	assert(G->parent != NULL);
	G->discover = malloc(sizeof(int*) * (n+1));
	assert(G->discover != NULL);
	G->done = malloc(sizeof(int*) * (n+1));
	assert(G->done != NULL);
	for (int i = 1; i <= n; i++){
		G->adj[i] = newList();
		G->color[i] = white;
		G->parent[i] = NIL;
		G->discover[i] = UNDEF;
		G->done[i] = UNDEF; 
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
		free((*pG)->discover);
		free((*pG)->done);
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

int getParent(Graph G, int u){
	if (G == NULL){
		printf("Graph Empty: calling getParent() on empty graph\n");
        exit(EXIT_FAILURE);
	}
	if (u > getOrder(G) || u < 1){
		printf("Calling getParent() on u out of range\n");
        exit(EXIT_FAILURE);
	}
	if (getDiscover(G, u) == UNDEF){
		return NIL;
	}else{
		return G->parent[u];
	}
}
int getDiscover(Graph G, int u){
	if (G == NULL){
		printf("Graph Empty: calling getDiscover() on empty graph\n");
        exit(EXIT_FAILURE);
	}
	if (u > getOrder(G) || u < 1){
		printf("Calling getDiscover() on u out of range\n");
        exit(EXIT_FAILURE);
	}
	return G->discover[u];


} /* Pre: 1<=u<=n=getOrder(G) */
int getFinish(Graph G, int u){
	if (G == NULL){
		printf("Graph Empty: calling getDiscover() on empty graph\n");
        exit(EXIT_FAILURE);
	}
	if (u > getOrder(G) || u < 1){
		printf("Calling getDiscover() on u out of range\n");
        exit(EXIT_FAILURE);
	}
	return G->done[u];
} /* Pre: 1<=u<=n=getOrder(G) */
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
		}else if(get(U) == v){
			return;
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
		}else if(get(V) == u){
			return;
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
		}else if(get(U) == v){
			return;
		}else{
			insertBefore(U, v);
		}
	}
	G->size++;

}
void Visit(Graph G, List S, int x, int *time){
	if (G == NULL){
		printf("Graph Empty: calling Visit() on empty graph\n");
        exit(EXIT_FAILURE);
	}
	List L = G->adj[x];
	//int n = get(L);
	G->discover[x] = ++(*time);
	G->color[x] = grey;  
	for (moveFront(L); index(L) >= 0; moveNext(L)){
		int y = get(L);
		if (G->color[y] == white){
			G->parent[y] = x;
			Visit(G, S, y, time); 
		}
	}
	G->color[x] = black;
	G->done[x] = ++(*time);
	prepend(S, x);
}
void DFS(Graph G, List S){
	if (G == NULL){
		printf("Graph Empty: calling DFS() on empty graph\n");
        exit(EXIT_FAILURE);
	}
	if (length(S) != getOrder(G)){
		printf("Wrong Order: calling DFS() on unequal order\n");
        exit(EXIT_FAILURE);
	}

	int time = 0;
	for (int i = 1; i <= getOrder(G); i++){
		G->color[i] = white; 
		G->parent[i] = NIL;
		G->discover[i] = UNDEF;
		G->done[i] = UNDEF;
	}
	for (moveFront(S); index(S) >= 0; moveNext(S)){
		int x = get(S);
		if (G->color[x] == white){
			Visit(G, S, x, &time);
		}
	}
	for (moveFront(S); index(S) >= 0; moveNext(S)){
		deleteBack(S);
	}
}/* Pre: length(S)==getOrder(G) */

// Other Functions
Graph transpose(Graph G){
	if (G == NULL){
		printf("Graph Empty: calling Transpose() on empty graph\n");
        exit(EXIT_FAILURE);
	}
	Graph nG = newGraph(getOrder(G));
	for (int i = 1;i <= getOrder(G); i++){
		moveFront(G->adj[i]);
		while(index(G->adj[i]) != -1){
			int data = get(G->adj[i]);
			addArc(nG, data, i);
			moveNext(G->adj[i]);
		}
	}
	return nG;
}
Graph copyGraph(Graph G){
	if (G == NULL){
		printf("Graph Empty: calling CopyGraph() on empty graph\n");
        exit(EXIT_FAILURE);
	}
	Graph nG = newGraph(getOrder(G));
	for (int i = 1;i <= getOrder(G); i++){
		moveFront(G->adj[i]);
		while(index(G->adj[i]) != -1){
			addArc(nG, i, get(G->adj[i]));
			moveNext(G->adj[i]);
		}
	}
	return nG;
}
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




