#ifndef INVENTORY_H
#define INVENTORY_H

#include "characters.h"
#include "items.h"
#include "hashTable.h"
#include <vector>

class Inventory
{
public:
    Inventory();
    ~Inventory();

    void insert(std::string itemName);
    void remove(std::string itemName);
    bool search(std::string itemName);
    bool search(int itemNum);

    std::string getItemName(int itemNum);
    int getItemID(std::string itemName);
    int getItemCost(int itemNum);

    bool ifItems();

    void addCoins(int num);
    void payCoins(int num);
    int getCoins();

    void printInventory();
    void printMerchantItems();

    void performItemAbility(int itemNum, Character *characters[4]);

private:
    std::string itemName;
    int itemNum;
    int num;
    int inventoryCapacity = 5;
    int coins = 20;
    int itemCount = 0;

    std::vector<Item*> items;

    HashTable htArr;
};

// constructor
Inventory::Inventory()
{    
    items.push_back(new SmallHealthPotion());
    items.push_back(new LargeHealthPotion());
    items.push_back(new RevivePotion());
    items.push_back(new StrengthPotion());
}

// destructor
Inventory::~Inventory()
{
    for (int i = 0; i < items.size(); ++i)
    {
        delete items[i];
    }
}

// insert item into hash table
void Inventory::insert(std::string itemName)
{    
    htArr.insert(getItemID(itemName));
    itemCount++;
}

// remove item from hash table
void Inventory::remove(std::string itemName)
{
    htArr.remove(getItemID(itemName));
    itemCount--;
}

// search for item in hash table using name
bool Inventory::search(std::string itemName)
{
    return htArr.search(getItemID(itemName));
}

// search for item in hash table using id
bool Inventory::search(int itemNum)
{
    return htArr.search(itemNum);
}

// return item's name
std::string Inventory::getItemName(int itemNum)
{
    for (int i = 0; i < items.size(); ++i)
    {
        if (items[i]->getItemID() == itemNum)
        {
            return items[i]->getItemName();
        }
    }

    return "";
}

// return item's id number
int Inventory::getItemID(std::string itemName)
{
    for (int i = 0; i < items.size(); ++i)
    {
        if (items[i]->getItemName() == itemName)
        {
            return items[i]->getItemID();
        }
    }

    return -1;
}

// return item's cost
int Inventory::getItemCost(int itemNum)
{
    return items[itemNum - 1]->getItemCost();
}

// check for items
bool Inventory::ifItems()
{
    return (itemCount > 0);
}

// add coins
void Inventory::addCoins(int num)
{
    coins += num;
}

// pay coins
void Inventory::payCoins(int num)
{
    coins -= num;
}

// return coin count
int Inventory::getCoins()
{
    return coins;
}

// print current inventory
void Inventory::printInventory()
{
    std::cout << "Inventory:\n";

    for (int i = 0; i < items.size(); ++i)
    {
        int itemID = items[i]->getItemID();
        int count = htArr.getDuplicates(itemID);

        if (count > 0)
        {
            std::cout << i + 1 << ". "<< items[i]->getItemName() << " x" << count << std::endl;
        }
    }
}

// print merchant's wares
void Inventory::printMerchantItems()
{
    for (int i = 0; i < items.size(); ++i)
    {
        std::cout << i + 1 << ". " << *items[i];
    }
}

// perform each item's ability
void Inventory::performItemAbility(int itemNum, Character *characters[4])
{
    Item *selectedItem = nullptr;

    for (int i = 0; i < items.size(); ++i)
    {
        if (items[i]->getItemID() == itemNum)
        {
            selectedItem = items[i];
            break;
        }
    }

    bool validUse = false;
    validUse = selectedItem->use(characters);

    if (validUse) 
    {
        htArr.remove(itemNum);
        itemCount--;
    }
}

#endif