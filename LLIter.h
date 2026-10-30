#ifndef LINKEDLISTITERATOR_H
#define LINKEDLISTITERATOR_H

#include "node.h"
#include <stdexcept>

template <class t>
class LinkedListIterator
{
private:
    Node<t> *current;

public:
    LinkedListIterator();
    LinkedListIterator(Node<t> *n);
    t operator*();
    LinkedListIterator<t> operator++();
    LinkedListIterator<t> operator--();
    bool operator==(const LinkedListIterator<t> &otherIter) const;
    bool operator!=(const LinkedListIterator<t> &otherIter) const;
};

// default constructor
template <class t>
LinkedListIterator<t>::LinkedListIterator()
{
    current = nullptr;
}

// constructor with value
template <class t>
LinkedListIterator<t>::LinkedListIterator(Node<t> *n)
{
    current = n;
}

// dereference override operator
template <class t>
t LinkedListIterator<t>::operator*()
{
    if (current != nullptr) 
    {
        return current->data;
    }
    else 
    {
        throw std::out_of_range("No data to return");
    }
}

// increment override operator
template <class t>
LinkedListIterator<t> LinkedListIterator<t>::operator++()
{
    if (current != nullptr)
    {
        current = current->forwLink;
    }
    else
    {
        throw std::out_of_range("Already at the end");
    }
    return *this;
}

// decrement override operator
template <class t>
LinkedListIterator<t> LinkedListIterator<t>::operator--()
{
    if (current != nullptr)
    {
        current = current->prevLink;
    }
    else
    {
        throw std::out_of_range("Already at the beginning");
    }
    return *this;
}

// equal override operator
template <class t>
bool LinkedListIterator<t>::operator==(const LinkedListIterator<t> &otherIter) const
{
    return this->current == otherIter.current;
}

// not equal override operator
template <class t>
bool LinkedListIterator<t>::operator!=(const LinkedListIterator<t> &otherIter) const
{
    return !(this->current == otherIter.current);
}

#endif