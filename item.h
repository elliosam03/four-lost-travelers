#ifndef ITEM_H
#define ITEM_H

class Character;

class Item 
{
public:
    Item();
    Item(std::string itemName, std::string itemAbility, int itemID, int itemCost);
    
    std::string getItemName() const;
    std::string getItemAbility() const;
    int getItemID() const;
    int getItemCost() const;

    virtual bool use(Character *characters[4]) = 0;

    friend std::ostream &operator<<(std::ostream &outputStream, const Item &itemToPrint);

private:
    std::string itemName;
    std::string itemAbility;
    int itemID;
    int itemCost;
};

// default constructor
Item::Item()
{
    itemName = "";
    itemAbility = "";
    itemID = 000;
    itemCost = 0;
}

// constructor with values
Item::Item(std::string itemName, std::string itemAbility, int itemID, int itemCost)
{
    this->itemName = itemName;
    this->itemAbility = itemAbility;
    this->itemID = itemID;
    this->itemCost = itemCost;
}

// getters

std::string Item::getItemName() const
{
    return itemName;
}

std::string Item::getItemAbility() const
{
    return itemAbility;
}

int Item::getItemID() const
{
    return itemID;
}

int Item::getItemCost() const
{
    return itemCost;
}

// friendly output function
std::ostream &operator<<(std::ostream &outputStream, const Item &itemToPrint) 
{
    outputStream << itemToPrint.itemName << " - " << itemToPrint.itemAbility << " - Costs: " << itemToPrint.itemCost << std::endl;

    return outputStream;
}

#endif