/*
*James Huang, hhuan143
*2023 spring CSE101 PA#3
*FindComponents.c
*main file to find the strongly connected components
*/

#include<stdio.h>
#include<stdlib.h>
#include"List.h"
#include"Graph.h"

int main(int argc, char * argv[]){
    if(argc != 3){
      fprintf(stderr, "wrong number of arguments\n");
      exit(1);
    }
    FILE *in, *out;
    in = fopen(argv[1], "r");
    if( in==NULL ){
    	fprintf(stderr, "Unable to open file %s for reading\n", argv[1]);
      	exit(1);
    }
    out = fopen(argv[2], "w");
    if( out==NULL ){
    	fprintf(stderr, "Unable to open file %s for writing\n", argv[2]);
        exit(1);
    }

    int n; 
    fscanf(in, "%d\n", &n);
    Graph G = newGraph(n);
    int x, y;

    while(1){
      fscanf(in,"%d %d\n", &x, &y);
      if (x == 0 && y == 0){
        break;
      }
      addArc(G, x, y);
    }
    fprintf(out, "Adjacency list representation of G:\n");
    printGraph(out, G);
    fprintf(out, "\n");

    int numSCCs;
    List S = newList();
    for(int i=1; i<=getOrder(G); i++) append(S, i);
    DFS(G,S);
    Graph T = transpose(G);
    DFS(T,S);
    for(int i = 1; i <= getOrder(T); i++){
    	if(getParent(T, i) == NIL){
    		numSCCs++;
    	}
    }
    fprintf(out, "G contains %d strongly connected components:\n", numSCCs);
    List *comp;
    comp = malloc(sizeof(List) * (numSCCs));
    for (int i = 1; i <= numSCCs; i++){
		comp[i] = newList();
	}

	int i = numSCCs + 1;
    for (moveFront(S); index(S) >= 0; moveNext(S)){
    	if (getParent(T, get(S)) == NIL){
    		i--;
    		append(comp[i], get(S));
    	}else{
    		append(comp[i], get(S));
    	}

    }
    for(int i = 1; i <= numSCCs; i++){
    	fprintf(out, "Component %d: ",i);
    	printList(out, comp[i]);
    	fprintf(out, "\n");
    }
    fclose(out);
    fclose(in);
    return 0;

}