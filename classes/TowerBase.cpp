#include <string.h>
#include "../mainHeader.h"
#include <iostream>
// Базовый класс Башни type = 0 - по умолчанию.


int TowerBase::getType(){
    return this->type;
}
std::string TowerBase::getChar(){
    return "\x1B[" + selfColor + "m" + selfChar + "\033[0m";
}
