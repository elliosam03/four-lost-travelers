#ifndef ROOM_H
#define ROOM_H

class Room
{
private:
    int roomNum;
    int contents;

public:
    Room();
    Room(int roomNum, int contents);

    int roomContents();

    int getRoomNum() const;
};

// default constructor
Room::Room()
{
    roomNum = 0;
    contents = 0;
}

// constructor with values
Room::Room(int roomNum, int contents)
{
    this->roomNum = roomNum;
    this->contents = contents;
}

// check what room contains
int Room::roomContents()
{
    return contents;
}

// return room number
int Room::getRoomNum() const
{
    return roomNum;
}

#endif