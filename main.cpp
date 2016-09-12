#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
#include "hashmap.h"

int main(int argc, char** argv)
{
    std::string key, value;
    std::ifstream infile("paragraph.txt");
    bool inputFailed = false;
    int failedInputs = 0;

    std::cout << "Please enter the number of key-value pairs: ";
    std::cin >> numObjects; //Takes in a user-defined number of objects
    constructor(numObjects);


    //part below doesn't work rn
    for (int i = 0; i < numObjects; i++)
    {
                std::cout << "pass" << std::endl;
            infile >> key >> value;

            if (setkv(key, value) == false)
            {
                inputFailed = true;
                failedInputs++;
            }
    }

    if (inputFailed)
    {
        std::cout << "Not all elements were correctly stored into the hashmap." << std::endl;
    }
    else
    {
        std::cout << "All elements were correctly stored into the hashmap." << std::endl;
    }

    std::cout << failedInputs << " instances of failure." << std::endl;

    return 0;
}
