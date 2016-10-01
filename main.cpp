//Jamin Chen

#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <limits>
#include <sstream>
#include "hashmap.h"

class Dummy {
public:
    int IQ;
};

void hashmapDiag (Hashmap &hashmap)
{
    std::cout << std::endl;
    std::cout << "======================== Diagnostic =========================" << std::endl;	
    std::cout << "##### Hashmap size: " << hashmap.size() << std::endl;
    std::cout << "##### No. of key-value pairs: " << hashmap.storedObjects() << std::endl;
    std::cout << "##### Load factor: " << hashmap.load() << std::endl;
}

int main()
{
    //
    // Initialize hashmap assuming the user will enter 1024 key-value pairs.
    // Run diagnostics.
    //
    Hashmap hashmap(1024);
    hashmapDiag(hashmap);

    //
    // Demonstrate setting and getting string values into/from the hashmap.
    //
    std::cout << std::endl << "=================== Case 1: String Value ====================" << std::endl;

    std::string s = "ABCD";
    std::string *sp;
    std::cout << "##### Set *key1* with string value: " << s << std::endl;
    hashmap.setkv("key1", s);
    sp = NULL;
    sp = (std::string *)hashmap.get("key1");
    std::cout << "##### Get *key1* with string value: " << *sp  << std::endl;

    //
    // Demonstrate setting and getting integer values into/from the hashmap.
    //
    std::cout << std::endl << "=================== Case 2: Integer Value ===================" << std::endl;

    int n = 12345;
    int *np;
    std::cout << "##### Set *key2* with integer value: " << n << std::endl;
    hashmap.setkv("key2", n);
    np = NULL;
    np = (int *)hashmap.get("key2");
    std::cout << "##### Get *key2* with integer value: " << *np  << std::endl;

    //
    // Demonstrate setting and getting arrays into/from the hashmap.
    //
    std::cout << std::endl << "==================== Case 3: Array Value ====================" << std::endl;

    char c[5] = {'A', 'B', 'C', 'E', 'F'};
    char *cp;
    std::cout << "##### Set *key3* with array value: {" << *c << ", " << *(c + 1) << ", " << *(c + 2) << ", " << *(c + 3) << ", " << *(c + 4) << "} " << std::endl;
    hashmap.setkv("key3", c);
    cp = NULL;
    cp = (char *)hashmap.get("key3");
    std::cout << "##### Get *key3* with array value: {" << *cp << ", " << *(cp + 1) << ", " << *(cp + 2) << ", " << *(cp + 3) << ", " << *(cp + 4) << "} " << std::endl;

    //
    // Demonstrate setting and getting arbitrary dummy class into/from the hashmap.
    //
    std::cout << std::endl << "==================== Case 4: Class Value ====================" << std::endl;

    Dummy dummy;
    dummy.IQ = -9;
    Dummy* dummyp;
    std::cout << "##### Set *key4* with dummy class value: " << dummy.IQ << std::endl;
    hashmap.setkv("key4", dummy);
    dummyp = NULL;
    dummyp = (Dummy *)hashmap.get("key4");
    std::cout << "##### Get *key4* with dummy class value: " << (*dummyp).IQ  << std::endl;

    hashmapDiag(hashmap);

    //
    // DEBUG ROUTINE:
    // Print memory locations of data stored in hashmap.
    //
    std::cout << std::endl << "================== Print hashmap content ====================" << std::endl;
    hashmap.dump();

    //
    // Demonstrate deleting a specific key-value pair.
    //
    std::cout << std::endl << "================== Delete hashmap content ===================" << std::endl;

    std::cout << "##### Delete *key1* and return the value." << std::endl;
    std::cout << "##### Value of *key1* is: " << (int *)(hashmap.del("key1").data) << std::endl;
    std::cout << std::endl << "##### Print hashmap content: " << std::endl;

    //
    // DEBUG ROUTINE:
    // Print memory locations of data stored in hashmap.
    //
    hashmap.dump();

    //
    // Demonstrate getting a nonexistent key-value pair.
    //
    std::cout << std::endl << "================== Get non-existing content =================" << std::endl;
    std::cout << "##### Get value associated with *key100*" << std::endl;
    sp = (std::string *)hashmap.get("key100");
    if (!sp) {
       std::cout << "!!!!! No value associated with *key100*" << std::endl;
    }

    //
    // Demonstrate deleting a nonexistent key-value pair.
    //
    std::cout << std::endl << "================= Delete non-existing content ===============" << std::endl;
    std::cout << "##### Delete value associated with *key100*" << std::endl;
    double *dp = (double *)hashmap.del("key100");
    if (dp == NULL) {
       std::cout << "!!!!! Trying to delete nonexisting key100" << std::endl << std::endl;
    }

    std::cout << "END OF TEST CASES" << std::endl << std::endl;

    exit(0);
}
