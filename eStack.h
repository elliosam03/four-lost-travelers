#ifndef ENEMIESSTACK_H
#define ENEMIESSTACK_H

#include "stack.h"

template <class t>
class EStack : public Stack<t>
{
public:
    ~EStack();
    void deleteNodes() override;
    void pop() override;
};

template <class t>
EStack<t>::~EStack()
{
    this->deleteNodes();
}

// deletes all nodes in stack and objects within
template <class t>
void EStack<t>::deleteNodes()
{
    if (!(this->isEmptyStack()))
    {
        Node<t> *temp;

        while (this->head != nullptr)
        {
            temp = this->head;   // matches temp to head
            this->head = this->head->forwLink;   // moves head forward
            delete temp->data;   // deletes object in node from everywhere
            delete temp;   // deletes node temp is pointing at
        }
        this->tail = nullptr;
        this->count = 0;
    }
}

// delete object from node and delete node from stack
template <class t>
void EStack<t>::pop()
{
    Node<t> *current;
    current = this->head;

    if (!(this->isEmptyStack()))   // check if stack has contents
    {
        this->head = this->head->forwLink;   // moves head forward
        delete current->data;   // deletes object in node from everywhere
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


#endif