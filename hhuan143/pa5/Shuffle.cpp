/*
*James Huang, hhuan143
*2023 spring CSE101 PA#5
*Shuffle.cpp
*the main file for List
*/

#include<iostream>
#include<fstream>
#include<string>
#include "List.h"
using namespace std;

void shuffle(List& D);

int main(int argc, char * argv[]){
	if(argc != 2){
    	cerr << "Usage: " << argv[0] << " <n>" << endl;
        return(EXIT_FAILURE);
    }

    std::cout << "deck size       shuffle count" << std::endl;
    std::cout << "------------------------------" << std::endl;

    int n = stoi(argv[1]); 
    List D;
    List OG;
    for (int i = 1; i <= n; i++){
    	int counter = 0;
    	D.insertBefore(i);
    	OG.insertBefore(i);

    	shuffle(D);
    	counter++;

    	while (!OG.equals(D)){
    		shuffle(D);
    		counter++;
    	}

	    if(i <= 9){
			std::cout << " "<< i << "               "<< counter <<std::endl;
		}else if(i <= 99){
			std::cout << " "<< i << "              "<< counter <<std::endl;
		}else{
	        std::cout << " "<< i << "             "<< counter <<std::endl;
	    }
	}
	return (EXIT_SUCCESS);
}
void shuffle(List& D){
	int n = D.length();
	if (n == 1){
		//cout << "first" << endl;
		return;
	}
	int half = n / 2;
	List A;
	List B;
	B = D;
	B.moveFront();
	//cout << "sdfdsf" << endl;
	//cout << B << endl;
	for (int i = 0; i < half; i++) {
    	A.insertBefore(B.front());
    	B.eraseAfter();
	}
	//cout << A << endl;
	//cout << B << endl;
	D.clear();
	A.moveFront();
	B.moveFront();
	//cout << "A = " << A << endl;
	//cout << "B = " << B << endl;
	while (A.position() != A.length() || B.position() != B.length()){
		if (B.position() != B.length()){
			D.insertBefore(B.peekNext());
			B.moveNext();
		}
		if (A.position() != A.length()){
			D.insertBefore(A.peekNext());
			A.moveNext();
		}
	}
	//cout << "D= " << D << endl;

	

}