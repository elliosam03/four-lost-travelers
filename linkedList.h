#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "node.h"
#include "LLIter.h"
#include <iostream>
#include <string>

template <class t>
class LinkedList
{
private:
    void copyList(const LinkedList<t> &otherList);

protected:
    Node<t> *head;
    Node<t> *tail;
    int count;

public:
    LinkedList();
    LinkedList(const LinkedList<t> &otherList);
    const LinkedList<t> &operator=(const LinkedList<t> &listToCopy);
    ~LinkedList();
    bool isEmptyList() const;
    int length() const;
    void print(std::ostream &out = std::cout, std::string seperator = " -> ") const;
    
    // to create an iterator 
    LinkedListIterator<t> begin();
    LinkedListIterator<t> end();
    
    // to be implemented by child class
    virtual void deleteNodes();
    virtual void insert(const t &newData) = 0;
};

// default constructor
template <class t>
LinkedList<t>::LinkedList()
{
    this->head = nullptr;
    this->tail = nullptr;
    this->count = 0;
}

// copy constructor
template <class t>
LinkedList<t>::LinkedList(const LinkedList<t> &otherList)
{
    // resets this list and then copies otherList into it
    this->head = nullptr;
    this->tail = nullptr;
    this->count = 0;
    this->copyList(otherList);
}

// assignment override operator
template <class t>
const LinkedList<t> &LinkedList<t>::operator=(const LinkedList<t> &listToCopy)
{
    if (this != &listToCopy)
    {
        this->copyList(listToCopy);
    }
    return *this;
}

// destructor
template <class t>
LinkedList<t>::~LinkedList()
{
    this->deleteNodes();
}

// is list empty check
template <class t>
bool LinkedList<t>::isEmptyList() const
{
    return this->head == nullptr || count == 0;
}

// return length of list
template <class t>
int LinkedList<t>::length() const
{
    return this->count;
}

// print list node data
template <class t>
void LinkedList<t>::print(std::ostream &out, std::string separator) const
{
    if (!isEmptyList())
    {
        Node<t> *current;
        current = this->head;
        while (current != nullptr)
        {
            out << (current->data) << separator;
            current = current->forwLink;
        }
    }
}

// create an iterator at the beginning of list
template <class t>
LinkedListIterator<t> LinkedList<t>::begin()
{
    return LinkedListIterator<t>(head);
}

// create an iterator at the end of list with nullptr
template <class t>
LinkedListIterator<t> LinkedList<t>::end()
{
    return LinkedListIterator<t>();
}

// delete all nodes in list
template <class t>
void LinkedList<t>::deleteNodes()
{
    if (!(this->isEmptyList()))
    {
        Node<t> *temp;
        while (head != nullptr) 
        {
            temp = this->head;   // temp now points to same node head does
            this->head = this->head->forwLink;   // moves head pointer forward one
            delete temp;   // deletes node temp is pointing to
        }
        this->tail = nullptr;
        count = 0;
    }
}

// copies otherList to this list
template <class t>
void LinkedList<t>::copyList(const LinkedList<t> &otherList)
{
    Node<t> *newNode;
    Node<t> *current;

    this->deleteNodes();   // clear this list

    if (otherList.isEmptyList())
    {
        return;   // no need to copy if otherList is empty too
    }
    else 
    {
        current = otherList.head;   // place current at otherList.head
        this->count = otherList.count;   // copy original count

        this->head = new Node<t>(otherList.head->data, nullptr, nullptr);   // creates first node

        this->tail = this->head;

        current = current->forwLink;   // moves current to the next node
        while (current != nullptr)
        {
            newNode = new Node<t>(current->data, this->tail, nullptr);   // create another node
            this->tail->forwLink = newNode;   // connect last node link to newNode
            this->tail = newNode;   // moves tail to last node
            current = current->forwLink;   // moves current to the next node
        }
    }
}

#endif