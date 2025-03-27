/*
*James Huang, hhuan143
*2023 spring CSE101 PA#5
*ListTest.cpp
*simple test for List.cpp
*/
#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"

using namespace std;

int main(){
	List A;
	List C;
	for(int i =1; i<=10; i++){
      A.insertAfter(i);
      C.insertAfter(i);
    }
    cout << "A = " << A << endl;
    cout << "A.position() = " << A.position() << endl;
    cout << "A.Length() = " << A.length() << endl;

    A.moveBack();
    cout << "A.position() = " << A.position() << endl;
    A.moveFront();

    A.moveNext();
    cout << "A.peekNext() = " << A.peekNext() << endl;
    cout << "A.peekPrev() = " << A.peekPrev() << endl;

    A.eraseBefore();
    A.eraseAfter();
    cout << "A = " << A << endl;
    A.insertBefore(-10);
    A.insertAfter(-10);
    cout << "A = " << A << endl;
    cout << "A.position() = " << A.position() << endl;
    A.setAfter(9);
    A.setBefore(10);
    cout << "A = " << A << endl;

    List B;

    for(int i =1; i<=10; i++){
      B.insertAfter(5);
    }

    cout << "B = " << B << endl;
    List F = A.concat(B);
    cout << "F = " << F << endl;
    F.cleanup();
    F.findNext(1);
    F.moveBack();
    F.findPrev(10);
    cout << "F = " << F << endl;

    if(A == C){
    	cout << "List A == C" << endl;
    }







	return ( EXIT_SUCCESS );
}