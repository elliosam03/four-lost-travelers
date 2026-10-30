#ifndef ATTACKDECISIONTREE_H
#define ATTACKDECISIONTREE_H

#include "binaryTree.h"
#include <stdexcept>

enum AttackType
{
    SPACER,
    NORMAL_ATTACK,
    STRONG_ATTACK,
    WEAK_ATTACK,
    DESPERATE_ATTACK
    // KILL_SHOT_ATTACK
};

struct AttackDecision
{
    int healthThreshold;
    AttackType attack;

    AttackDecision()   // default constructor
    {
        healthThreshold = 0;
        attack = NORMAL_ATTACK;
    }

    AttackDecision(int threshold, AttackType type)
    {
        healthThreshold = threshold;
        attack = type;
    }
};

class AttackDecisionTree : public BinaryTree<AttackDecision>
{
public:
    AttackDecisionTree();
    AttackDecision getAttack(double health, double healthCapacity);

private:
    AttackDecision traverse(BinaryNode<AttackDecision> *node, double healthPercent);
};

// hardcoded decision tree
AttackDecisionTree::AttackDecisionTree()
{
    root = new BinaryNode<AttackDecision>(AttackDecision(50, SPACER));

    root->lLink = new BinaryNode<AttackDecision>(AttackDecision(75, SPACER));
    
    root->lLink->lLink = new BinaryNode<AttackDecision>(AttackDecision(75, NORMAL_ATTACK));   // Normal attack node

    root->lLink->rLink = new BinaryNode<AttackDecision>(AttackDecision(50, STRONG_ATTACK));   // Strong attack node

    root->rLink = new BinaryNode<AttackDecision>(AttackDecision(25, SPACER));

    root->rLink->lLink = new BinaryNode<AttackDecision>(AttackDecision(25, WEAK_ATTACK));   // Weak attack node

    root->rLink->rLink = new BinaryNode<AttackDecision>(AttackDecision(0, DESPERATE_ATTACK));   // Desperate attack node
}

AttackDecision AttackDecisionTree::getAttack(double health, double healthCapacity)
{
    double healthPercent = (health / healthCapacity) * 100;

    return traverse(root, healthPercent);
}

// traverse through tree to find match for enemy's health
AttackDecision AttackDecisionTree::traverse(BinaryNode<AttackDecision> *node, double healthPercent)
{
    if (node->lLink == nullptr && node->rLink == nullptr)
    {
        return node->data;
    }

    if (healthPercent >= node->data.healthThreshold)
    {
        return traverse(node->lLink, healthPercent);
    }
    else
    {
        return traverse(node->rLink, healthPercent);
    }
}

#endif