#include <string.h>
#include <iostream>
// Базовый класс Существа type = 0 - по умолчанию.

class EntityBase
{
    private:
        int type = 0;
        char selfChar = '*';
        std::string selfColor = "36";
    public:
        EntityBase(/* args */);
        int getType(){return type;};
        std::string getChar(){return "\x1B[" + selfColor + "m" + selfChar + "\033[0m";}// Возвращает сразу строку со своим символом и правильным циветом
}; 

EntityBase::EntityBase(/* args */)
{
}

