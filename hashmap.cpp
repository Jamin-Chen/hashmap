#include <cstdlib>
#include <climits>
#include <string>
#include <iostream>
#include "hashmap.h"

List::List()    //constructor function
{
    head = NULL;
}

std::vector<List> buckets;
int numBuckets;
int numObjects;

unsigned int hashThis (std::string key);

bool List::addNode(std::string addKey, std::string &addValue) //function for adding new element to our linked list
{
    nodePtr current;
    nodePtr n = new node;
    n->next = NULL;
    n->key = addKey;
    n->value = addValue;

    if (head != NULL) //if TRUE then we have an existing list
    {
        current = head; //current pointer points to front of list
        while (current->next != NULL) //check if we are at the end of the list
        {
            current = current->next;  //push current pointer to last node in list
        }
        current->next = n; //point to new node we created
        return true;
    }
    else //if it is a new list
    {
        head = n; //make the new node we created the head of list
        return true;
    }
}

std::string List::deleteNode(std::string delKey)
{
    std::string value;
    nodePtr temp, current;
    nodePtr delPtr = NULL;
    temp = head;
    current = head;
    while (current != NULL && current->key != delKey)
    {
        temp = current; //keep the temp pointer trailing behind
        current = current->next;
    } //loop exits either when we pass through the entire list or find the value we want
    if (current == NULL) // data not found
    {
        std::cout << delKey << "is not in the list" << std::endl;
        delete delPtr;
        return NULL;
    }
    else // data was found
    {
        value = current->value;
        delPtr = current;
        current = current->next; //bump the current pointer ahead
        temp->next = current; //patches the list
        if (delPtr == head) //check if our list is empty
        {
            head = head->next;
            temp = NULL;
        }
        delete delPtr;
        std::cout << delKey << "was successfully deleted from the list." << std::endl;
        return value;
    }
}

void List::PrintList()
{
    nodePtr current;
    current = head;
    while (current != NULL)
    {
        std::cout << current->key  << " ";
        current = current->next;
    }
}

int List::sizeOf()
{
    nodePtr current;
    current = head;
    int i = 0;
    while (current != NULL)
    {
        i++;
        current = current->next;
    }
    return i;
}

int List::countNode()
{
    nodePtr current;
    current = head;
    int counter = 0;
    while (current != NULL)
    {
        counter++;
        current = current->next;
    }
    std::cout << "Number of current items in bucket is: " << counter << std::endl;
    return counter;
}

std::string List::getValue(std::string getKey)
{
    nodePtr current;
    if (head == NULL) //nonexistent list
    {
        std::cout << "No value associated with given key." << std::endl;
        return NULL;
    }
    else // existing list, must search for data
    {
        while (current != NULL && current->key != getKey)
        {
            current = current->next;
        }
        if (current == NULL) // searched through list, no associated value.
        {
            std::cout << "No value associated with given key." << std::endl;
            return NULL;
        }
        else
        {
            std::cout << "The associated value with the given key is: " << current -> key << std::endl;
            return  current->value;
        }
    }
}

void constructor (int numObjects)
{
    buckets.resize(numObjects * 4 / 3); // initialize hashmap capacity
}

bool setkv(std::string key, std::string &value)                              //boolean set(key, value): stores the given key/value pair in the hash map.
{                                                                           //Returns a boolean value indicating success / failure of the operation.
    if (buckets[hashThis(key)].addNode(key, value) == true)
    {
        return true;
    }
    else
    {
        return false;
    }
}

std::string get(std::string key)                                            //get(key): return the value associated with the given key,
{                                                                           //or null if no value is set.
    std::string output;
    std::cout << "Please enter the string key: ";
    std::cin >> key;
    output = buckets[hashThis(key)].getValue(key);
    if (output.empty())
    {
        std::cout << "The associated value is NULL" << std::endl;
        return output;
    }
    else
    {
        std::cout << "The associated value is " << output << std::endl;
        return output;
    }
}

std::string del(std::string key)                                         //delete(key): delete the value associated with the given key, returning the
{                                                                           //value on success or null if the key has no value.
    std::string output;
    std:: cout << "Please enter the string key: ";
    std::cin >> key;
    return buckets[hashThis(key)].deleteNode(key);
}

float load()
{
    int storedObjects = 0;
    for (int i =0; i < numBuckets; i++)
    {
        storedObjects = storedObjects + buckets[i].sizeOf();
    }
    return static_cast< float >(storedObjects) / static_cast< float >(numBuckets);
}

unsigned int hashThis (std::string key)
{
    unsigned int hashCode = 0;
    for (unsigned int i = 1; i < key.length(); i++)
    {
        if (hashCode > (UINT_MAX - key[i])/ 31) // modulo 31 to prevent overflow
        {
            hashCode = hashCode % 31;
        }
        hashCode = 31 * hashCode + key[i]; // hash algorithm taken from Oracle's Java hashmap documentation
    }
    hashCode = hashCode % numBuckets;
    return hashCode;
}

