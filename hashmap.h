#ifndef HASHMAP_H
#define HASHMAP_H

#include<vector>

bool setkv(std::string key, std::string &value);
std::string get(std::string key);
std::string del(std::string key);
float load();
void constructor(int numObjects);

class List
{
private:

    typedef struct node
    {
        std::string key;
        std::string value;
        node* next;
    }* nodePtr;

    nodePtr head;

public: //functions that can manipulate the data
    List();
    bool addNode(std::string addKey, std::string &addValue);
    std::string deleteNode(std::string delKey);
    void PrintList();
    int countNode();
    std::string getValue(std::string getKey);
    int sizeOf ();
};

extern std::vector<List> buckets;
extern int numBuckets;
extern int numObjects;

#endif // HASHMAP_H
