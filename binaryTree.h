#ifndef BINARYTREE_H
#define BINARYTREE_H

#include "node.h"

template <class t>
class BinaryTree 
{
public:
    BinaryTree();
    BinaryTree(const BinaryTree<t> &treeToCopy);
    const BinaryTree<t> &operator=(const BinaryTree<t> &treeToCopy);
    ~BinaryTree();
    bool isEmpty() const;

    int treeHeight() const;
    int treeNodeCount() const;
    int treeLeavesCount() const;

protected:
    BinaryNode<t> *root;

private: 
    void copyTree(BinaryNode<t> *&myTreeNode, BinaryNode<t> *treeToCopyNode);
    void destroy(BinaryNode<t> *&currentNode);
        
    int nodeCount(BinaryNode<t> *currentNode) const;
    int height(BinaryNode<t> *currentNode) const;
    int leavesCount(BinaryNode<t> *currentNode) const;
};

// default constructor
template <class t>
BinaryTree<t>::BinaryTree()
{
    root = nullptr;
}

// copy constructor
template <class t>
BinaryTree<t>::BinaryTree(const BinaryTree<t> &treeToCopy)
{
    root = nullptr;
    copyTree(this->root, treeToCopy.root);
}

// assignment operator override
template <class t>
const BinaryTree<t> &BinaryTree<t>::operator=(const BinaryTree<t> &treeToCopy)
{
    if (this != &treeToCopy)
    {
        if (!this->isEmpty())
        {
            destroy(this->root);
        }
        copyTree(this->root, treeToCopy.root);
    }
}

// destructor
template <class t>
BinaryTree<t>::~BinaryTree()
{
    destroy(this->root);
}

// check if tree is empty
template <class t>
bool BinaryTree<t>::isEmpty() const
{
    return root == nullptr;
}

// access to treeHeight getter
template <class t>
int BinaryTree<t>::treeHeight() const
{
    return height(this->root);
}

// access to treeNodeCount getter
template <class t>
int BinaryTree<t>::treeNodeCount() const
{
    return nodeCount(this->root);
}

// access to treeLeavesCount getter
template <class t>
int BinaryTree<t>::treeLeavesCount() const
{
    return leavesCount(this->root);
}

// copy function
template <class t>
void BinaryTree<t>::copyTree(BinaryNode<t> *&myTreeNode, BinaryNode<t> *treeToCopyNode)
{
    if (treeToCopyNode == nullptr)
    {
        myTreeNode = nullptr;
    }
    else
    {
        myTreeNode = new BinaryNode<t>(treeToCopyNode->data);
        copyTree(myTreeNode->lLink, treeToCopyNode->lLink);
        copyTree(myTreeNode->rLink, treeToCopyNode->rLink);
    }
}

// delete function
template <class t>
void BinaryTree<t>::destroy(BinaryNode<t> *&currentNode)
{
    if (currentNode != nullptr)
    {
        destroy(currentNode->lLink);
        destroy(currentNode->rLink);
        delete currentNode;
        currentNode = nullptr;
    }
}

// tree node count getter
template <class t>
int BinaryTree<t>::nodeCount(BinaryNode<t> *currentNode) const
{
    if (currentNode == nullptr)
    {
        return 0;
    }
    return nodeCount(currentNode->lLink) + nodeCount(currentNode->rLink) + 1;
}

// tree height getter
template <class t>
int BinaryTree<t>::height(BinaryNode<t> *currentNode) const
{
    if (currentNode == nullptr)
    {
        return 0;
    }
    return max(height(currentNode->lLink), height(currentNode->rLink)) + 1;
}

// tree leaves count getter
template <class t>
int BinaryTree<t>::leavesCount(BinaryNode<t> *currentNode) const
{
    if (currentNode == nullptr)
    {
        return 0;
    }
    if (currentNode->lLink == nullptr && currentNode->rLink == nullptr)
    {
        return 1;
    }
    return leavesCount(currentNode->lLink) + leavesCount(currentNode->rLink);
}

#endif