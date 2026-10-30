#ifndef ENEMIES_H
#define ENEMIES_H

#include "enemy.h"

std::string attackDecision;

// common enemies

class Mimic : public Enemy 
{
public:
    // name = Mimic
    // health = 100
    // damage = 20
    // Levels 1-5
    Mimic() :
        Enemy("Mimic", 100, 20) {};

    void attack(Character &target) override
    {
        std::cout << "The " << getEnemyName() << " mirrors " << target.getCharacterName() << "'s attack." << std::endl;

        performDecidedAttack(target);
    }
};

class Wolf : public Enemy 
{
public:
    // name = Gravefang
    // health = 40
    // damage = 10
    // Levels 1-2
    Wolf() :
        Enemy("Gravefang", 40, 10) {};

    void attack(Character &target) override
    {
        attackDecision = decideAttack();

        if (attackDecision == "normal")
        {
            std::cout << "The " << getEnemyName() << " lunges forward at " << target.getCharacterName() << "." << std::endl;
        }
        else if (attackDecision == "strong")
        {
            std::cout << "The " << getEnemyName() << " tears into " << target.getCharacterName() << "'s arms." << std::endl;
        }
        else if (attackDecision == "weak")
        {
            std::cout << "The " << getEnemyName() << " slashes " << target.getCharacterName() << " with its claws." << std::endl;
        }
        else if (attackDecision == "desperate")
        {
            std::cout << "The " << getEnemyName() << " pounces onto " << target.getCharacterName() << "." << std::endl;
        }

        performDecidedAttack(target);
    }
};

class Skeleton : public Enemy 
{
public:
    // name = Skeleton Soldier
    // health = 70
    // damage = 15
    // Levels 1-5
    Skeleton() :
        Enemy("Skeleton Soldier", 70, 15) {};

    void attack(Character &target) override
    {
        attackDecision = decideAttack();

        if (attackDecision == "normal")
        {
            std::cout << "The " << getEnemyName() << " throws an axe at " << target.getCharacterName() << "." << std::endl;
        }
        else if (attackDecision == "strong")
        {
            std::cout << "The " << getEnemyName() << " slashes " << target.getCharacterName() << " with its sword." << std::endl;
        }
        else if (attackDecision == "weak")
        {
            std::cout << "The " << getEnemyName() << " shoots an arrow into " << target.getCharacterName() << "." << std::endl;
        }
        else if (attackDecision == "desperate")
        {
            std::cout << "The " << getEnemyName() << " smashes " << target.getCharacterName() << " with its shield." << std::endl;
        }

        performDecidedAttack(target);
    }
};

class Spider : public Enemy 
{
public:
    // name = Dungeon Spider
    // health = 55
    // damage = 12
    // Levels 1-3
    Spider() :
        Enemy("Dungeon Spider", 55, 12) {};

    void attack(Character &target) override
    {
        attackDecision = decideAttack();

        if (attackDecision == "normal")
        {
            std::cout << "The " << getEnemyName() << " scurries forward and bites " << target.getCharacterName() << "." << std::endl; 
        }
        else if (attackDecision == "strong")
        {
            std::cout << "The " << getEnemyName() << " drives its pincers into " << target.getCharacterName() << "." << std::endl;
        }
        else if (attackDecision == "weak")
        {
            std::cout << "The " << getEnemyName() << " stabs " << target.getCharacterName() << "." << std::endl;
        }
        else if (attackDecision == "desperate")
        {
            std::cout << "The " << getEnemyName() << " shoots poisonous venom at " << target.getCharacterName() << "." << std::endl;
        }

        performDecidedAttack(target);
    }
};

class Goblin : public Enemy 
{
public:
    // name = Goblin
    // health = 90
    // damage = 22
    // Levels 3-4
    Goblin() :
        Enemy("Goblin", 90, 22) {};

    void attack(Character &target) override
    {
        attackDecision = decideAttack();

        if (attackDecision == "normal")
        {
            std::cout << "The " << getEnemyName() << " slashes " << target.getCharacterName() << " with its claws." << std::endl;
        }
        else if (attackDecision == "strong")
        {
            std::cout << "The " << getEnemyName() << " plunges its dagger deep into " << target.getCharacterName() << "." << std::endl;
        }
        else if (attackDecision == "weak")
        {
            std::cout << "The " << getEnemyName() << " throws a knife at " << target.getCharacterName() << "." << std::endl;
        }
        else if (attackDecision == "desperate")
        {
            std::cout << "The " << getEnemyName() << " throws a barrage of sharpened bones at " << target.getCharacterName() << "." << std::endl;
        }

        performDecidedAttack(target);
    }
};

