#ifndef LEVEL_H
#define LEVEL_H

#include "room.h"
#include <vector>

class Level
{
private:
    int levelNum;
    std::vector<Room*> rooms;

public:
    Level();
    Level(int levelNum);
    ~Level();

    void addRoom(Room *room);

    int getLevelNum() const;
    int getRoomCount() const;
    Room *getRoom(int index) const;
};

// default constructor
Level::Level()
{
    levelNum = 0;
}

// constructor with value
Level::Level(int levelNum)
{
    this->levelNum = levelNum;
}

// destructor
Level::~Level()
{
    for (int i = 0; i < rooms.size(); ++i)
    {
        delete rooms[i];
    }
}

// add room to level
void Level::addRoom(Room *room)
{
    rooms.push_back(room);
}

// getters

int Level::getLevelNum() const
{
    return levelNum;
}
 
int Level::getRoomCount() const
{
    return rooms.size();
}

Room* Level::getRoom(int index) const
{
    return rooms[index];
} 

#endif