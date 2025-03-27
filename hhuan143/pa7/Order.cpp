/*
*James Huang, hhuan143
*2023 spring CSE101 PA#7
*Order.cpp
*main file 
*/

#include<string>
#include<iostream>
#include<stdexcept>
#include <fstream>
#include<stdlib.h>
#include"Dictionary.h"

using namespace std;

int main(int argc, char * argv[]){
	Dictionary D;
	ifstream in;
	ofstream out;
	if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
        return (EXIT_FAILURE);
    }

    in.open(argv[1]);
    if(!in.is_open()){
        cerr << "Unable to open file " << argv[1] << " for reading" << endl;
        return(EXIT_FAILURE);
    }

    out.open(argv[2]);
    if(!out.is_open()){
        cerr << "Unable to open file " << argv[2] << " for writing" << endl;
        return(EXIT_FAILURE);
    }
    string s; 
    int i = 1;
	while(getline(in,s)){
		D.setValue(s, i);
		i++;
	}
	out << D.to_string() << endl;
	out << D.pre_string() << endl;

    in.close();
    out.close();

	return(EXIT_SUCCESS);
}