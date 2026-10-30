#ifndef CHARACTERS_H
#define CHARACTERS_H

#include "character.h"
#include "enemy.h"

class Warrior : public Character 
{
public:
    // name = magnus
    // profession = warrior
    // level = 1
    // health = 70
    // damageReduction = 10 %
    // weapon = sword     // damage = 15, heal = 0
    // inventoryCapacity = 2     // potential items = shield
    Warrior() :
        Character("Magnus", "Warrior", 1, 70, 10, Weapon("Sword", 15, 0)) {};

    void attack(Enemy &target) override
    {
        std::cout << std::endl << getCharacterName() << " slashes the " << target.getEnemyName() << " with his mighty sword." << std::endl;

        target.takeDamage(getWeapon().getWeaponDamage());
    }
};

class Mage : public Character 
{
public:
    // name = archibald
    // profession = mage
    // level = 1
    // health = 50
    // damageReduction = 20 %
    // weapon = staff     // damage = 10, heal = 0
    // inventoryCapacity = 6     // potential items = fireSpell, iceSpell, protectSpell
    Mage() : 
        Character("Vera", "Mage", 1, 50, 20, Weapon("Staff", 10, 0)) {};

    void attack(Enemy &target) override
    {
        std::cout << std::endl << getCharacterName() << " casts a spell at the " << target.getEnemyName() << "." << std::endl;

        target.takeDamage(getWeapon().getWeaponDamage());
    }
};

class Archer : public Character 
{
public:
    // name = flint
    // profession = archer
    // level = 1
    // health = 40
    // damageReduction = 5 %
    // weapon = bow     // damage = 10, heal = 0
    // inventoryCapacity = 4     // potential items = fireArrows, iceArrows
    Archer() : 
        Character("Flint", "Archer", 1, 40, 5, Weapon("Bow", 10, 0)) {};

    void attack(Enemy &target) override
    {
        std::cout << std::endl << getCharacterName() << " shoots an arrow through the " << target.getEnemyName() << "." << std::endl;

        target.takeDamage(getWeapon().getWeaponDamage());
    }
};

class Healer : public Character 
{
public:
    // name = quassi
    // profession = healer
    // level = 1
    // health = 10
    // damageReduction = 0 %
    // weapon = wand     // damage = 0, heal = 5
    // inventoryCapacity = 4     // potential items = healthSteal
    Healer() : 
        Character("Quassi", "Healer", 1, 10, 0, Weapon("Wand", 0, 5)) {};

    void selfHeal() override
    {
        heal(getWeapon().getWeaponHeal() * 2);   // double power for selfHeal()

        std::cout << getCharacterName() << " heals himself\n\n";

    }

    void healOthers(Character *characters[4]) override
    {
        for (int i = 0; i < 3; ++i)
        {
            if (!characters[i]->isDead())
            {
                if (characters[i]->getHealth() != characters[i]->getHealthCapacity())   // check if health is already full
                {
                    characters[i]->heal(getWeapon().getWeaponHeal());

                    std::cout << std::endl << getCharacterName() << " heals " << characters[i]->getCharacterName() << ".";
                }
            }
        }
        
        std::cout << std::endl << std::endl;
    }
};

#endif