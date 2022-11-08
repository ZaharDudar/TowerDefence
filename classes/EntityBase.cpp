#include <string.h>
#include <iostream>
#include "../mainHeader.h"
// Базовый класс Существа type = 0 - по умолчанию.

int EntityBase::getType(){
    return this->type;
}
std::string EntityBase::getChar(){
    return "\x1B[" + selfColor + "m" + selfChar + "\033[0m";
}

