#ifndef QUEUE_H
#define QUEUE_H

#include "node.h"
#include <stdexcept>

template <class t>
class Queue 
{
private:
    void copyQueue(const Queue<t> &otherQueue);

protected:
    Node<t> *head;
    Node<t> *tail;
    int count;

public:
    Queue();
    Queue(const Queue<t> &otherQueue);
    const Queue<t> &operator=(const Queue<t> &queueToCopy);

    ~Queue();
    virtual void deleteNodes();
    bool isEmptyQueue() const;

    void enqueue(const t &newData);
    virtual void dequeue();
    t front() const;
};

// default contructor
template <class t>
Queue<t>::Queue()
{
    this->head = nullptr;
    this->tail = nullptr;
    this->count = 0;
}

// copy constructor
template <class t>
Queue<t>::Queue(const Queue<t> &otherQueue)
{
    this->head = nullptr;
    this->tail = nullptr;
    this->count = 0;
    this->copyQueue(otherQueue);
}

// assignment operator override
template <class t>
const Queue<t> &Queue<t>::operator=(const Queue<t> &queueToCopy)
{
    if (this != &queueToCopy)
    {
        this->deleteNodes();
        this->copyQueue(queueToCopy);
    }
    return *this;
}

// destructor
template <class t>
Queue<t>::~Queue()
{
    this->deleteNodes();
}

// delete all nodes
template <class t>
void Queue<t>::deleteNodes()
{
    if (!(this->isEmptyQueue()))
    {      
        Node<t> *temp;

        while (this->head != nullptr)
        {
            temp = this->head;   // match temp to head
            this->head = this->head->forwLink;   // move head forward
            delete temp;   // delete node
        }
        this->tail = nullptr;
        this->count = 0;
    }
}

// check if queue is empty
template <class t>
bool Queue<t>::isEmptyQueue() const
{
    return this->head == nullptr || this->count == 0;
}

// add to queue
template <class t>
void Queue<t>::enqueue(const t &newData)
{
    Node<t> *newNode = new Node<t>(newData, nullptr, nullptr);

    if (this->isEmptyQueue())   // add node to front if empty
    {
        this->head = newNode;
        this->tail = newNode;
    }
    else   // add node in back
    {
        this->tail->forwLink = newNode;   // connect tail to newNode
        this->tail = newNode;   // move tail to end
    }

    this->count++;
}

// remove from queue
template <class t>
void Queue<t>::dequeue()
{
    if (!(this->isEmptyQueue()))
    {
        Node<t> *temp = this->head;   // match temp to head
        this->head = this->head->forwLink;   // move head forward
        delete temp;   // delete temp node
        this->count--;
    }
    else
    {
        throw std::out_of_range("Queue is empty.");
    }

    if (this->isEmptyQueue())
    {
        this->tail = nullptr;
    }
}

// return front of queue
template <class t>
t Queue<t>::front() const
{
    if (this->isEmptyQueue())
    {
        throw std::out_of_range("Queue is empty.");
    }

    return this->head->data;
}

// copies otherQueue to this queue
template <class t>
void Queue<t>::copyQueue(const Queue<t> &otherQueue)
{
    Node<t> *newNode;
    Node<t> *current;

    this->deleteNodes();   // clears this queue

    if (otherQueue.isEmptyQueue())
    {
        return;   // no need to copy empty queue
    }
    else
    {
        current = otherQueue.head;   // match current to otherQueue's head
        this->count = otherQueue.count;   // copy count

        this->head = new Node<t>(otherQueue.head->data, nullptr, nullptr);   // copy first node
    
        this->tail = this->head;

        current = current->forwLink;   // move current forward
        while (current != nullptr)
        {
            newNode = new Node<t>(current->data, nullptr, nullptr);
            this->tail->forwLink = newNode;   // connect tail node to newNode
            this->tail = newNode;   // move tail to end
            current = current->forwLink;   // move current forward
        }
    }
}

#endif