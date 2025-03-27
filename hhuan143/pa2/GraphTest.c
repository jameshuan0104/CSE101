/*
*James Huang, hhuan143
*2023 spring CSE101 PA#2
*GraphTest.c
*simple test for Graph.c functions
*/

#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"

int main(int argc, char* argv[]){
	Graph G = newGraph(6);
	addEdge(G, 1, 2);
	addEdge(G, 1, 3);
	addEdge(G, 3, 4);
	addEdge(G, 3, 5);
	addEdge(G, 5, 6);
	addArc(G, 2, 3);
	printGraph(stdout, G);
	printf("order: %d\n", getOrder(G));
	printf("size: %d\n", getSize(G));
	BFS(G, 1);
	printf("source: %d\n", getSize(G));
	printf("parent of 3: %d\n", getParent(G, 3));
	printf("distance of 6: %d\n", getDist(G, 6));
	List L = newList();
	getPath(L, G, 6);
	printList(stdout, L);
	printf(" (getPath() of 6)\n");
	makeNull(G);
	printGraph(stdout, G);
	freeList(&L);
	freeGraph(&G);


   return(0);
}