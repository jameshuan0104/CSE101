/*
*James Huang, hhuan143
*2023 spring CSE101 PA#2
*FindPath.c
*main file for reading a graph and finding distance of given vertex
*/
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
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
      addEdge(G, x, y);
    }
    printGraph(out, G);
    fprintf(out, "\n");

    while(1){
      fscanf(in, "%d %d\n", &x, &y);
      if (x && y == 0){
        break;
      }
      List L = newList();
      BFS(G, x);
      getPath(L, G, y);
      if(length(L) == 0 || getDist(G, y) < 0){
        fprintf(out, "The distance from %d to %d is infinity\nNo %d-%d path exists", x, y, x, y);
      }else{
        moveBack(L);
        fprintf(out, "The distance from %d to %d is %d\nA shortest %d-%d path is: ", x, y, index(L), x, y);
        printList(out, L);
      }
      fprintf(out, "\n");
      fprintf(out, "\n");
      freeList(&L);
      //freeGraph(&G);
    }
    fclose(out);
    fclose(in);
    //freeList(&L);
    freeGraph(&G);
    return 0;

}