/*
*James Huang, hhuan143
*2023 spring CSE101 PA#7
*DictionaryTest.cpp
*simple test for ADT
*/

#include <iostream>
#include <string>
#include "Dictionary.h"

using namespace std;

int main() {
    Dictionary dict;

    dict.setValue("lion", 1);
    dict.setValue("elephant", 2);
    dict.setValue("tiger", 3);
    dict.setValue("giraffe", 4);

    cout << "Dictionary size: " << dict.size() << endl;
    cout << dict << endl;

    cout << "Value for 'elephant': " << dict.getValue("elephant") << endl;
    cout << "Value for 'tiger': " << dict.getValue("tiger") << endl;

    dict.remove("elephant");

    cout << "Dictionary size after removing 'elephant': " << dict.size() << endl;
    cout << dict << endl;

    dict.setValue("zebra", 5);

    cout << "Dictionary size after adding 'zebra': " << dict.size() << endl;
    cout << dict << endl;

    cout << "Animals in the dictionary:" << endl;
    for (dict.begin(); dict.hasCurrent(); dict.next()) {
        string animal = dict.currentKey();
        int value = dict.currentVal();
        cout << animal << ": " << value << endl;
    }

    cout << endl;

    cout << "Pre-string representation of the dictionary: " << endl;
    cout << dict.pre_string() << endl;

    return EXIT_SUCCESS;
}

