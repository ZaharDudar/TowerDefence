#include <string.h>
#include <iostream>
// Базовый класс Башни type = 0 - по умолчанию.

class TowerBase
{
    private:
        int type = 0;
        char selfChar = '*';
        std::string selfColor = "36";
    public:
        TowerBase(/* args */);
        int getType(){return type;};
        std::string getChar(){return "\x1B[" + selfColor + "m" + selfChar + "\033[0m";} // Возвращает сразу строку со своим символом и правильным циветом
};

TowerBase::TowerBase(/* args */)
{
}

