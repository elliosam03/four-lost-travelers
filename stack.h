#ifndef STACK_H
#define STACK_H

#include "node.h"
#include <stdexcept>

template <class t>
class Stack
{
private:
    void copyStack(const Stack<t> &otherStack);

protected:
    Node<t> *head;
    Node<t> *tail;
    int count;

public:
    Stack();
    Stack(const Stack<t> &otherStack);
    const Stack<t> &operator=(const Stack<t> &stackToCopy);

    virtual ~Stack();
    virtual void deleteNodes();
    bool isEmptyStack() const;

    void push(const t &newData);
    virtual void pop();
    t &top() const;
};

// default constructor
template <class t>
Stack<t>::Stack()
{
    this->head = nullptr;
    this->tail = nullptr;
    this->count = 0;
}

// copy constructor
template <class t>
Stack<t>::Stack(const Stack<t> &otherStack)
{
    this->head = nullptr;
    this->tail = nullptr;
    this->count = 0;
    this->copyStack(otherStack);
}

// assignment override operator
template <class t>
const Stack<t> &Stack<t>::operator=(const Stack<t> &stackToCopy)
{
    if (this != &stackToCopy)
    {
        this->deleteNodes();
        this->copyStack(stackToCopy);
    }
    return *this;
}

// destructor
template <class t>
Stack<t>::~Stack()
{
    this->deleteNodes();
}

// deletes all nodes in stack
template <class t>
void Stack<t>::deleteNodes()
{
    if (!(this->isEmptyStack()))
    {
        Node<t> *temp;

        while (this->head != nullptr)
        {
            temp = this->head;   // matches temp to head
            this->head = this->head->forwLink;   // moves head forward
            delete temp;   // deletes node temp is pointing at
        }
        this->tail = nullptr;
        this->count = 0;
    }
}

// is stack empty check
template <class t>
bool Stack<t>::isEmptyStack() const
{
    return this->head == nullptr || this->count == 0;
}

// return top node data
template <class t>
t &Stack<t>::top() const
{
    if (this->isEmptyStack())
    {
        throw std::out_of_range("Stack is empty.");
    }
    return this->head->data;
}

// add new node to stack
template <class t>
void Stack<t>::push(const t &newData)
{
    // create a new node
    Node<t> *newNode = new Node<t>(newData, nullptr, nullptr);
    
    if (this->isEmptyStack())   // add node if stack is empty
    {
        this->head = newNode;
        this->tail = newNode;
    }
    else   // add newNode on top
    {
        newNode->forwLink = this->head;
        this->head = newNode;
    }

    this->count++;
}

// delete node from stack
template <class t>
void Stack<t>::pop()
{
    Node<t> *current;
    current = this->head;

    if (!(this->isEmptyStack()))   // check if stack has contents
    {
        this->head = this->head->forwLink;   // moves head forward
        delete current;   // deletes node
        this->count--;
    }
    else
    {
        throw std::out_of_range("Stack is empty.");
    }

    if (this->isEmptyStack())
    {
        this->tail = nullptr;
    }
}

// copies otherStack to this stack
template <class t>
void Stack<t>::copyStack(const Stack<t> &otherStack)
{
    Node<t> *newNode;
    Node<t> *current;

    this->deleteNodes();   // clears this stack

    if (otherStack.isEmptyStack())
    {
        return;   // no need to copy empty stack to empty stack
    }
    else
    {
        current = otherStack.head;   // move current to otherStack.head
        this->count = otherStack.count;   // copy count

        this->head = new Node<t>(otherStack.head->data, nullptr, nullptr);   // create first node

        this->tail = this->head;

        current = current->forwLink;
        while (current != nullptr)
        {
            newNode = new Node<t>(current->data, nullptr, nullptr);   // creates another node
            this->tail->forwLink = newNode;   // connect last node to newNode
            this->tail = newNode;
            current = current->forwLink;
        }
    }
}

#endif