#ifndef MAINEXTENSION_H
#define MAINEXTENSION_H

#include "characters.h"
#include "eStack.h"
#include "enemies.h"
#include "levelsLL.h"
#include "level.h"
#include "graph.h"
#include "queue.h"
#include "inventory.h"
#include <cstdlib>
#include <ctime>
// #include <crtdbg.h>   // for memory leaks

void resetStream() 
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void enter()
{    
    std::cout << "     \"enter\"\n";

    std::string input;
    
    std::getline(std::cin, input);

    input.clear();
}

void introText()
{
    std::cout << 
    "Four weary travelers have spent the entire day crossing a remote and unforgiving wilderness. As evening approaches, a violent storm rolls across the mountains, bringing freezing rain, howling winds, and frequent lighting strikes. With night falling fast, they realize they have no chance of reaching the nearest settlement before the storm becomes too dangerous.\n\n";

    enter();

    std::cout << 
    "Desperate for shelter, they discover the dark entrance of a large cave hidden beneath a rocky cliff. With nowhere else to go and the storm closing in behind them, they decide the cave is their safest option. They light their torches and cautiously make their way inside, relieved to finally be out of the cold.\n\n";

    enter();

    std::cout << 
    "But the deeper they travel, the stranger the cave becomes. They find signs that something has been living there: broken bones, enormous tracks, abandoned weapons, and scraps of old clothing scattered across the floor.\n\n";

    enter();

    std::cout << 
    "Before they can turn back, the cave entrance suddenly collapses, as if sensing their presence and sealing them inside.\n\n";

    enter();

    std::cout << 
    "As the walls behind them continue to crumble, they have no choice but to go deeper.\n\n" 

    "They haven't found shelter.   And this cave is not empty.\n\n";

    enter();

    std::cout << 
    "As they venture into the cavern they stumble upon a large open room and decide to enter.\n\n";

    enter();
}

void createEnemies(EStack<Enemy*> &enemies)
{
    enum EnemyType {
        mimic, wolf, skeleton, spider, goblin, scion, inferius, boss1, boss2, boss3, boss4, boss5
    };//  0      1      2        3       4       5       6        7      8      9      10     11
    
    // order of enemies    backwards
    EnemyType arr[] = { 
        boss5, inferius, scion, inferius, mimic, inferius, scion, skeleton, 
        boss4, scion, inferius, scion, skeleton, goblin, mimic, 
        boss3, goblin, scion, mimic, skeleton, goblin, spider, 
        boss2, spider, mimic, skeleton, spider, wolf, 
        boss1, mimic, wolf, spider, skeleton, wolf
    };

    // create enemies
    for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i)
    {
        switch (arr[i]) 
        {
            case 0:
                enemies.push(new Mimic());
                break;
            case 1:
                enemies.push(new Wolf());
                break;
            case 2:
                enemies.push(new Skeleton());
                break;
            case 3:
                enemies.push(new Spider());
                break;
            case 4:
                enemies.push(new Goblin());
                break;
            case 5:
                enemies.push(new Scion());
                break;
            case 6:
                enemies.push(new Inferius());
                break;
            case 7:
                enemies.push(new Boss1());
                break;
            case 8:
                enemies.push(new Boss2());
                break;
            case 9:
                enemies.push(new Boss3());
                break;
            case 10:
                enemies.push(new Boss4());
                break;
            case 11:
                enemies.push(new Boss5());
                break;
        }
    }
}

