
#ifndef ITEMS_H
#define ITEMS_H

#include "item.h"
#include <vector>

class SmallHealthPotion : public Item
{
public:
    // name = small health potion
    // ability = heals all living players
    // id = 001
    // cost = 15
    SmallHealthPotion() :
        Item("Small Health Potion", "Heals all living players", 001, 15) {};

    bool use(Character *characters[4]) override
    {
        for (int i = 0; i < 4; ++i)
        {
            if (!characters[i]->isDead() && characters[i]->getHealth() < characters[i]->getHealthCapacity())
            {
                characters[i]->heal(30);

                std::cout << characters[i]->getCharacterName() << " was healed." << std::endl;
            }
        }

        std::cout << std::endl;

        return true;
    }
};

class LargeHealthPotion : public Item
{
public:
    // name = large health potion
    // ability = heals all living players
    // id = 002
    // cost = 50
    LargeHealthPotion() :
        Item("Large Health Potion", "Greatly heals all living players", 002, 50) {};

    bool use(Character *characters[4]) override
    {
        for (int i = 0; i < 4; ++i)
        {
            if (!characters[i]->isDead() && characters[i]->getHealth() < characters[i]->getHealthCapacity())
            {
                characters[i]->heal(60);

                std::cout << characters[i]->getCharacterName() << " was healed." << std::endl;
            }
        }

        std::cout << std::endl;

        return true;
    }
};

class RevivePotion : public Item
{
public:
    // name = revive potion
    // ability = revives a dead player
    // id = 003
    // cost = 100
    RevivePotion() :
        Item("Revive Potion", "Revives a dead player", 003, 100) {};

    bool use(Character *characters[4]) override
    {
        std::vector<int> deadPlayers;

        for (int i = 0; i < 4; ++i)
        {
            if (characters[i]->isDead())   // add dead players to vector
            {
                deadPlayers.push_back(i);
            }
        }

        if (deadPlayers.empty()) 
        {
            std::cout << "No-one has died yet.\n\n";
            return false;
        }

        std::cout << "Choose a player to revive:" << std::endl;

        for (int i = 0; i < deadPlayers.size(); ++i)
        {
            std::cout << deadPlayers[i] + 1 << ". " << characters[deadPlayers[i]]->getCharacterName() << std::endl;
        }

        int choice;
        bool validChoice = false;

        std::cin >> choice;
        while (!validChoice) 
        {
            while (choice < 1 || choice > 4)
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                std::cout << "Choose a player to revive:" << std::endl;
                std::cin >> choice;
            }

            if (characters[choice-1]->isDead()) 
            {
                validChoice = true;
            }
            else
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                std::cout << "Choose a dead player" << std::endl;
                std::cin >> choice;
            }
        }

        int reviveHealth = characters[choice-1]->getHealthCapacity() * 3 / 4;

        characters[choice-1]->setHealth(reviveHealth);
        
        std::cout << characters[choice-1]->getCharacterName() << " has been revived to " << reviveHealth << " health.\n\n";

        return true;
    }
};

class StrengthPotion : public Item
{
public:
    // name = strength potion
    // ability = temporarily increases weapon damge
    // id = 004
    // cost = 40
    StrengthPotion() :
        Item("Strength Potion", "Temporarily increases weapon damge", 004, 40) {};

    bool use(Character *characters[4]) override
    {
        // finish later

        return true;
    }
};

#endif