#ifndef LEVELSLINKEDLIST_H
#define LEVELSLINKEDLIST_H

#include "linkedList.h"

template <class t>
class LevelsLL : public LinkedList<t>
{
public:
    ~LevelsLL();
    void deleteNodes() override;
    void insert(const t &newData) override;
};

// destructor
template <class t>
LevelsLL<t>::~LevelsLL()
{
    this->deleteNodes();
}

// deletes all levels and nodes
template <class t>
void LevelsLL<t>::deleteNodes()
{
    if (!(this->isEmptyList()))
    {
        Node<t> *temp;
        while (this->head != nullptr) 
        {
            temp = this->head;   // temp now points to same node head does
            this->head = this->head->forwLink;   // moves head pointer forward one
            delete temp->data;   // deletes the node's level from everywhere
            delete temp;   // deletes node temp is pointing to
        }
        this->tail = nullptr;
        this->count = 0;
    }
}

// insert newNode
template <class t>
void LevelsLL<t>::insert(const t &newData)
{
    // create a new node
    Node<t> *newNode = new Node<t>(newData, nullptr, nullptr);

    // add node if list is empty
    if (this->isEmptyList())
    {
        this->head = newNode;
        this->tail = newNode;
        this->count++;
        return;
    }

    // insert node at tail
    this->tail->forwLink = newNode;
    newNode->prevLink = this->tail;
    this->count++;
    
    // update tail pointer
    this->tail = newNode;
}

#endif