class Scion : public Enemy 
{
public:
    // name = Grafted Scion
    // health = 140
    // damage = 28
    // Levels 3-5
    Scion() :
        Enemy("Grafted Scion", 140, 28) {};

    void attack(Character &target) override
    {
        attackDecision = decideAttack();

        if (attackDecision == "normal")
        {
            std::cout << "The " << getEnemyName() << " drops a warhammer onto " << target.getCharacterName() << "'s head." << std::endl;
        }
        else if (attackDecision == "strong")
        {
            std::cout << "The " << getEnemyName() << " spins and slashes " << target.getCharacterName() << " with its double swords."  << std::endl;
        }
        else if (attackDecision == "weak")
        {
            std::cout << "The " << getEnemyName() << " throws a corpse at " << target.getCharacterName() << "." << std::endl;
        }
        else if (attackDecision == "desperate")
        {
            std::cout << "The " << getEnemyName() << " throws " << target.getCharacterName() << " against the wall." << std::endl;
        }

        performDecidedAttack(target);
    }
};

class Inferius : public Enemy 
{
public:
    // name = Inferius
    // health = 180
    // damage = 35
    // Levels 4-5
    Inferius() :
        Enemy("Inferius", 180, 35) {};

    void attack(Character &target) override
    {
        attackDecision = decideAttack();

        if (attackDecision == "normal")
        {
            std::cout << "The " << getEnemyName() << " throws a flaming rock at " << target.getCharacterName() << "." << std::endl;
        }
        else if (attackDecision == "strong")
        {
            std::cout << "The " << getEnemyName() << " lights the ground underneath " << target.getCharacterName() << " on fire." << std::endl;
        }
        else if (attackDecision == "weak")
        {
            std::cout << "The " << getEnemyName() << " explodes into a living ball of fire." << std::endl;
        }
        else if (attackDecision == "desperate")
        {
            std::cout << "The " << getEnemyName() << " grazes " << target.getCharacterName() << " and sets them ablaze."  << std::endl;
        }

        performDecidedAttack(target);
    }
};

// boss enemies

class Boss1 : public Enemy 
{
public:
    // name = Abyssal Knight
    // health = 150
    // damage = 20
    Boss1() :
        Enemy("Abyssal Knight", 150, 20) {};

    void attack(Character &target) override
    {
        attackDecision = decideAttack();

        if (attackDecision == "normal")
        {
            std::cout << "With an angry yell, the " << getEnemyName() << " plunges its sharpened greatsword into " << target.getCharacterName() << "." << std::endl;
        }
        else if (attackDecision == "strong")
        {
            std::cout << "With a heavy swing, the " << getEnemyName() << " brings his sharpened greatsword down upon " << target.getCharacterName() << "'s head."  << std::endl;
        }
        else if (attackDecision == "weak")
        {
            std::cout << "The " << getEnemyName() << " pierces a dagger into " << target.getCharacterName() << "." << std::endl;
        }
        else if (attackDecision == "desperate")
        {
            std::cout << "With its remaining strength, the " << getEnemyName() << " smashes " << target.getCharacterName() << " with its shield." << std::endl;
        }

        performDecidedAttack(target);
    }
};

class Boss2 : public Enemy 
{
public:
    // name = Dread Matron
    // health = 225
    // damage = 35
    Boss2() :
        Enemy("Dread Matron", 225, 35) {};

    void attack(Character &target) override
    {
        attackDecision = decideAttack();

        if (attackDecision == "normal")
        {
            std::cout << "The " << getEnemyName() << " pounces forward and stings " << target.getCharacterName() << "."  << std::endl;
        }
        else if (attackDecision == "strong")
        {
            std::cout << "The " << getEnemyName() << " drives its razor-sharp pincers into " << target.getCharacterName() << "." << std::endl;
        }
        else if (attackDecision == "weak")
        {
            std::cout << "With an angry cry, the " << getEnemyName() << " releases a swarm of spiders upon " << target.getCharacterName() << "." << std::endl;
        }
        else if (attackDecision == "desperate")
        {
            std::cout << "With its remaining strength, the " << getEnemyName() << " stabs into " << target.getCharacterName() << "." << std::endl;
        }

        performDecidedAttack(target);
    }
};

