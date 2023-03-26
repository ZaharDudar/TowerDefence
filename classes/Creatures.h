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
        mutable int hp = 0;
        int type = 0; // 0 - тип по умолчанию, служебный
        char selfChar = '*';
        int create_tick= -1;
        vector<string> colors_hp{"30","31","32","33","34","35","36","37"};
    public:
        EntityBase(){};
        virtual int getHp();
        virtual bool isAlive();
        virtual bool takeDamage(int);
        virtual int getType();
        virtual int getIndPos(int);
        virtual std::string getChar(); // Возвращает сразу строку со своим символом и правильным циветом
}; 
class TowerBase
{
    protected:
        int type = 0; // 0 - тип по умолчанию, служебный
        char selfChar = '*';
        int  r = 0;
        int damage = 0;
        std::string selfColor = "36";
    public:
        TowerBase(){};
        virtual int getType();
        virtual int getDamage ();
        virtual std::string getChar(); // Возвращает сразу строку со своим символом и правильным циветом
        virtual vector<vector<int>> getRelativeCoord();
};

class Zombie: public EntityBase
{
    public:
        Zombie(char selfChar, int type, int create_tick, int hp){
            this->type = type;
            this->hp = hp;
            this->selfChar = selfChar;
            this->create_tick = create_tick;
        };
};

class Tower: public TowerBase
{

    public:
        
        Tower(char selfChar, string color, int type, int r, int damage){
            this->type = 1;
            this->selfColor = color;
            this->selfChar = selfChar;
            this->r = r;
            this->damage = damage;
        };

        // vector<vector<int>> getRelativeCoord() override;
};

#endif 
