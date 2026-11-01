#ifndef WEAPON_H
#define WEAPON_H

#include <iostream>
#include <string>

class Weapon 
{
private:
    std::string weaponName;
    int weaponDamage;
    int weaponHeal;

public:
    Weapon();
    Weapon(std::string name, int damage, int heal);
    
    std::string getWeaponName() const; 
    int getWeaponDamage() const;
    int getWeaponHeal() const;

    void setWeaponDamage(int weaponDamage);
    void setWeaponHeal(int weaponHeal);
    
    void weaponLevelUp();

    friend std::ostream &operator<<(std::ostream &outputStream, const Weapon &weaponToPrint);
};

// default constructor
Weapon::Weapon() 
{
    weaponName = "";
    weaponDamage = 0;
    weaponHeal = 0;
}

// constructor with values
Weapon::Weapon(std::string name, int damage, int heal) 
{
    weaponName = name;
    weaponDamage = damage;
    weaponHeal = heal;
}
    
// getters

std::string Weapon::getWeaponName() const
{
    return weaponName;
}

int Weapon::getWeaponDamage() const
{
    return weaponDamage;
}

int Weapon::getWeaponHeal() const
{
    return weaponHeal;
}

// setters

void Weapon::setWeaponDamage(int weaponDamage)
{
    this->weaponDamage = weaponDamage;
}

void Weapon::setWeaponHeal(int weaponHeal)
{
    this->weaponHeal = weaponHeal;
}

// weapon upgrade
void Weapon::weaponLevelUp()
{
    if (weaponDamage > 0) {
        weaponDamage += 5;
        std::cout << weaponName << " now does " << weaponDamage << " damage." << std::endl;
    } else {
        weaponHeal += 5;
        std::cout << weaponName << " now does " << weaponHeal << " heal." << std::endl;
    }
}

// friendly output function
std::ostream& operator<<(std::ostream& outputStream, const Weapon& weaponToPrint) 
{
    outputStream << weaponToPrint.weaponName << std::endl;
    if (weaponToPrint.weaponDamage > 0) 
    {
        outputStream << "  Damage: " << weaponToPrint.weaponDamage << std::endl;
    }
    if (weaponToPrint.weaponHeal > 0) 
    {
        outputStream << "  Heal: " << weaponToPrint.weaponHeal << std::endl;
    }

    return outputStream;
}

#endif