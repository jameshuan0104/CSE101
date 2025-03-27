/*
*James Huang, hhuan143
*2023 spring CSE101 PA#4
*List.c
*writes the functions of List.h
*/
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>
#include "List.h"

// private Node type
typedef struct NodeObj* Node;

// private NodeObj type
typedef struct NodeObj{
   ListElement data;
   Node next;
   Node previous;
} NodeObj;

// private QueueObj type
typedef struct ListObj{
   int cursor;
   Node cursorNode;
   Node front;
   Node back;
   int length;
} ListObj;


// Constructors-Destructors ---------------------------------------------------
List newList(void){
    List L;
    L = malloc(sizeof(ListObj));
    assert(L != NULL);
    L->cursor = -1;
    L->front = L->back = L->cursorNode = NULL;
    L->length = 0;
    return L;
} // Creates and returns a new empty List.

void freeList(List* pL){
    if (pL != NULL && *pL != NULL){
        clear(*pL);
        free(*pL);
        *pL = NULL;
    }
} // Frees all heap memory associated with *pL, and sets
// *pL to NULL.

Node newNode(ListElement data){
    //malloc?
    Node N;
    N = malloc(sizeof(NodeObj));
    assert(N != NULL);
    N->data = data; 
    N->next = N->previous = NULL;
    return N;
}

