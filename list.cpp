#include <cstdlib>
#include <string>
#include <iostream>
#include "list.h"

List::List()
{
    head = NULL;
    current = NULL;
    temp = NULL;

}

bool List::addNode(std::string addKey, std::string addValue) //function for adding new element to our linked list
{
    nodePtr n = new node;
    n -> next = NULL;
    n -> key = addKey;
    n -> value = addValue;

    if (head != NULL) //if TRUE then we have an existing list
    {
        current = head; //current pointer points to front of list
        while (current -> next != NULL) //check if we are at the end of the list
        {
            current = current -> next;  //push current pointer to last node in list
        }
        current -> next = n; //point to new node we created
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
    nodePtr delPtr = NULL;
    temp = head;
    current = head;
    while (current != NULL && current -> key != delKey)
    {
        temp = current; //keep the temp pointer trailing behind
        current = current -> next;
    } //loop exits either when we pass through the entire list or find the value we want
    if (current == NULL) // data not found
    {
        std::cout << delKey << "is not in the list" << std::endl;
        delete delPtr;
        return NULL;
    }
    else // data was found
    {
        value = current -> value;
        delPtr = current;
        current = current -> next; //bump the current pointer ahead
        temp -> next = current; //patches the list
        if (delPtr == head) //check if our list is empty
        {
            head = head -> next;
            temp = NULL;
        }
        delete delPtr;
        std::cout << delKey << "was successfully deleted from the list." << std::endl;
        return value;
    }
}

void List::PrintList()
{
    current = head;
    while (current != NULL)
    {
        std::cout << current -> key  << " ";
        current = current -> next;
    }
}

int List::countNode()
{
    current = head;
    int counter = 0;
    while (current != NULL)
    {
        counter++;
        current = current -> next;
    }
    std::cout << "Number of current items in bucket is: " << counter << std::endl;
    return counter;
}

std::string List::getValue(std::string getKey)
{
    if (head == NULL) //nonexistent list
    {
        std::cout << "No value associated with given key." << std::endl;
        return NULL;
    }
    else // existing list, must search for data
    {
        while (current != NULL && current -> key != getKey)
        {
            current = current -> next;
        }
        if (current == NULL) // searched through list, no associated value.
        {
            std::cout << "No value associated with given key." << std::endl;
            return NULL;
        }
        else
        {
            std::cout << "The associated value with the given key is: " << current -> key << std::endl;
            return  current -> value;
        }
    }
}

