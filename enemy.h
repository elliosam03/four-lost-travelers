#ifndef ENEMY_H
#define ENEMY_H

#include "attackDT.h"
#include <iostream>
#include <string>

class Character;

class Enemy 
{
private: 
    std::string enemyName;
    int health;
    int healthCapacity;
    int damage;
    
    AttackDecisionTree decisionTree;

public:
    Enemy();
    Enemy(std::string name, int healthCapacity, int damage);
    Enemy(const Enemy &other);
    Enemy &operator=(const Enemy &other);
    virtual ~Enemy() {};

    std::string getEnemyName() const;
    int getHealth() const;
    int getHealthCapacity() const;
    int getDamage() const;

    virtual void attack(Character &target) = 0;
    std::string decideAttack();
    void performDecidedAttack(Character &target);

    void takeDamage(int damage);
    bool isDead() const;

    friend std::ostream &operator<<(std::ostream &outputStream, const Enemy &enemyToPrint);
};

// default constructor
Enemy::Enemy()
{
    enemyName = " ";
    health = 1;
    healthCapacity = 1;
    damage = 1;
}

// constructor with values
Enemy::Enemy(std::string name, int healthCapacity, int damage)
{
    enemyName = name;
    health = healthCapacity;
    this->healthCapacity = healthCapacity;
    this->damage = damage;
}

// copy constructor
Enemy::Enemy(const Enemy &other)
{
    enemyName = other.enemyName;
    health = other.health;
    healthCapacity = other.healthCapacity;
    damage = other.damage;
}

// assignment override operator
Enemy &Enemy::operator=(const Enemy &other)
{
    if (this != &other)
    {
        enemyName = other.enemyName;
        health = other.health;
        healthCapacity = other.healthCapacity;
        damage = other.damage;
    }
    return *this;
}

// getters

std::string Enemy::getEnemyName() const
{
    return enemyName;
}

int Enemy::getHealth() const
{
    return health;
}

int Enemy::getHealthCapacity() const
{
    return healthCapacity;
}

int Enemy::getDamage() const
{
    return damage;
}

// combat functions

std::string Enemy::decideAttack()
{
    AttackDecision decision = decisionTree.getAttack(health, healthCapacity);

    if (decision.attack == NORMAL_ATTACK)
    {
        return "normal";
    }
    else if (decision.attack == STRONG_ATTACK)
    {
        return "strong";
    }
    else if (decision.attack == WEAK_ATTACK)
    {
        return "weak";
    }
    else
    {
        return "desperate";
    }
}

void Enemy::performDecidedAttack(Character &target)
{
    AttackDecision decision = decisionTree.getAttack(health, healthCapacity);

    if (decision.attack == NORMAL_ATTACK)
    {
        target.takeDamage(damage);
    }
    else if (decision.attack == STRONG_ATTACK)
    {
        target.takeDamage(damage * 2);
    }
    else if (decision.attack == WEAK_ATTACK)
    {
        target.takeDamage(damage * 0.5);
    }
    else
    {
        target.takeDamage(damage * 1.5);
    }
}

void Enemy::takeDamage(int damage)
{
    health -= damage;

    if (health <= 0) {
        health = 0;
        std::cout << "Hourah, the " << enemyName << " has fallen!" << std::endl << std::endl;
    } else {
        std::cout << enemyName << "'s health is now " << health << " / " << healthCapacity << std::endl << std::endl;
    }
}

bool Enemy::isDead() const
{
    return health == 0;
}

// friendly output override operator
std::ostream &operator<<(std::ostream &outputStream, const Enemy &enemyToPrint)
{
    outputStream << enemyToPrint.getEnemyName() << std::endl;
    outputStream << "Health: " << enemyToPrint.getHealth() << " / " << enemyToPrint.getHealthCapacity() << std::endl;
    outputStream << "Damage: " << enemyToPrint.getDamage() << std::endl;

    return outputStream;
}

#endif