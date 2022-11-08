#include <Windows.h>
#include <string>
#include <tuple>
#include <vector>
using namespace std;

class EntityBase
{
    private:
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


class Map
{
    private:
        int width = 0;
        int height = 0;
        vector<vector<int>> map;
        vector<std::tuple<int, int, EntityBase>> entities;
        vector<std::tuple<int, int, TowerBase>> towers;
        vector<char> charOfMapObjects = {".","#"};
        vector<string> colorsOfMapObjects = {"35", "95"};
    public:
        Map(int, int, vector<vector<int>>&);//Конструктор, передаю размеры поля и само поле формата vector<vector<int>>
        void move(int, int, int, int);//Пока что не реализовал
        TowerBase getTower(int, int);//По координате возвращает Башню на поле
        EntityBase getEntity(int, int);//По координате возвращает Существо на поле
        int addTower(int, int, TowerBase);//Добавляет Башню на поле в заданное место
        int addEntitiy(int, int, EntityBase);//Добавляет Существо на поле в заданное место
        void DedugPrintMap();//Выводит в консоль карту, сама карта - цифрами, башня - #, существо - @. ТОЛЬКО ДЛЯ ДЕБАГА, ВЫВОД В КОНСОЛЬ БУДЕТ ОСУЩЕСТВЛЯТЬСЯ С ПОМОШЬЮ КЛАССА Display
        int setStyleToElement(int, char, string&); // Меняет или добавляет (в случае, если объекта на карте с таким индексом нет) цвет и символ элемента
        std::pair<char, string> getStyleOfElement(int); // Возвращает символ и цвет элемента, если его нет, вернёт пару с пустыми строками
        string getPixel(int, int); //Вернёт строку формата "\x1B[" + selfColor + "m" + selfChar + "\033[0m" для конкретной точки на катре
        void loadStyle(); //Пока не реализованно
};

class Display
{
    private:
        int width = 0;
        int height = 0;
        HANDLE hConsole;
        CONSOLE_CURSOR_INFO cursor_info;
        COORD offsetMainMap;        
    public:
        Display(int, int, int, int);
        void draw(Map& map);
};