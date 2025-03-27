/*
*James Huang, hhuan143
*2023 spring CSE101 PA#4
*MatrixTest.c
*simple test for functions in Matrix.c
*/
#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include"Matrix.h"
int main(){
	Matrix A = newMatrix(3);
	changeEntry(A, 1, 1, 1);
	changeEntry(A, 2, 2, 1);
	changeEntry(A, 3, 3, 1);

	printf("%d\n", NNZ(A));
    printMatrix(stdout, A);
    printf("\n");

    Matrix T = transpose(A);

    if (equals(T,A)){
    	printf("transpose of identity matrix stays the same:\n");
    	printf("%d\n", NNZ(T));
    	printMatrix(stdout, T);
    	printf("\n");
    }
	
    Matrix smult = scalarMult(10, A);
    printf("scalarMult by 10:\n");
    printf("%d\n", NNZ(smult));
    printMatrix(stdout, smult);
    printf("\n");

    Matrix add = sum(smult, T);
    printf("sum with 10 + T:\n");
    printf("%d\n", NNZ(add));
    printMatrix(stdout, add);
    printf("\n");

    Matrix minus = diff(smult, T);
    printf("diff with 10 - T:\n");
    printf("%d\n", NNZ(minus));
    printMatrix(stdout, minus);
    printf("\n");

    Matrix mult = product(smult, T);
    printf("product with 10 * T:\n");
    printf("%d\n", NNZ(mult));
    printMatrix(stdout, mult);
    printf("\n");

    Matrix cop = copy(T);
    printf("copy T:\n");
    printf("%d\n", NNZ(cop));
    printMatrix(stdout, cop);
    printf("\n");

    makeZero(T);
    makeZero(A);
    if (equals(T,A)){
    	printf("makeZero on T and A:\n");
    	printf("%d\n", NNZ(T));
    	printMatrix(stdout, T);
    	printf("\n");
    }

    freeMatrix(&A);
    freeMatrix(&T);
    freeMatrix(&smult);
	freeMatrix(&minus);
    freeMatrix(&add);
    freeMatrix(&mult);
    freeMatrix(&cop);


	return EXIT_SUCCESS;
}