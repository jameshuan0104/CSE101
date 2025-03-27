/*
*James Huang, hhuan143
*2023 spring CSE101 PA#1
*ListTest.c
*Short test to test List.c
*/




#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"List.h"

int main(int argc, char* argv[]){
	List A = newList();
    List B = newList();
    printList(stdout, A);
    printf("\n");
    printList(stdout, B);
    printf("\n");
    if(equals(A, B)){
    	printf("True\n");
    }else{
    	printf("False\n");
    }

    int i;
    for(i=1; i<=30; i++){
        append(A,i);
    	prepend(B,i);
    }

    printList(stdout, A); //1-30
    printf("\n");
    printList(stdout, B); //30-1
    printf("\n");

    if(equals(A, B)){
    	printf("True\n");
    }else{
    	printf("False\n");
    }

    moveFront(A); //cursor set to front
    moveBack(B);  //cursor set to back

    movePrev(B); 
    moveNext(A); 
    printf("index: %d\n", index(A)); //1
    printf("index: %d\n", index(B)); //28
    moveNext(B);
    movePrev(A);

    printf("index: %d\n", index(A)); //0
    printf("index: %d\n", index(B)); //29

    printf("length: %d\n", length(A)); //30
    printf("length: %d\n", length(B)); //30

    insertBefore(A, 0); //0-30
    insertAfter(B, 0);  //30-0

    printList(stdout, A); //0-30
    printf("\n");
    printList(stdout, B); //30-0
    printf("\n");

    deleteBack(A); //0-29
    deleteFront(B);//29-0

    set(A, -1); //1 -> -1
    set(B, -1); //1 -> -1

   	printList(stdout, A);
   	printf("\n"); 
    printList(stdout, B);
    printf("\n");

    clear(B);

    List copyA = copyList(A);
    if(equals(copyA, A)){
    	printf("True\n");
    }else{
    	printf("False\n");
    }

    printList(stdout, A); //0-29
    printf("\n");
    printList(stdout, copyA); //0-29
    printf("\n");

    freeList(&A);
    freeList(&B);
    return 0;


}