#if !defined(Creatures_h)
#define Creatures_h

#include <Windows.h>
#include <string>
#include <tuple>
#include <vector>
using namespace std;

class EntityBase
{
    protected:
        int type = 0; // 0 - тип по умолчанию, служебный
        char selfChar = '*';
        std::string selfColor = "36";
    public:
        EntityBase(){};
        int getType();
        std::string getChar(); // Возвращает сразу строку со своим символом и правильным циветом
}; 
class TowerBase
{
    private:
        int type = 0; // 0 - тип по умолчанию, служебный
        char selfChar = '*';
        std::string selfColor = "36";
    public:
        TowerBase(){};
        int getType();
        std::string getChar(); // Возвращает сразу строку со своим символом и правильным циветом
};

class testEntity: public EntityBase
{

    public:
        testEntity(char selfChar, string color, int type){
            this->type = 1;
            this->selfColor = color;
            this->selfChar = selfChar;
        };
};


#endif 
