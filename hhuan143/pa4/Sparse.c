/*
*James Huang, hhuan143
*2023 spring CSE101 PA#4
*Sparse.c
*main file for Matrix.c
*/

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"Matrix.h"

int main(int argc, char* argv[]){
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
    int n, Annz, Bnnz;
    out = fopen(argv[2], "w");
    if( out==NULL ){
    	fprintf(stderr, "Unable to open file %s for writing\n", argv[2]);
        exit(1);
    }

    fscanf(in, "%d %d %d", &n, &Annz, &Bnnz);

    Matrix A = newMatrix(n);
    Matrix B = newMatrix(n);

    int row, col;
    double val;
    for (int i = 1; i <= Annz; i++){
    	fscanf(in, "%d %d %lf\n", &row, &col, &val);
    	changeEntry(A, row, col, val);
    }



    for (int i = 1; i <= Bnnz; i++){
    	fscanf(in, "%d %d %lf\n", &row, &col, &val);
    	changeEntry(B, row, col, val);
    }

    fprintf(out, "\nA has %d non-zero entries:\n", NNZ(A));
    printMatrix(out, A);

    fprintf(out, "\nB has %d non-zero entries:\n", NNZ(B));
    printMatrix(out, B);

    Matrix smult = scalarMult(1.5, A);
    fprintf(out, "\n(1.5)*A =\n");
    printMatrix(out, smult);

    Matrix add1 = sum(A, B);
    fprintf(out, "\nA+B =\n");
	printMatrix(out, add1);

	Matrix add2 = sum(A, A);
    fprintf(out, "\nA+A =\n");
    printMatrix(out, add2);

    Matrix minus1 = diff(B, A);
    fprintf(out, "\nB-A =\n");
    printMatrix(out, minus1);

    Matrix minus2 = diff(A, A);
    fprintf(out, "\nA-A =");
    printMatrix(out, minus2);

    Matrix T = transpose(A);
    fprintf(out, "\nTranspose(A) =\n");
    printMatrix(out, T);

    Matrix mult1 = product(A, B);
    fprintf(out, "\nA*B =\n");
    printMatrix(out, mult1);

    Matrix mult2 = product(B, B);
    fprintf(out, "\nB*B =\n");
    printMatrix(out, mult2);



	return 0;
}