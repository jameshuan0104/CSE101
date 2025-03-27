/*
*James Huang, hhuan143
*2023 spring CSE101 PA#6
*Arithmetic.cpp
*main file for BigInteger.cpp
*/

#include "BigInteger.h"
#include <fstream>

using namespace std;

int main(int argc, char *argv[]) {
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

    string num1;
    string num2;
    in >> num1;
    in >> num2;

    BigInteger A = BigInteger(num1);
    BigInteger B = BigInteger(num2);

    BigInteger int2 = BigInteger("2");
    BigInteger int3 = BigInteger("3");
    BigInteger int9 = BigInteger("9");
    BigInteger int16 = BigInteger("16");

    out << (A) << endl << endl;
    
    out << (B) << endl << endl;
    
    out << (A + B) << endl << endl;
    
    out << (A - B) << endl << endl;
    
    out << (A - A) << endl << endl;
    
    out << ((int3 * A) - (int2* B)) << endl << endl;
    
    out << (A * B) << endl << endl;    
    
    out << (A * A) << endl << endl;
    
    out << (B * B) << endl << endl;

    out << ((int9 * (A * A * A * A)) + (int16 * (B * B * B * B * B))) << endl << endl;

    in.close();
    out.close();

    return 0;
}