void freeNode(Node* pN){
    if (pN != NULL && *pN != NULL){
        free(*pN);
        *pN = NULL;
    }
}
// Access functions -----------------------------------------------------------
int length(List L){
    if (L == NULL){
        printf("List Error: calling Length() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    return L->length;
} // Returns the number of elements in L.

int index(List L){
    if (L == NULL){
        printf("List Error: calling index() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    return L->cursor;
} // Returns index of cursor element if defined, -1 otherwise.

ListElement front(List L){
    if (L == NULL){
        printf("List Error: calling front() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) <= 0){
        printf("List Error: calling front() on EMPTY List reference\n");
        exit(EXIT_FAILURE);
    }
    return L->front->data;
} // Returns front element of L. Pre: length()>0
ListElement back(List L){
    if (L == NULL){
        printf("List Error: calling back() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) <= 0){
        printf("List Error: calling back() on EMPTY List reference\n");
        exit(EXIT_FAILURE);
    }
    return L->back->data;
} // Returns back element of L. Pre: length()>0
ListElement get(List L){
    if (L == NULL){
        printf("List Error: calling get() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) <= 0 && index(L) < 0){
        printf("List Error: calling get() on EMPTY List reference\n");
        exit(EXIT_FAILURE);
    }    
    return L->cursorNode->data;
} // Returns cursor element of L. Pre: length()>0, index()>=0
/*bool equals(List A, List B){
    if( A==NULL || B==NULL ){
      printf("List Error: calling equals() on NULL List reference\n");
      exit(EXIT_FAILURE);
    }
    bool eq;
    Node N, M;

    eq = ( A->length == B->length );
    N = A->front;
    M = B->front;
    while(eq && N != NULL){
      eq = ( N->data==M->data );
      N = N->next;
      M = M->next;
    }
   return eq;
} */// Returns true iff Lists A and B are in same
 // state, and returns false otherwise.

// Manipulation procedures ----------------------------------------------------
void clear(List L){
    if(L == NULL){
      printf("List Error: calling clear() on NULL List reference\n");
      exit(EXIT_FAILURE);
    }
    while(L->front != NULL){
        Node temp = L->front->next;
        freeNode(&L->front);
        L->front = temp;
    }
    L->cursor = -1;
    L->front = L->back = L->cursorNode = NULL;
    L->length = 0;
} // Resets L to its original empty state.
void set(List L, ListElement x){
    if(L == NULL){
      printf("List Error: calling set() on NULL List reference\n");
      exit(EXIT_FAILURE);
    }
    if (length(L) <= 0 || index(L) < 0){
        printf("List Error: calling set() on EMPTY List reference\n");
        exit(EXIT_FAILURE);
    }
    L->cursorNode->data = x;
} // Overwrites the cursor element’s data with x.
 // Pre: length()>0, index()>=0

void moveFront(List L){
    if(L == NULL){
      printf("List Error: calling moveFront() on NULL List reference\n");
      exit(EXIT_FAILURE);
    }
    if (length(L) != 0){
        L->cursor = 0;
        L->cursorNode = L->front;
    }
} // If L is non-empty, sets cursor under the front element,
 // otherwise does nothing.
void moveBack(List L){
    if(L == NULL){
      printf("List Error: calling moveBack() on NULL List reference\n");
      exit(EXIT_FAILURE);
    }
    if (length(L) != 0){
        L->cursor = length(L) - 1;
        L->cursorNode = L->back;
    }
} // If L is non-empty, sets cursor under the back element,
 // otherwise does nothing.
void movePrev(List L){
    if(L == NULL){
      printf("List Error: calling moveBack() on NULL List reference\n");
      exit(EXIT_FAILURE);
    }
    if (L->cursor != -1){
        if (L->cursor == 0){
            L->cursor = -1;
            L->cursorNode = NULL;
        }else{
            L->cursor -=1;
            L->cursorNode = L->cursorNode->previous;
        }
    }
} // If cursor is defined and not at front, move cursor one
 // step toward the front of L; if cursor is defined and at
 // front, cursor becomes undefined; if cursor is undefined
 // do nothing
void moveNext(List L){
    if(L == NULL){
      printf("List Error: calling moveNext() on NULL List reference\n");
      exit(EXIT_FAILURE);
    }
    if (L->cursor != -1){
        if (L->cursor == length(L) - 1){
            L->cursor = -1;
            L->cursorNode = NULL;
        }else{
            L->cursor +=1;
            L->cursorNode = L->cursorNode->next;
        }
    }
} // If cursor is defined and not at back, move cursor one
 // step toward the back of L; if cursor is defined and at
 // back, cursor becomes undefined; if cursor is undefined
 // do nothing

void prepend(List L, ListElement x) {
    // if L is empty then just create a new node with the data x, have its prev and next both be null as that will be the only element
    if(L == NULL){
      printf("List Error: calling prepend() on NULL List reference\n");
      exit(EXIT_FAILURE);
    }
    if (L->cursor == -1){
        L->cursor = 0;
    }
    if (length(L) == 0){
        Node N = newNode(x);
        L->back = N;
        L->front = N;
        L->length++;
        L->cursor++;
    }
    else{
        Node N = newNode(x);
        L->front->previous = N;
        N->next = L->front;
        L->front = N;
        L->length++;
        L->cursor++;
    }
    // if L is not empty, then you want to add a new node containing the data x with its next being the previous front element, then if its a circular linked list
    // then you are going to want to set its previous to the very end of the list
} // Insert new element into L. If L is non-empty,
 // insertion takes place before front element.
void append(List L, ListElement x){
    if(L == NULL){
      printf("List Error: calling append() on NULL List reference\n");
      exit(EXIT_FAILURE);
    }
    // if (L->cursor == -1){
    //     L->cursor = length(L) - 1;
    // }
    if (length(L) == 0){
        Node N = newNode(x);
        L->front = N;
        L->back = N;
        L->length++;
    }else{
        Node N = newNode(x);
        L->back->next = N;
        N->previous = L->back;
        L->back = N;
        L->length++;
    }
} // Insert new element into L. If L is non-empty,
 // insertion takes place after back element.

void insertBefore(List L, ListElement x){
    if(L == NULL){
      printf("List Error: calling insertBefore() on NULL List reference\n");
      exit(EXIT_FAILURE);
    }
    if (length(L) <= 0 || index(L) <0 ){
      printf("List Error: calling insertBefore() on EMPTY List reference\n");
      exit(EXIT_FAILURE);
    }
    Node N = newNode(x);
    if (index(L) == 0){
        N->previous = NULL; 
        L->front = N;
    }else{
        N->previous = L->cursorNode->previous;
        N->previous->next = N;
    }
    N->next = L->cursorNode;
    L->cursorNode->previous = N;
    L->cursor += 1;
    L->length += 1;

} // Insert new element before cursor.
 // Pre: length()>0, index()>=0

void insertAfter(List L, ListElement x){
    if(L == NULL){
      printf("List Error: calling insertAfter() on NULL List reference\n");
      exit(EXIT_FAILURE);
    }
    if (length(L) <= 0 || index(L) < 0){
      printf("List Error: calling insertAfter() on EMPTY List reference\n");
      exit(EXIT_FAILURE);
    }

    Node N = newNode(x);
    if (L->cursor == length(L) - 1){
        N->next = NULL;
        L->back = N;
    }else{
        N->next = L->cursorNode->next;
        N->next->previous = N;
    }
    N->previous = L->cursorNode;
    L->cursorNode->next = N;
    L->length++;
} // Insert new element after cursor.
 // Pre: length()>0, index()>=0
void deleteFront(List L){
    if(L == NULL){
      printf("List Error: calling deleteFront() on NULL List reference\n");
      exit(EXIT_FAILURE);
    }
    if(length(L) <= 0){
        printf("List Error: calling deleteFront() on EMPTY List reference\n");
        exit(EXIT_FAILURE);
    }
    if(L->cursor == 0) {
        L->cursorNode = NULL;
        L->cursor--;
    }else{
        L->cursor--;
    }
    if (length(L) == 1){
        freeNode(&L->front);
        L->front = L->back = NULL;
        L->length = 0;

    }else{
        Node temp = L->front->next;
        freeNode(&L->front);
        L->front = temp;
        L->front->previous = NULL; 
        L->length--;
    }
} // Delete the front element. Pre: length()>0
void deleteBack(List L){
    if(L == NULL){
        printf("List Error: calling deleteBack()) on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if(length(L) <= 0){
        printf("List Error: calling deleteBack() on EMPTY List reference\n");
        exit(EXIT_FAILURE);
    }
    if (length(L) == 1){
        freeNode(&L->back);
        L->front = L->back = NULL;
    }else{
        Node temp = L->back->previous;
        L->back->previous->next = NULL;
        freeNode(&L->back); 
        L->back = temp;
    } 
    if(L->cursor == length(L) - 1) {
        L->cursor = -1;
        L->cursorNode = NULL;
    }
    L->length--;
} // Delete the back element. Pre: length()>0
void delete(List L){
    if(L == NULL){
        printf("List Error: calling delete() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (index(L) < 0 || length(L) <= 0){
        printf("List Error: calling delete() on EMPTY List reference\n");
        exit(EXIT_FAILURE);
    }
    if(L->cursor == 0){
        deleteFront(L);
    }
    else if(L->cursor == length(L) - 1){
        deleteBack(L);
    }
    else{
        L->cursorNode->next->previous = L->cursorNode->previous;
        L->cursorNode->previous->next = L->cursorNode->next;
        L->cursor = -1;
        freeNode(&L->cursorNode);
        L->length--;
        L->cursorNode = NULL;
    }
} // Delete cursor element, making cursor undefined.
 // Pre: length()>0, index()>=0

// Other operations -----------------------------------------------------------
/*void printList(FILE* out, List L){
    Node N = NULL;

    if(L == NULL){
        printf("Queue Error: calling printList() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    for(N = L->front; N != NULL; N = N->next){
        // as long as it isn't the last element in the list we want to separate the items by a space.
        if (L->back->data != N->data) {
            fprintf(out,"%d ", N->data); 
        }
        // the last element in the list, we dont want a space after it
        else {
            fprintf(out,"%d", N->data);
        }
    }
}*/ // Prints to the file pointed to by out, a
 // string representation of L consisting
 // of a space separated sequence of integers,
// with front on left.
/*List copyList(List L){
    List copy = newList();
    Node N = NULL;
    for(N = L->front; N != NULL; N = N->next){
        append(copy, N->data);
    }
    return copy;
} // Returns a new List representing the same integer
 // sequence as L. The cursor in the new list is undefined,
// regardless of the state of the cursor in L. The state
// of L is unchanged.*/


