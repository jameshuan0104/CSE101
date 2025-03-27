/*
*James Huang, hhuan143
*2023 spring CSE101 PA#8
*WordFrequency.cpp
*main for pa8
*/

#include<string>
#include<iostream>
#include<stdexcept>
#include <fstream>
#include<stdlib.h>
#include"Dictionary.h"
#include <cstring>
#include<bits/stdc++.h>

using namespace std;

int main(int argc, char * argv[]){
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


    Dictionary D;
	int token_count, line_count;
	size_t begin, end, len;
	string line;
	string tokenBuffer;
	string token;
	//string delim = " "; 
	string delim = " \t\\\"\',<.>/?;:[{]}|`~!@#$%^&*()-_=+0123456789";
	// read each line of input file, then count and print tokens 
	line_count = 0;
	while( getline(in, line) )  {

		line_count++;
		len = line.length();
	  
		// get tokens in this line
		token_count = 0;
		tokenBuffer = "";

		// get first token
		begin = min(line.find_first_not_of(delim, 0), len);
		end   = min(line.find_first_of(delim, begin), len);
		token = line.substr(begin, end-begin);
	  	transform(token.begin(), token.end(), token.begin(), ::tolower);
		while( token!="" ){  // we have a token
			// update token buffer
			tokenBuffer += "   "+token+"\n";
			token_count++;
			if (D.contains(token)){
				D.getValue(token)++;
			}else{
				D.setValue(token, 1);
			}
			// get next token
			begin = min(line.find_first_not_of(delim, end+1), len);
			end   = min(line.find_first_of(delim, begin), len);
			token = line.substr(begin, end-begin);
			transform(token.begin(), token.end(), token.begin(), ::tolower);
		}

		// print tokens in this line
		//out << "line " << line_count << " contains " << token_count;
		//ut << " token" << (token_count==1?"":"s") << endl;
		//out << tokenBuffer << endl;
	}


	out << D << endl;


	in.close();
    out.close();

	return(EXIT_SUCCESS);
}