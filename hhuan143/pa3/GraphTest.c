/*
*James Huang, hhuan143
*2023 spring CSE101 PA#3
*GraphTest.c
*simple test for Graph.c 
*/
#include<stdio.h>
#include<stdlib.h>
#include"List.h"
#include"Graph.h"

int main(int argc, char* argv[]){
   Graph G = newGraph(6);
   addArc(G, 1, 3);
   addArc(G, 1, 2);
   addArc(G, 2, 3);
   addArc(G, 3, 4);
   addArc(G, 4, 5);
   addEdge(G, 5, 6);
   fprintf(stdout, "Order: %d\n", getOrder(G));
   fprintf(stdout, "Size: %d\n", getSize(G));
   printGraph(stdout, G);
   List L = newList();
   for(int i=1; i<=6; i++) append(L, i);
   DFS(G, L);
   fprintf(stdout, "x:  d  f  p\n");
   for(int i=1; i<=6; i++){
      fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(G, i), getFinish(G, i), getParent(G, i));
   }
   
   fprintf(stdout, "\n");
   Graph copy = copyGraph(G);
   Graph gT = transpose(copy);
   DFS(gT, L);
   fprintf(stdout, "x:  d  f  p\n");
   for(int i=1; i<=6; i++){
      fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(gT, i), getFinish(gT, i), getParent(gT, i));
   }

   freeGraph(&G);
   freeGraph(&copy);
   freeGraph(&gT);

   return(0);
}