void createLevels(LevelsLL<Level*> &levels)
{
    // level count for dungeon
    const int levelCount = 5;

    // room count per level
    int roomCount[levelCount] = {10, 10, 12, 12, 14};

    // 2D vector to show if room has combat
    std::vector<std::vector<int>> roomContents = {
        {0, 1, 0, 1, 1, 0, 1, 0, 1, 1},           // level 1 : 6 enemeies
        {0, 1, 1, 2, 1, 0, 1, 1, 0, 1},           // level 2 : 6 enemeies
        {0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1},        // level 3 : 7 enemeies
        {0, 1, 1, 0, 1, 2, 1, 1, 0, 1, 0, 1},        // level 4 : 7 enemeies
        {0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1}   // level 5 : 8 enemeies
    };

    // level creation loop
    
    int globalRoomNum = 1;

    for (int i = 0; i < levelCount; ++i)
    {
        Level *level = new Level(i + 1);   // create level

        for (int j = 0; j < roomCount[i]; ++j)
        {
            Room *room = new Room(globalRoomNum, roomContents[i][j]);   // create room

            level->addRoom(room);   // add current room to level
            
            globalRoomNum++;
        }

        levels.insert(level);   // add current level to levels
    }
}

Room *findRoom(LevelsLL<Level*> &levels, int roomNum)
{
    LinkedListIterator<Level*> levelIter = levels.begin();

    while (levelIter != levels.end())
    {
        Level *level = *levelIter;

        for (int i = 0; i < level->getRoomCount(); ++i)
        {
            Room *room = level->getRoom(i);

            if (room->getRoomNum() == roomNum)
            {
                return room;   // return found room
            }
        }

        ++levelIter;
    }

    return nullptr;   // room not found
}

int enterNextRoom(LinkedListIterator<Level*> &levelIter, LevelsLL<Level*> &levels, Graph &roomGraph, Room *&currentRoom, bool &beatGame)
{
    Level* currentLevel = *levelIter;   // get current level from iter
    
    if (currentRoom == nullptr)
    {
        currentRoom = currentLevel->getRoom(0);   // enter very first room
    }
    else
    {     
        int previousLevelNum = currentLevel->getLevelNum();
        int roomNum = currentRoom->getRoomNum();

        GraphLL<int> &adjacentRooms = roomGraph.getAdjacentVertices(roomNum);   // get room's adjacent vertices 

        if (adjacentRooms.isEmptyList())   // last room has no adjacent rooms
        {
            beatGame = true;
            return 0; 
        }

        std::vector<int> roomChoices;
        LinkedListIterator<int> graphIter = adjacentRooms.begin();
        
        while (graphIter != adjacentRooms.end())   // add adjacent vertices to roomChoices
        {
            roomChoices.push_back(*graphIter);
            ++graphIter;
        }

        int nextRoomNum;

        if (adjacentRooms.length() > 1)
        {
            std::cout << "The group sees two paths ahead.\n\n";

            std::cout << "Do they venture left or right?" << std::endl;

            std::string direction;

            std::cin >> direction;
            while (direction != "left" && direction != "right")
            {
                resetStream();
                std::cout << "Enter a direction." << std::endl;
                std::cin >> direction;
            }

            resetStream();
            std::cout << std::endl;

            srand(time(NULL));   // direction is random each time regardless of user choice - haha

            int roomChoice = rand() % 2;  

            nextRoomNum = roomChoices[roomChoice];
        }
        else 
        {
            nextRoomNum = roomChoices[0];
        }

        currentRoom = findRoom(levels, nextRoomNum);

        levelIter = levels.begin();

        while (levelIter != levels.end())   // iterate through the levels
        {
            currentLevel = *levelIter;

            int firstRoom = currentLevel->getRoom(0)->getRoomNum();

            int lastRoom = currentLevel->getRoom(currentLevel->getRoomCount() - 1)->getRoomNum();

            if (nextRoomNum >= firstRoom && nextRoomNum <= lastRoom) break;

            ++levelIter;
        }

        if (levelIter == levels.end())
        {
            beatGame = true;
            return 0;
        }

        if (currentLevel->getLevelNum() != previousLevelNum)
        {
            std::cout << "Made it to Level " << currentLevel->getLevelNum() << "!" << std::endl;
        }
    }

    if (currentRoom->roomContents() == 1)
    {
        std::cout << "They enter the next room, and a menacing shadow begins to emerge from the darkness.\n\n";
        enter();
    }
    else if (currentRoom->roomContents() == 2)
    {
        std::cout << "They enter the next room, and off in the distance, they spot a glowing campfire.\n\n";
        enter();
    }
    else if (currentRoom->roomContents() == 0)
    {
        std::cout << "They enter the next room, and spot a small wooden chest, hidden under some fallen rock.\n\n";
        enter();
    }

    return currentRoom->roomContents();
}