class Boss3 : public Enemy 
{
public:
    // name = Morgok, the Goblin King
    // health = 325
    // damage = 50
    Boss3() :
        Enemy("Goblin King, Morgok", 325, 50) {};

    void attack(Character &target) override
    {
        attackDecision = decideAttack();

        if (attackDecision == "normal")
        {
            std::cout << "With a blood curdling scream, the " << getEnemyName() << " throws " << target.getCharacterName() << " against the wall." << std::endl;
        }
        else if (attackDecision == "strong")
        {
            std::cout << "With an angry roar, the " << getEnemyName() << " pummels "  << target.getCharacterName() << " with its obsidian greataxe." << std::endl;
        }
        else if (attackDecision == "weak")
        {
            std::cout << "Weakened, the " << getEnemyName() << " throws a wave of broken bones at " << target.getCharacterName() << "." << std::endl;
        }
        else if (attackDecision == "desperate")
        {
            std::cout << "With its remaining strength, the" << getEnemyName() << " slashes " << target.getCharacterName() << " with its greataxe." << std::endl;
        }

        performDecidedAttack(target);
    }
};

class Boss4 : public Enemy 
{
public:
    // name = Grimgor, the Flesh Golem
    // health = 450
    // damage = 65
    Boss4() :
        Enemy("Flesh Golem, Grimgor", 450, 65) {};

    void attack(Character &target) override
    {
        attackDecision = decideAttack();

        if (attackDecision == "normal")
        {
            std::cout << "With a deep growl, the " << getEnemyName() << "slings a giant boulder at " << target.getCharacterName() << "."  << std::endl;
        }
        else if (attackDecision == "strong")
        {
            std::cout << "With a terrifying roar, the " << getEnemyName() << " pounds " << target.getCharacterName() << " into the ground." << std::endl;
        }
        else if (attackDecision == "weak")
        {
            std::cout << "Weakened, the " << getEnemyName() << " throws several rotting corpses at " << target.getCharacterName() << "." << std::endl;
        }
        else if (attackDecision == "desperate")
        {
            std::cout << "With its remaining strength, the " << getEnemyName() << " pummels " << target.getCharacterName() << " with its meaty fists." << std::endl;
        }

        performDecidedAttack(target);
    }
};

class Boss5 : public Enemy 
{
public:
    // name = Vorthrax, the Deep Wyrm
    // health = 600
    // damage = 90
    Boss5() :
        Enemy("Deep Wyrm, Vorthrax", 600, 90) {};

    void attack(Character &target) override
    {
        attackDecision = decideAttack();

        if (attackDecision == "normal")
        {
            std::cout << "The " << getEnemyName() << " slices its wing into " << target.getCharacterName() << "." << std::endl;
        }
        else if (attackDecision == "strong")
        {
            std::cout << "With a thunderous roar, the " << getEnemyName() << " unleashes a torrent of flames upon " << target.getCharacterName() << "." << std::endl;   // or Tail Sweep or Devour(final)
        }
        else if (attackDecision == "weak")
        {
            std::cout << "The " << getEnemyName() << " smashes its tail into " << target.getCharacterName() << "." << std::endl;
        }
        else if (attackDecision == "desperate")
        {
            std::cout << "With its remaining strength, the " << getEnemyName() << " tears through " << target.getCharacterName() << "'s flesh." << std::endl;
        }

        performDecidedAttack(target);
    }
};

class Merchant : public Enemy 
{
public:
    // name = Merchant
    // health = 1000
    // damage = 200
    Merchant() :
        Enemy("Merchant", 1000, 200) {};

    void attack(Character &target) override
    {
        attackDecision = decideAttack();

        if (attackDecision == "normal")
        {
            std::cout << "The " << getEnemyName() << " skewers " << target.getCharacterName() << " with both his swords." << std::endl;
        }
        else if (attackDecision == "strong")
        {
            std::cout << "The " << getEnemyName() << " cuts " << target.getCharacterName() << " to pieces." << std::endl;
        }
        else if (attackDecision == "weak")
        {
            std::cout << "The " << getEnemyName() << " slashes " << target.getCharacterName() << " across the face ." << std::endl;
        }
        else if (attackDecision == "desperate")
        {
            std::cout << "The " << getEnemyName() << " plunges a dagger deep into " << target.getCharacterName() << "." << std::endl;
        }

        performDecidedAttack(target);
    }
};

#endif