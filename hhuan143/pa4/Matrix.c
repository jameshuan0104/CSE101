/*
*James Huang, hhuan143
*2023 spring CSE101 PA#4
*Matrix.c
*writes the functions for Matrix.h
*/

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>
#include <math.h>
#include "Matrix.h"

typedef struct EntryObj *Entry;

typedef struct EntryObj {
    int col;
    double val;
} EntryObj;

typedef struct MatrixObj {
    int size;
    int NNZ;
    List *row;
} MatrixObj;

// constructor for Entry
Entry newEntry(int column, double value) {
    Entry E = malloc(sizeof(EntryObj));
    E->col = column; 
    E->val = value; 
    return E;
}

void deleteEntry(Entry *pE) {
    if (pE != NULL && *pE != NULL){
        free(*pE);
        *pE = NULL;
    }
}


// newMatrix()
// Returns a reference to a new nXn Matrix object in the zero state.
Matrix newMatrix(int n){ 
	if (n < 0){
		printf("Matrix Error: calling newMatrix() on size zero\n");
        exit(EXIT_FAILURE);
	}
	Matrix M;
	M = malloc(sizeof(MatrixObj));
	assert(M != NULL);
	M->size = n;
	M->NNZ = 0;//need this? 
	M->row = malloc(sizeof(List) * (n+1));
	for (int i = 1; i <= n; i++){
		M->row[i] = newList();
	}
	return M;
}