void enemyAttack(EStack<Enemy*> &enemies, Character *characters[4], bool &startCombat, bool &playerAlive)
{
    // check for living players

    std::vector<int> livingPlayers;

    for (int i = 0; i < 4; ++i) 
    {
        if (!characters[i]->isDead())   // add living players to vector
        {
            livingPlayers.push_back(i);
        }
    }

    if (livingPlayers.empty()) // if players are all dead
    {
        playerAlive = false;
        startCombat = false;
    }

// enemy attack section

    if (startCombat)
    {
        Character *target = nullptr;

        int weights[4] = {50, 30, 15, 5};   // attack weight per player
        int totalWeight = 0;
            
        for (int i = 0; i < livingPlayers.size(); ++i)   // add weight based on players alive
        {
            totalWeight += weights[livingPlayers[i]];
        }
        
        srand(time(NULL));   // true randomness
        int attackNum = rand() % totalWeight;   // roll random attackNum

        int attackNumSearch = 0;

        for (int i = 0; i < livingPlayers.size(); ++i)   // allign attackNum with living player
        {
            attackNumSearch += weights[livingPlayers[i]];

            if (attackNumSearch > attackNum) 
            {
                target = characters[livingPlayers[i]];   // target chosen player
                break;
            }
        }

        enemies.top()->attack(*target);   // enemy attacks targeted player

        enter();
    }
}

void playerAttack(EStack<Enemy*> &enemies, Character *characters[4], bool &startCombat, bool &playerAlive, bool &beatGame, Inventory &inventory)
{
    // check for living players

    std::vector<int> livingPlayers;

    for (int i = 0; i < 4; ++i)
    {
        if (!characters[i]->isDead())   // add living players to vector
        {
            livingPlayers.push_back(i);
        }
    }
    
    if (livingPlayers.empty()) // if players are all dead
    {
        playerAlive = false;
        startCombat = false;
    }

// player attack section

    if (startCombat)
    {
        std::cout << "Choose which player acts:" << std::endl;

        // output living players
        for (int i = 0; i < 4; ++i) 
        {
            if (!characters[i]->isDead())
            {
                std::cout << i + 1 << ". " << characters[i]->getCharacterName() << ", the " << characters[i]->getProfession() << std::endl;
            }
        }

        if (inventory.ifItems())
        {
            std::cout << "5. or use an item" << std::endl;
        } 

        int choice;
        bool validChoice = false;

        // living player choice validation
        std::cin >> choice;
        if (choice == 5 && inventory.ifItems())
        {
            validChoice = true;
        }

        while (!validChoice) 
        {
            while (choice < 1 || choice > 4)
            {
                resetStream();
                std::cout << "Choose which player acts:" << std::endl;
                std::cin >> choice;
            }

            if (!characters[choice-1]->isDead()) 
            {
                validChoice = true;
            }
            else
            {
                resetStream();
                std::cout << "Choose a living player" << std::endl;
                std::cin >> choice;
            }
        }

        if (choice == 5)   // item selection
        {
            inventory.printInventory();

            int itemChoice;

            std::cin >> itemChoice;
            while (itemChoice < 1 || itemChoice > 4 || !inventory.search(itemChoice))
            {
                resetStream();
                std::cout << "Select a valid item" << std::endl;
                std::cin >> itemChoice;
            }

            inventory.performItemAbility(itemChoice, characters);
    
        }
        else if (choice == 4)   // healer actions
        {
            std::cout << "1. Self Heal" << std::endl;
            std::cout << "2. Heal Others" << std::endl;
            int healChoice;

            // input validation
            std::cin >> healChoice;
            while (healChoice < 1 || healChoice > 2)
            {
                resetStream();
                std::cout << "Enter 1 or 2" << std::endl;
                std::cin >> healChoice;
            }

            // perform healer action
            if (healChoice == 1 && characters[3]->getHealth() != characters[3]->getHealthCapacity())
            {
                characters[3]->selfHeal();
            }
            else if (healChoice == 1 && characters[3]->getHealth() == characters[3]->getHealthCapacity())
            {
                std::cout << characters[3]->getCharacterName() << "'s health is already full. Healing others instead.";
                
                characters[3]->healOthers(characters);
            }
            else
            {
                characters[3]->healOthers(characters);
            }
        }
        else   // chosen player 1-3 attacks
        {
            characters[choice - 1]->attack(*enemies.top());
        }

        // check if enemy has been defeated
        if (enemies.top()->isDead())
        {
            enemies.pop();
            startCombat = false;

            if (enemies.isEmptyStack())
            {
                beatGame = true;
            }
            else   // choose a player to level up
            {
                std::cout << "Level up:" << std::endl;
                int levelUpChoice;

                // output all players
                for (int i = 0; i < 4; ++i) 
                {
                    std::cout << i + 1 << ". " << characters[i]->getCharacterName() << ", the " << characters[i]->getProfession() << std::endl;
                }

                // input validation
                std::cin >> levelUpChoice;
                while (levelUpChoice < 1 || levelUpChoice > 4)
                {
                    resetStream();
                    std::cout << "Level up: (1-4)" << std::endl;
                    std::cin >> levelUpChoice;
                }

                // level up chosen player
                switch (levelUpChoice) 
                {
                    case 1: 
                        characters[0]->levelUp();
                        break;
                    case 2:
                        characters[1]->levelUp();
                        break;
                    case 3: 
                        characters[2]->levelUp();
                        break;
                    case 4: 
                        characters[3]->levelUp();
                        break;
                }
                std::cout << std::endl;
            }
        }
        resetStream();
        enter();
    }
}

