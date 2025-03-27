/*
*James Huang, hhuan143
*2023 spring CSE101 PA#1
*Lex.c
*main file that does a insert sort
*/




#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include"List.h"

#define MAX_LEN 300

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
    //printf("meow\n");
    int lines = 0;
    char txt[MAX_LEN];
    while(fgets(txt, MAX_LEN, in) != NULL){
    	lines++;
    }
    rewind(in);

    char **buffer = (char **) malloc(lines *sizeof(char *));

    int i = 0;
    while(fgets(txt, MAX_LEN, in) != NULL){
    	buffer[i] = malloc(MAX_LEN *sizeof(char));
    	strcpy(buffer[i], txt);
    	i++;
    }
    

   	List A = newList();
   	for(int i = 0; i < lines; i++){
   		if(length(A) == 0){
   			append(A, 0);
   			moveFront(A);
   		}else{
   			for(moveFront(A); index(A) >= 0; moveNext(A)){
   				if(strcmp(buffer[get(A)], buffer[i]) >= 0){
   					insertBefore(A, i);
   					break;
   				}
   			}
   			if(index(A) == -1){
   				append(A, i);
   			}
   		
	   	}
   	}
    //printList(stdout, A);
    //printf("\n");
    moveFront(A);
    while(index(A) != -1){
    	fprintf(out, "%s",buffer[get(A)]);
    	moveNext(A);
    }


    fclose(out);
    fclose(in);
    freeList(&A);
    

    for(int i = 0; i < lines; i++){
    	free(buffer[i]);
    }
    free(buffer);
   




   
   



}