// freeMatrix()
// Frees heap memory associated with *pM, sets *pM to NULL.
void freeMatrix(Matrix* pM){
	if (pM != NULL && *pM != NULL){
        makeZero(*pM);
        free(*pM);
        *pM = NULL;
    }
}
// Access functions
// size()
// Return the size of square Matrix M.
int size(Matrix M){
	if (M == NULL){
		printf("Matrix Error: calling size() on NULL matrix\n");
        exit(EXIT_FAILURE);
	}
	return M->size; 
}
// NNZ()
// Return the number of non-zero elements in M.
int NNZ(Matrix M){
	if (M == NULL){
		printf("Matrix Error: calling NNZ() on NULL matrix\n");
        exit(EXIT_FAILURE);
	}
	return M->NNZ; 
}
// equals()
// Return true (1) if matrices A and B are equal, false (0) otherwise.
int equals(Matrix A, Matrix B){
	if( A==NULL || B==NULL ){
      printf("Matrix Error: calling equals() on NULL Matrix reference\n");
      exit(EXIT_FAILURE);
    }
    if (A->size != B->size){
    	return 0;
    }
    Entry x, y;
    //List c, d;
    for (int i = 1; i <= A->size; i++){
    	moveFront(A->row[i]);
    	moveFront(B->row[i]);
    	if (length(A->row[i]) == length(B->row[i])){
    		while(index(A->row[i]) >= 0 && index(B->row[i]) >= 0){
    			x = (Entry)get(A->row[i]);
                y = (Entry)get(B->row[i]);
                if (x->val != y->val){
                	return 0;
                }
                if (x->col != y->col){
                    return 0;
                }
                moveNext(A->row[i]);
                moveNext(B->row[i]);
    		}
    	}else{
    		return 0;
    	}
    }
    return 1;
}
// Manipulation procedures
// makeZero()
// Re-sets M to the zero Matrix state.
void makeZero(Matrix M){
    if(M == NULL){
      printf("Matrix Error: calling makeZero() on NULL Matrix reference\n");
      exit(EXIT_FAILURE);
    }
    M->NNZ = 0;
    Entry E;
    for (int i = 1; i <= M->size; i++){
        for (moveFront(M->row[i]);index(M->row[i]) >= 0; moveNext(M->row[i])){
            E = (Entry)get(M->row[i]);
            deleteEntry(&E); 
        }
        clear(M->row[i]);
    }

}
// changeEntry()
// Changes the ith row, jth column of M to the value x.
// Pre: 1<=i<=size(M), 1<=j<=size(M)
void changeEntry(Matrix M, int i, int j, double x){
    if (M == NULL){
        printf("Matrix Error: calling changeEntry() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }
    if (i > M->size || i < 1){
        printf("Matrix Error: calling changeEntry() on invalid i value\n");
        exit(EXIT_FAILURE);
    }
    if (j > M->size || j < 1){
        printf("Matrix Error: calling changeEntry() on invalid j value\n");
        exit(EXIT_FAILURE);
    }
    List L = M->row[i];
    if (length(L) == 0){
        if (x != 0){
            Entry E = newEntry(j, x);
            append(L, E);
            M->NNZ++;
        }
    }else{
        for (moveFront(L); index(L) >= 0; moveNext(L)){
            Entry E = (Entry)get(L);
            if (E->col == j){
                if (x != 0){
                    Entry E = (Entry)get(L);
                    E->val = x;
                }else{
                    Entry E = (Entry)get(L);
                    deleteEntry(&E);
                    delete(L);
                    M->NNZ--;
                }
                break;
            }else if(E->col > j){
                if (x != 0){
                    Entry E = newEntry(j, x);
                    insertBefore(L, E);
                    M->NNZ++;
                }
                break;
            }
        }
        if (index(L) == -1){
            if (x != 0){
                Entry E = newEntry(j, x);
                append(L, E);
                M->NNZ++;
            }
        }
    }
}
// Matrix Arithmetic operations
// copy()
// Returns a reference to a new Matrix object having the same entries as A.
Matrix copy(Matrix A){
    if (A == NULL){
        printf("Matrix Error: calling copy() on NULL matrix reference\n");
        exit(EXIT_FAILURE);
    }
    int col;
    double val;
    Matrix M = newMatrix(A->size);
    M->NNZ = A->NNZ;
    for (int i = 1;i <= A->size; i++){
        for (moveFront(A->row[i]); index(A->row[i]) >= 0; moveNext(A->row[i])){
            Entry E = (Entry)get(A->row[i]);
            col = E->col;
            val = E->val;
            Entry copy = newEntry(col, val);
            append(M->row[i], copy);
        }
    }
    return M;

}
// transpose()
// Returns a reference to a new Matrix object representing the transpose
// of A.
Matrix transpose(Matrix A){
    if (A == NULL){
        printf("Matrix Error: calling transpose() on NULL matrix reference\n");
        exit(EXIT_FAILURE);
    }
    Matrix T = newMatrix(A->size);
    double val;
    int j;
    T->NNZ = A->NNZ;
    for (int i = 1; i <= A->size; i++){
        for (moveFront(A->row[i]); index(A->row[i]) >= 0; moveNext(A->row[i])){
            Entry E = (Entry)get(A->row[i]);
            j = E->col;
            val = E->val;
            Entry copy = newEntry(i, val);
            append(T->row[j], copy);
        }
    }
    return T;
}
// scalarMult()
// Returns a reference to a new Matrix object representing xA.
Matrix scalarMult(double x, Matrix A){
    if (A == NULL){
        printf("Matrix Error: calling scalarMult() on NULL matrix reference\n");
        exit(EXIT_FAILURE);
    }
    Matrix M = newMatrix(A->size);
    int col;
    double val;
    if (x == 0 || A->NNZ == 0){
        return M;
    }
    for (int i = 1; i <= A->size; i++){
        for (moveFront(A->row[i]); index(A->row[i]) >= 0; moveNext(A->row[i])){
            Entry E = (Entry)get(A->row[i]);
            col = E->col;
            val = E->val * (x);
            Entry copy = newEntry(col, val);
            append(M->row[i], copy);
            M->NNZ++;
        }
    }
    return M;
}
// sum()
// Returns a reference to a new Matrix object representing A+B.
// pre: size(A)==size(B)
void vecSum(List A, List B, List C, int sign){
    double x, y, z;
    Entry a, b;
    moveFront(A);
    moveFront(B);
    while (index(A) >= 0 && index(B) >= 0){
        a = get(A);
        b = get(B);
        x = a->val;
        y = (sign) * b->val;
        if (a->col == b->col){
            z = x + y;
            if (z != 0){
                Entry new = newEntry(a->col, z);
                append(C, new);
            }
            moveNext(A);
            moveNext(B);
        }else if (a->col < b->col){
            Entry new = newEntry(a->col, x);
            append(C, new);
            moveNext(A);
        }else{
            Entry new = newEntry(b->col, y);
            append(C, new);
            moveNext(B);
        }

    }
    while (index(A) >= 0){
        a = get(A);
        Entry new = newEntry(a->col, a->val);
        append(C, new);
        moveNext(A);
    }
    while (index(B) >= 0){
        b = get(B);
        Entry new = newEntry(b->col, (sign) * b->val);
        append(C, new);
        moveNext(B);
    }
}
Matrix sum(Matrix A, Matrix B){
    if (A == NULL || B == NULL){
        printf("Matrix Error: calling sum() on NULL matrix reference\n");
        exit(EXIT_FAILURE);
    }
    if (A->size != B->size){
        printf("Matrix Error: calling sum() on different size matrices\n");
        exit(EXIT_FAILURE);
    }
    Matrix M = newMatrix(A->size);
    if (equals(A, B) == 1){
        return scalarMult(2, A);
    }else{
        for (int i = 1; i <= M->size; i++){
            vecSum(A->row[i], B->row[i], M->row[i], 1);
            M->NNZ += length(M->row[i]);
        }
    }
    return M;
}
// diff()
// Returns a reference to a new Matrix object representing A-B.
// pre: size(A)==size(B)
Matrix diff(Matrix A, Matrix B){
    if (A == NULL || B == NULL){
        printf("Matrix Error: calling sum() on NULL matrix reference\n");
        exit(EXIT_FAILURE);
    }
    if (A->size != B->size){
        printf("Matrix Error: calling sum() on different size matrices\n");
        exit(EXIT_FAILURE);
    }
    Matrix M = newMatrix(A->size);
    if (equals(A, B)){
        makeZero(M);
        return M;
    }else{
        for (int i = 1; i <= M->size; i++){
            vecSum(A->row[i], B->row[i], M->row[i], -1);
            M->NNZ += length(M->row[i]);
        }
    }
    return M;
}
// product()
// Returns a reference to a new Matrix object representing AB
// pre: size(A)==size(B)
double vecDot(List A, List B){
    double x = 0.0;
    Entry a, b; 
    moveFront(A); 
    moveFront(B);
    while (index(A) >= 0 && index(B) >= 0){
        //printf("meow\n");
        a = (Entry)get(A);
        b = (Entry)get(B);
        if (a->col == b->col){
            x += a->val * b->val;
            moveNext(A);
            moveNext(B);
        }else if (a->col < b->col){
            moveNext(A);
        }else{
            moveNext(B);
        }

    }
    return x;
}
Matrix product(Matrix A, Matrix B){
    if (A == NULL || B == NULL){
        printf("Matrix Error: calling sum() on NULL matrix reference\n");
        exit(EXIT_FAILURE);
    }
    if (A->size != B->size){
        printf("Matrix Error: calling sum() on different size matrices\n");
        exit(EXIT_FAILURE);
    }
    Matrix M = newMatrix(A->size);
    Matrix T = transpose(B);
    double x; 
    for (int i = 1; i <= A->size; i++){
        for (int j = 1; j <= A->size; j++){
            if (length(A->row[i]) == 0){
                break;
            }
            x = vecDot(A->row[i], T->row[j]);
            if (x != 0.0){
                Entry new = newEntry(j, x);
                append(M->row[i], new);
                M->NNZ++;

            }
        }
    }
    freeMatrix(&T);
    return M;
}
// printMatrix()
// Prints a string representation of Matrix M to filestream out. Zero rows
// are not printed. Each non-zero row is represented as one line consisting
// of the row number, followed by a colon, a space, then a space separated
// list of pairs "(col, val)" giving the column numbers and non-zero values
// in that row. The double val will be rounded to 1 decimal point.
void printMatrix(FILE* out, Matrix M){
    Entry E;
    for (int i = 1; i <= M->size; i++){
        if (length(M->row[i]) != 0){
            fprintf(out, "%d:", i);
            for (moveFront(M->row[i]); index(M->row[i]) >= 0; moveNext(M->row[i])){
                E = (Entry)get(M->row[i]);
                fprintf(out, "(%d, %.1f) ", E->col, E->val);
            }
            if (index(M->row[i]) == -1){
                fprintf(out, "\n");
            }
        }
    }
}