void combat(EStack<Enemy*> &enemies, Character *characters[4], bool &playerAlive, bool &beatGame, Inventory &inventory)
{
    bool startCombat = true;

    Queue<std::string> turns;

    // attack order
    turns.enqueue("enemy");   // enemy attacks first
    turns.enqueue("player");

    while (startCombat && playerAlive) {

        // enemy's turn
        if (turns.front() == "enemy") 
        {
            enemyAttack(enemies, characters, startCombat, playerAlive);
            turns.dequeue();
            turns.enqueue("enemy");
        }
        
        // players' turn
        else if (turns.front() == "player")
        {
            playerAttack(enemies, characters, startCombat, playerAlive, beatGame, inventory);
            turns.dequeue();
            turns.enqueue("player");
        }
    }
}

bool merchant(EStack<Enemy*> &enemies, Inventory &inventory)
{
    std::cout << "Sitting by the fire they see an old man covered in tattered rags.\n\n";
    enter();
    
    std::string choice;

    std::cout << "Do they sit down beside him or do they walk by?\n";
    std::cin >> choice;
    resetStream();

    while (choice != "sit" && choice != "walk")
    {
        
        std::cout << "Type \"sit\" or \"walk\"" << std::endl;
        std::cin >> choice;
        resetStream();
    }

    if (choice == "walk")
    {
        return false;
    }

    std::cout << "\nAs they sit down and talk to the man, he offers them wisdom and some inventory to help them on thier journey.\n\n";
    std::cout << "Although, the help does not come free, and he asks for something in return.\n\n";
    enter();

    std::cout << "Do they offer to trade with the merchant, or do they take all that he has for themselves.\n";
    std::cin >> choice;
    resetStream();

    while (choice != "trade" && choice != "take")
    {
        std::cout << "Type \"trade\" or \"take\"" << std::endl;
        std::cin >> choice;
        resetStream();
    }

    // stealing section

    if (choice == "take")
    {
        std::cout << "\nAs they rummage through his things, the old man becomes enraged at thier disrespect.\n\n";
        std::cout << "The merchant stands up to reveal that he is not a measly old man, but an ancient samurai warrior taking refuge in the cave.\n\n";
        enter();

        enemies.push(new Merchant());
        
        return true;
    }

    // trade section
    
    std::cout << "\nThe merchant shows them his wares.\n\n";

    inventory.printMerchantItems();
        
    int itemNum;

    std::cout << "\nChoose an item to purchase or Enter 0 to leave." << std::endl;
    std::cin >> itemNum;

    while (itemNum != 0)
    {
        while (itemNum < 0 || itemNum > 3)
        {
            resetStream();
            std::cout << "Enter 1-3 or 0" <<std::endl;
            std::cin >> itemNum;
        }

        if (itemNum == 0) break;
        
        if (inventory.getCoins() < inventory.getItemCost(itemNum)) 
        {
            std::cout << "You do not have enough coins.\n\n";

            return false;
        }

        switch (itemNum) 
        {
            case 1:
                inventory.insert("Small Health Potion");
                break;
            case 2:
                inventory.insert("Large Health Potion");
                break;
            case 3:
                inventory.insert("Revive Potion");
                break;
            case 4:
                inventory.insert("Strength Potion");
                break;
            case 5:
                // add more
                break;
        }

        inventory.payCoins(inventory.getItemCost(itemNum));
        
        std::cout << "The merchant thanks them for their purchase.\n\n";
        
        std::cout << "You now have " << inventory.getCoins() << " coins.\n\n";
        enter();

        std::cout << "Choose another item to purchase or Enter 0 to leave." << std::endl;
        std::cin >> itemNum;
    }

    std::cout << "\nThe merchant bids them farwell and goodluck on their journey.\n\n";

    return false;
}

