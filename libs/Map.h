#include <vector>
#include <iostream>
/* Предполагаю, что в этом классе хранится вся карта по уровням:
    Типа нижний уровень, сама карта:
    ########
    .......#
    ######.#
    #......#
    #.######
    #.......
    ########
    Все закодировано не символами, а индексами типа:
    0 - .
    1 - #
    ...
    Дальше два массива: 
    entities[]
    towers[]
    Содержат информацию о положении каждого врага/каждой башни на карте, и отрисовываются поверх основной карты.
    Такое разделение будет удобно для отрисовки, вычислением дистанций и т.п. 
    В можно добавить к позиции просто индект типа (например: 0 - ближнебойная, 1 - дальнобойная)

*/
using std::vector, std::find;

class Map
{
    private:
        int width = 0;
        int height = 0;
        vector<vector<int>> map;
        vector<vector<int>> entities;
        vector<vector<int>> towers;
    public:
        Map(int, int, vector<vector<int>>&);//Конструктор, передаю размеры поля и само поле формата vector<vector<int>>
        void move(int, int, int, int);//Пока что не реализовал
        int getIndexOfTower(int, int);//По координате возвращает индекс Башни на поле
        int getIndexOfEntity(int, int);//По координате возвращает индекс Существа на поле
        int addTower(int, int);//Добавляет Башню на поле в заданное место
        int addEntitiy(int, int);//Добавляет Существо на поле в заданное место
        void DedugPrintMap();//Выводит в консоль карту, сама карта - цифрами, башня - #, существо - @. ТОЛЬКО ДЛЯ ДЕБАГА, ВЫВОД В КОНСОЛЬ БУДЕТ ОСУЩЕСТВЛЯТЬСЯ С ПОМОШЬЮ КЛАССА Display
};

Map::Map(int width, int height, vector<vector<int>>& inpMap)
{
    this->width = width;
    this->height = height;
    vector<int> line;
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            line.push_back(inpMap[y][x]);
        }
        map.push_back(line);
        line = {};
    }
    
}

int Map::getIndexOfEntity(int x, int y)
{
    vector<int> pos = {x, y};
  
    for (int i = 0; i < entities.size(); i++)
    {
        if(entities[i][0] == x && entities[i][1] == y){
            return i;
        }      
    }
    return -1; 
}
int Map::getIndexOfTower(int x, int y)
{
    vector<int> pos = {x, y};
    for (int i = 0; i < towers.size(); i++)
    {
        if(towers[i][0] == x && towers[i][1] == y){
            return i;
        }      
    }
    return -1;
}

int Map::addEntitiy(int x, int y)
{
    entities.push_back(vector<int> {x,y});
    return entities.size() - 1;
}
int Map::addTower(int x, int y)
{
    towers.push_back(vector<int> {x,y});
    return towers.size() - 1;
}

void Map::DedugPrintMap()
{
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            if (getIndexOfEntity(x, y) != -1){
                std::cout << "@" << " ";
            }
            else if (getIndexOfTower(x, y) != -1){
                std::cout << "#" << " ";
            }
            else{
                std::cout << map[y][x] << " ";
            }
        }
        std::cout << "\n";
    }
}

