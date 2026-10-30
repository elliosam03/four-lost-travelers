/* Program name: Four Lost Travelers
* Author: Sam Elliott
* Date last updated: 10/29/2026
* Purpose: Dungeon Crawler Game
*/

#include "mainExt.h"

int main() 
{
    // for memory leaks
    // _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    introText();

    // character creation
    Warrior warrior;  Mage mage;  Archer archer;  Healer healer;
    Character *characters[4] = {&warrior, &mage, &archer, &healer};

    Inventory inventory;
    
    bool beatGame = false;
    bool playerAlive = true;
    int contents;
    int teamDeaths = 0;

    std::cout << "The following are your initial player stats: \n\n";
    displayCharacterStats(characters, teamDeaths, inventory);

    std::cout << "(C)ontinue or (Q)uit?" << std::endl;
    std::string playGame;
    std::cin >> playGame;
    resetStream();
    std::cout << std::endl;

    while (playGame != "q" && !beatGame) 
    {
        while (playerAlive && !beatGame)
        {
            // enemy creation
            EStack<Enemy*> enemies;
            createEnemies(enemies);

            // dungeon creation
            LevelsLL<Level*> levels;
            createLevels(levels);

            LinkedListIterator<Level*> levelIter = levels.begin();
            
            Graph rooms;
            rooms.createGraph();
            
            Room* currentRoom = nullptr;

            while (playerAlive && !beatGame) 
            {
                // traverse through rooms
                contents = enterNextRoom(levelIter, levels, rooms, currentRoom, beatGame);

                if (contents == 1)   // fight enemies to progress
                {
                    combat(enemies, characters, playerAlive, beatGame, inventory);
                }
                else if (contents == 2)   // interact with merchant
                {
                    bool angry = merchant(enemies, inventory);

                    if (angry)
                    {
                        combat(enemies, characters, playerAlive, beatGame, inventory);
                    }
                }
                else if (contents == 0)   // discover loot
                {
                    chest(inventory);
                }
            }
        }

        if (!beatGame) 
        {
            teamDeaths++;

            playGame = resetPlayers(characters, teamDeaths, inventory);
            playerAlive = true;
        }
        else   // end game message
        {
            beatGameMsg(characters, teamDeaths, inventory);
        }
    }

    return 0;
}