void chest(Inventory &inventory)
{
    srand(time(NULL));   // true randomness
    int chestNum = rand() % 10 + 1;

    if (chestNum < 4) // increase to 5 once strength potion is complete
    {
        std::cout << "They uncover the chest and find a " << inventory.getItemName(chestNum) << " hidden within.\n\n";
        enter();

        inventory.insert(inventory.getItemName(chestNum));
    }
    else 
    {
        int coinsNum = rand() % 25 + 15;

        std::cout << "They uncover the chest and find a stack of " << coinsNum << " coins.\n\n";
        enter();
        
        inventory.addCoins(coinsNum);
    }
}

void displayCharacterStats(Character *characters[4], int &teamDeaths, Inventory &inventory)
{
    if (teamDeaths != 0)
    {
        std::cout << "\nTeam Deaths: " << teamDeaths << "\n\n";
    }

    std::cout << *characters[0] << std::endl;
    std::cout << *characters[1] << std::endl;
    std::cout << *characters[2] << std::endl;
    std::cout << *characters[3] << std::endl;
    std::cout << "Coins: " << inventory.getCoins() << std::endl;
    inventory.printInventory();
    std::cout << std::endl;
}

std::string resetPlayers(Character *characters[4], int &teamDeaths, Inventory &inventory)
{
    std::cout << "Everyone has died. Back to the beginning they go.\n\n";

    std::cout << "Would you like to see your current character stats? (y or n)" << std::endl;
        
    std::string input;
    std::cin >> input;

    // output current character stats
    if (input == "y" || input == "Y") 
    {
        resetStream();

        displayCharacterStats(characters, teamDeaths, inventory);

        enter();
    }

    // revive players
    characters[0]->resetHealth();
    characters[1]->resetHealth();
    characters[2]->resetHealth();
    characters[3]->resetHealth();

    std::cout << "Still trapped in the cave, but now with a new sense of mortality, the four travelors make their way deeper into the cave to the first chamber.\n\n";

    std::cout << "(C)ontinue or (Q)uit?" << std::endl;
    std::string playGame;
    std::cin >> playGame;
    resetStream();
    std::cout << std::endl;

    return playGame;
}

void beatGameMsg(Character *characters[4], int &teamDeaths, Inventory &inventory)
{
    std::cout << "Well done! You have beaten the game! Thank you for taking the time to play my game.\n\n";
        
    std::cout << "Here are your final character stats.\n\n";

    enter();
    
    displayCharacterStats(characters, teamDeaths, inventory);
}

#endif