//Jamin Chen

#include <cstdlib>
#include <climits>
#include <string>
#include <iostream>
#include "hashmap.h"



//
// List functions
//

List::List()
{
    head = NULL;
}


List::~List()
{
    purge();
}

//
// function for adding new element to our linked list
//
bool List::addNode(std::string key, AnyType& value)
{
    NodePtr current;
    NodePtr n = new node;

    n->next = NULL;
    n->key = key;
    n->value = value;

    if (head != NULL)
    {
        current = head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = n;

        return true;
    }
    else
    {
        head = n;

        return true;
    }

    return false;
}

//
// function for deleting element from the linked list
//
AnyType List::deleteNode(std::string key)
{
    NodePtr temp, current;
    NodePtr delPtr = NULL;

    AnyType t;
    t.data = NULL;

    current = head;
    while (current != NULL && current->key != key)
    {
        temp = current;
        current = current->next;
    }

    if (current == NULL)
    {
        //std::cout << key << "is not in the list" << std::endl;
        return t;
    }
    else
    {
        delPtr = current;
        if (delPtr == head)
        {
            head = NULL;
            temp = NULL;
        }

	if (temp)
	{
	    temp->next = current->next;
	}

        AnyType value = delPtr->value;
        delete delPtr;
        //std::cout << key << " was successfully deleted from the list." << std::endl;

        return value;
    }
}

void List::printList()
{
    NodePtr current;
    current = head;
    while (current != NULL)
    {
        std::cout << "##### " << current->key  << "     " << current->value.data << std::endl;
        current = current->next;
    }
}


void List::purge()
{
    NodePtr current;

    while (head)
    {
	current = head;
	head = head->next;
	delete current;
    }
};


int List::sizeOf()
{
    NodePtr current;
    current = head;
    int i = 0;
    while (current != NULL)
    {
        i++;
        current = current->next;
    }
    return i;
}

AnyType List::getValue(std::string key)
{
    NodePtr current;
    AnyType t;
    t.data = NULL;

    if (head == NULL)
    {
        return t;
    }
    else
    {
        current = head;
        while (current != NULL && current->key != key)
        {
            current = current->next;
        }

	return current ? current->value : t;
    }
}


//
// Hashmap functions
//

Hashmap::Hashmap(int numObjects)
{
    //
    //NOTE: Assuming that the user enters a fixed number of key-value pairs, the constructor
    //      function will scale the hashmap's size such that the load factor is 0.75, because
    //      this is the default for Java's hashmap class and allows for relatively optimized
    //      performance.
    //

    bucketSize = numObjects * 4 / 3;
    buckets.resize(bucketSize);
};

Hashmap::~Hashmap()
{
    for (std::vector<List>::iterator it = buckets.begin(); it != buckets.end(); ++it)
	(*it).purge();

    std::vector<List> v;
    buckets.clear();
    buckets.swap(v);
};

int Hashmap::size()
{
    return buckets.size();
}


int Hashmap::storedObjects()
{
    int storedObjects = 0;

    for (std::vector<List>::iterator it = buckets.begin(); it != buckets.end(); ++it)
    {
        storedObjects += (*it).sizeOf();
    }

    return storedObjects;
}


float Hashmap::load()
{
    return static_cast< float >(storedObjects()) / static_cast< float >(buckets.size());
}


void Hashmap::dump()
{
    for (std::vector<List>::iterator it = buckets.begin(); it != buckets.end(); ++it)
    {
	   (*it).printList();
    }
}


unsigned int Hashmap::hashThis(std::string key)
{
    //
    // The following hashing algorithm for strings is taken from Oracle's Java hashmap documentation.
    //
    unsigned int hashCode = 0;
    for (unsigned int i = 1; i < key.length(); i++)
    {
        if (hashCode > (UINT_MAX - key[i])/ 31) // modulo 31 to prevent overflow
        {
            hashCode = hashCode % 31;
        }
        hashCode = 31 * hashCode + key[i];
    }

    hashCode = hashCode % bucketSize;

    return hashCode;
}


AnyType Hashmap::get(std::string key)
{
    AnyType output;

    output = buckets[hashThis(key)].getValue(key);

    return output;
}


AnyType Hashmap::del(std::string key)
{
    AnyType output;

    output = buckets[hashThis(key)].deleteNode(key);
    /*
    if (!output.data)
    {
        std::cout << "##### No value associated with given key." << std::endl;
    }
    else
    {
        std::cout << "##### Successfully deleted key with value " << output.data << std::endl;
    }
    */

    return output; 
}

