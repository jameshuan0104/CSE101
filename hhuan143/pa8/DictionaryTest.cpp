/*
*James Huang, hhuan143
*2023 spring CSE101 PA#8
*DictionaryTest.cpp
*simple test
*/

#include <iostream>
#include "Dictionary.h"

using namespace std;

int main() {
    Dictionary dict;

    dict.setValue("chocolate", 10);
    dict.setValue("gummy bears", 5);
    dict.setValue("lollipop", 8);
    dict.setValue("caramel", 3);

    cout << "Dictionary size: " << dict.size() << endl;
    cout << "Dictionary contents:\n" << dict << endl;

    cout << "Quantity of 'gummy bears': " << dict.getValue("gummy bears") << endl;
    dict.getValue("gummy bears") = 7;
    cout << "New quantity of 'gummy bears': " << dict.getValue("gummy bears") << endl;

    dict.remove("lollipop");

    cout << "Updated dictionary:\n" << dict << endl;

    return EXIT_SUCCESS;
}

