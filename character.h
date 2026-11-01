#ifndef CHARACTER_H
#define CHARACTER_H

#include "weapon.h"

class Enemy;

class Character 
{
private:
    std::string characterName;
    std::string profession;
    int level;
    int health;
    int healthCapacity;
    int damageReduction;
    
    Weapon weapon;

public:
    Character();
    Character(std::string name, std::string profession, int level, int healthCapacity, int damageReduction, Weapon weapon);
    Character(const Character &other);
    Character &operator=(const Character &other);

    std::string getCharacterName() const;
    std::string getProfession() const;
    int getLevel() const;
    int getHealth() const;
    int getHealthCapacity() const;
    int getDamageReduction() const;
    Weapon getWeapon() const;

    void setLevel(int level);
    void setHealth(int health);
    void setHealthCapacity(int healthCapacity);
    void setDamageReduction(int damageReduction);
    void setWeapon(int weaponDamage, int weaponHeal);

    virtual void attack(Enemy &target) {};
    virtual void selfHeal() {};
    virtual void healOthers(Character *characters[4]) {};

    void takeDamage(int damage);
    void heal(int heal);
    bool isDead() const;

    void levelUp();
    void resetHealth();
    
    friend std::ostream &operator<<(std::ostream &outputStream, const Character &characterToPrint);
};

// default constructor
Character::Character() 
{
    characterName = "";
    profession = "";
    level = 1;
    health = 1;
    healthCapacity = 1;
    damageReduction = 1;
    weapon = Weapon("Sword", 25, 0);
}

// constructor with values
Character::Character(std::string name, std::string profession, int level, int healthCapacity, int damageReduction, Weapon weapon) 
{
    characterName = name;
    this->profession = profession;
    this->level = level;
    health = healthCapacity;
    this->healthCapacity = healthCapacity;
    this->damageReduction = damageReduction;
    this->weapon = weapon;
}

// copy constructor
Character::Character(const Character &other)
{
    characterName = other.characterName;
    profession = other.profession;
    level = other.level;
    health = other.health;
    healthCapacity = other.healthCapacity;
    damageReduction = other.damageReduction;
    weapon = other.weapon;
}

// copy assignment operater
Character &Character::operator=(const Character &other) 
{
    if (this != &other) {
        characterName = other.characterName;
        profession = other.profession;
        level = other.level;
        health = other.health;
        healthCapacity = other.healthCapacity;
        damageReduction = other.damageReduction;
        weapon = other.weapon;
    }
    return *this;
}

// getters

std::string Character::getCharacterName() const 
{
    return characterName;
}

std::string Character::getProfession() const
{
    return profession;
}

int Character::getLevel() const 
{
    return level;
}

int Character::getHealth() const
{
    return health;
}

int Character::getHealthCapacity() const 
{
    return healthCapacity;
}

int Character::getDamageReduction() const 
{
    return damageReduction;
}
     
Weapon Character::getWeapon() const 
{
    return weapon;
}

// setter

void Character::setLevel(int level)
{
    this->level = level;
}

void Character::setHealth(int health)
{
    this->health = health;
}

void Character::setHealthCapacity(int healthCapacity)
{
    this->healthCapacity = healthCapacity;
}

void Character::setDamageReduction(int damageReduction)
{
    this->damageReduction = damageReduction;
}

void Character::setWeapon(int weaponDamage, int weaponHeal)
{
    this->weapon.setWeaponDamage(weaponDamage);
    this->weapon.setWeaponHeal(weaponHeal);
}

// combat functions

void Character::takeDamage(int damage)
{
    int factoredDamage = damage - (damage * damageReduction / 100);
    health -= factoredDamage;

    if (health <= 0) 
    {
        health = 0;
        std::cout << "Welp, " << characterName << " has died" << std::endl << std::endl;
    } 
    else 
    {
        std::cout << characterName << "'s health is now " << health << " / " << healthCapacity << std::endl << std::endl;
    }
}

void Character::heal(int heal) 
{
    health += heal;

    if (health > healthCapacity)
    {
        resetHealth();
    }
}

bool Character::isDead() const
{
    return health == 0;
}

// character upgrades
void Character::levelUp() 
{
    int input;  
    std::cout << "Choose an attribute to increase: " << std::endl;
    
    if (damageReduction == 50) 
    {
        std::cout << "1 for Health, Damage-Reduction-Maxed-Out, 3 for Weapon" << std::endl;
        std::cin >> input;
        while (input != 1 && input != 3) 
        {
            std::cin.clear();   std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Please enter 1 or 3" << std::endl;
            std::cin >> input;
        }
    } 
    else 
    {
        std::cout << "1 for Health, 2 for Damage Reduction, 3 for Weapon" << std::endl;
        std::cin >> input;
        while (input < 1 || input > 3) 
        {
            std::cin.clear();   std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Please enter 1, 2, or 3" << std::endl;
            std::cin >> input;
        }
    }

    switch (input) {
        case 1:
            healthCapacity += 10;
            health += 10;
            std::cout << characterName << "'s health is now " << health << " / " << healthCapacity << "."<< std::endl;
            level++;
            break;
        case 2:
            damageReduction += 5;
            std::cout << characterName << "'s damage reduction is now " << damageReduction << "%." << std::endl;
            level++;
            break;
        case 3:
            weapon.weaponLevelUp();
            level++;
            break;
    }
}

// reset health
void Character::resetHealth()
{
    health = healthCapacity;
}

// friendly output function
std::ostream &operator<<(std::ostream &outputStream, const Character &characterToPrint) 
{
    outputStream << characterToPrint.characterName << ", the " << characterToPrint.profession << std::endl;
    outputStream << "Level: " << characterToPrint.level << std::endl;
    outputStream << "Health: " << characterToPrint.health << " / " << characterToPrint.healthCapacity << std::endl;
    outputStream << "Damage Reduction: " << characterToPrint.damageReduction << "%" << std::endl;
    outputStream << "Weapon: " << characterToPrint.getWeapon();

    return outputStream;
}

#endif