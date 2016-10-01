//Jamin Chen

#ifndef HASHMAP_H
#define HASHMAP_H

#include<vector>

class AnyType {

 public:
    void *data;
    template <typename T>
    operator T ()
    {
      return const_cast<T>(reinterpret_cast<const T>(data));
    }
};

typedef struct node
{
    std::string key;
    AnyType value;
    struct node *next;
} Node, *NodePtr;


class List
{
  private:

    NodePtr head;

  public:
    List();
    ~List();
    void printList();
    void purge();
    int sizeOf();

    bool addNode(std::string key, AnyType& value);
    AnyType deleteNode(std::string key);
    AnyType getValue(std::string key);
};


class Hashmap
{
  private:
    int bucketSize;
    int loadCapacity;
    std::vector<List> buckets;

  public:
    Hashmap(int numObjects);
    ~Hashmap();
    unsigned int hashThis(std::string key);

    //
    // Stores the given key/value pair in the hash map. 
    // Returns a boolean value indicating success / failure of the operation.
    //
    template<typename T>
    bool setkv(std::string key, T& value)
    {
	AnyType input;

	input.data = (void *)&value;
	return buckets[hashThis(key)].addNode(key, input);
    }

    //
    // Returns the value associated with the given key, or null if no value is set.
    //
    AnyType get(std::string key);

    //
    // Deletes the value associated with the given key, returning the value on success
    // or null if the key has no value.
    //
    AnyType del(std::string key);
    int storedObjects();
    int size();
    float load();
    void dump();
};


#endif // HASHMAP_H
