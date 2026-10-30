#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "node.h"
#include <iostream>

// stores data in an array of linked lists
// inserts duplicate items at end of linked list

class HashTable
{
public:
    HashTable();
    ~HashTable();

    void insert(int num);
    void remove(int num);
    bool search(int num);

    int getInserts();
    int getDuplicates(int num);
    double getCollisions();

private:
    int hashIndex;
    int HT_SIZE = 10;
    Node<int> **htArr;
    
    int inserts = 0;
    int collisions = 0;

    int hash(int num);
};

// default constructor
HashTable::HashTable()
{
    htArr = new Node<int>*[HT_SIZE]();
}

// destructor
HashTable::~HashTable()
{
    for (int i = 0; i < HT_SIZE; ++i)
    {
        Node<int> *current = htArr[i];

        while (current != nullptr)
        {
            Node<int> *next = current->forwLink;

            delete current;

            current = next;
        }
    }

    delete[] htArr;
}

// insert number into hash table
void HashTable::insert(int num)
{
    // call hash function
    hashIndex = hash(num);

    Node<int> *current = htArr[hashIndex];

    // check for collisions
    if (htArr[hashIndex] != nullptr)
    {
        collisions++;
    }

    Node<int> *newNode = new Node<int>(num);
    
    // insert num into hash table
    if (htArr[hashIndex] == nullptr)
    {
        htArr[hashIndex] = newNode;
        inserts++;
    }
    else
    {
        current = htArr[hashIndex];

        while (current->forwLink != nullptr)
        {
            current = current->forwLink;
        }

        current->forwLink = newNode;
        inserts++;
    }
}

// remove number from hash table
void HashTable::remove(int num)
{
    if (!search(num)) 
    {
        std::cout << "Nothing to remove." << std::endl;
        return;
    }

    hashIndex = hash(num);

    Node<int> *current = htArr[hashIndex];
    Node<int> *trailCurrent = nullptr;

    while (current->forwLink != nullptr)   // move to end of LL
    {
        trailCurrent = current;
        current = current->forwLink;
    }

    if (trailCurrent == nullptr)
    {
        htArr[hashIndex] = nullptr;
    }
    else
    {
        trailCurrent->forwLink = nullptr;
    }

    delete current;
}

// search for number within hash table
bool HashTable::search(int num)
{
    // call hash function
    hashIndex = hash(num);

    Node<int> *current = htArr[hashIndex];

    while (current != nullptr)
    {
        if (current->data == num)
        {
            return true;
        }
        else 
        {
            current = current->forwLink;
        }
    }

    return false;
}

// get insert count
int HashTable::getInserts()
{
    return inserts;
}

// get duplicate count
int HashTable::getDuplicates(int num)
{
    int hashIndex = hash(num);

    int count = 0;
    
    Node<int> *current = htArr[hashIndex];

    while (current != nullptr)
    {
        if (current->data == num)
        {
            count++;
        }

        current = current->forwLink;
    }
    
    return count;
}

// get collision count
double HashTable::getCollisions()
{
    return collisions;
}

// hash number
int HashTable::hash(int num)
{
    hashIndex = num % HT_SIZE;
    
    return hashIndex;
}

#endif