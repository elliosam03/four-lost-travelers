#ifndef NODE_H
#define NODE_H

// doubly linked node
template <class t>
struct Node
{
    t data;
    Node<t> *prevLink;    
    Node<t> *forwLink;
    Node(const t &data, Node<t> *prevLink = nullptr, Node<t> *forwLink = nullptr);
};

// constructor with values
template <class t>
Node<t>::Node(const t &data, Node<t> *prevLink, Node<t> *forwLink) : data(data)
{
    this->prevLink = prevLink;
    this->forwLink = forwLink;
}


// binary node
template <class t>
struct BinaryNode
{
    t data;
    BinaryNode<t> *lLink;
    BinaryNode<t> *rLink;
    BinaryNode(t data);
};

// default constructor with data
template <class t>
BinaryNode<t>::BinaryNode(t data) : data(data)
{
    lLink = nullptr;
    rLink = nullptr;
}

#endif