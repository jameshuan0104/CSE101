/*
*James Huang, hhuan143
*2023 spring CSE101 PA#4
*ListTest.c
*simple test for functions in Matrix.c
*/

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"List.h"

int main(int argc, char* argv[]){
	List A = newList();
	List B = newList();
    List C = newList();

    int X[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
    int i, u=-1, v=-2, w=-3; 
    bool equal = false;

    // initialize Lists A and B
    for(i=1; i<=20; i++){
       append(A, &X[i]);
       prepend(B, &X[i]);
    }

    // print both lists of integers in forward direction
    for(moveFront(A); index(A)>=0; moveNext(A)){
       printf("%d ", *(int*)get(A));
    }
    printf("\n");
    for(moveFront(B); index(B)>=0; moveNext(B)){
       printf("%d ", *(int*)get(B));
    }
    printf("\n");

    if (length(A) == length(B)){
    	printf("equal length!");
    }

    printf("front A: %d ", *(int*)front(A));
    printf("back A: %d ", *(int*)back(A));

    deleteFront(A);
    deleteBack(A);

    clear(A);
    clear(B);
    freeList(&A);
    freeList(&B);



    return 0;


}