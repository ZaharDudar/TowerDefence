#include <string.h>
#include <iostream>

#include ".\Creatures.h"
// Базовый класс Башни type = 0 - по умолчанию.

int TowerBase::getType()
{
    return this->type;
}
int TowerBase::get_num_targets()
{
    return this->num_targets;
}
std::string TowerBase::getChar()
{
    return "\x1B[" + selfColor + "m" + selfChar + "\033[0m";
}

int TowerBase::getDamage(){
    return this->damage;
}

vector<vector<int> > TowerBase::getRelativeCoord() {
    vector<vector<int>> relative_coords;
    for (int x = -1*((this->r)); x <= ((this->r)); x++)
    {
        for (int y = -1*((this->r)); y <= ((this->r)); y++)
        {
            vector<int> _a{x,y};
            relative_coords.push_back(_a);
        }
    }
    return relative_coords;
};