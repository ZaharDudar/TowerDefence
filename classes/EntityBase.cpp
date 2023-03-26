#include <string.h>
#include <iostream>
#include ".\Creatures.h"
// Базовый класс Существа type = 0 - по умолчанию.

int EntityBase::getType()
{
    return this->type;
}
int EntityBase::getIndPos(int tick)
{
    return tick - create_tick;
}
std::string EntityBase::getChar()
{ 
   double color_index = (((double)hp) /((double)created_hp)) * ((int)colors_hp.size()-1);
    
    string selfColor = colors_hp[(int)color_index];
    return "\x1B[" + selfColor + "m" + selfChar + "\033[0m";
}

int EntityBase::getHp(){
    return this->hp;
}

bool EntityBase::takeDamage(int damage){
    this->hp-=damage;
    bool mind = true;
    if ((this->hp)<=0){
        mind = false;
    };
    return mind;
}

bool EntityBase::isAlive(){
    return (this->hp)>0;
}
