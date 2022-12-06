#include <vector>
#include <iostream>
#include <tuple>
#include <string.h>
#include ".\libsHeader.h"
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
using std::vector, std::find, std::string, std::get;

Map::Map(int width, int height, vector<vector<int>> &inpMap, vector<vector<int>> &path)
{
    this->path = path;
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

// EntityBase* Map::getEntity(int x, int y)
// {
//     for (int i = 0; i < entities.size(); i++)
//     {
//         if (get<0>(entities[i]) == x && std::get<1>(entities[i]) == y)
//         {
//             return std::get<2>(entities[i]);
//         }
//     }
//     return &(EntityBase());
// }

EntityBase *Map::getEntityById(int x)
{
    return std::get<2>(entities[x]);
}

int Map::getEntityId(int x, int y)
{
    for (int i = 0; i < entities.size(); i++)
    {
        if (get<0>(entities[i]) == x && std::get<1>(entities[i]) == y && (*std::get<2>(entities[i])).isAlive())
        {
            return i;
        }
    }
    return -1;
}

TowerBase Map::getTower(int x, int y)
{
    for (int i = 0; i < towers.size(); i++)
    {
        if (std::get<0>(towers[i]) == x && std::get<1>(towers[i]) == y)
        {
            return std::get<2>(towers[i]);
        }
    }
    return TowerBase();
}

int Map::getTowerId(int x, int y)
{
    for (int i = 0; i < towers.size(); i++)
    {
        if (std::get<0>(towers[i]) == x && std::get<1>(towers[i]) == y)
        {
            return i;
        }
    }
    return -1;
}

int Map::addEntitiy(int x, int y, EntityBase *ent)
{
    std::tuple<int, int, EntityBase *> toPush = {x, y, ent};
    entities.push_back(toPush);
    return entities.size() - 1;
}
int Map::addTower(int x, int y, TowerBase tower)
{
    std::tuple<int, int, TowerBase> toPush = {x, y, tower};
    towers.push_back(toPush);
    return towers.size() - 1;
}

void Map::DedugPrintMap()
{
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            int ent_id = getEntityId(x, y);
            EntityBase ent;
            if (ent_id != -1)
            {
                ent = *get<2>(entities[ent_id]);
            }
            else
            {
                ent = EntityBase();
            }

            TowerBase tow = getTower(x, y);
            if (ent.getType() != 0)
            {
                std::cout << ent.getChar() << " ";
            }
            else if (tow.getType() != 0)
            {
                std::cout << ent.getChar() << " ";
            }
            else
            {
                std::cout << map[y][x] << " ";
            }
        }
        std::cout << "\n";
    }
}
// int Map::setStyleToElement(int i, char ch, string& color)
// {
//     if(i >= colorOfMapObject.begin() || i <= charOfMapOjects.end())
//     {

//     }
// }
std::pair<char, string> Map::getStyleOfElement(int ind)
{
    return std::make_pair(charOfMapObjects[ind], colorsOfMapObjects[ind]);
}

string Map::getPixel(int x, int y)
{
    int ent_id = getEntityId(x, y);
    EntityBase entity;
    if (ent_id != -1)
    {
        entity = *get<2>(entities[ent_id]);
    }
    else
    {
        entity = EntityBase();
    }

    TowerBase tower = getTower(x, y);
    if (entity.getType() != 0)
    {
        return entity.getChar();
    }
    else if (tower.getType() != 0)
    {
        return tower.getChar();
    }
    std::pair<char, string> style = getStyleOfElement(map[y][x]);
    return "\x1B[" + std::get<1>(style) + "m" + std::get<0>(style) + "\033[0m";
}

std::pair<int, int> Map::getSize()
{
    return std::make_pair(this->height, this->width);
}

bool Map::move(int x1, int y1, int x2, int y2)
{
    int entity1 = getEntityId(x1, y1);
    int tower1 = getTowerId(x1, y1);

    int entity2 = getEntityId(x2, y2);
    int tower2 = getTowerId(x2, y2);
    if (entity2 == -1 && tower2 == -1 && width > x2 >= 0 && height > y2 >= 0)
    {
        if (entity1 != -1)
        {
            get<0>(entities[entity1]) = x2;
            get<1>(entities[entity1]) = y2;
        }
        if (tower1 != -1)
        {
            get<0>(towers[tower1]) = x2;
            get<1>(towers[tower1]) = y2;
        }
        return true;
    }
    return false;
}
bool Map::moveEnt(int id, int x2, int y2)
{
    int entity2 = getEntityId(x2, y2);
    int tower2 = getTowerId(x2, y2);
    if (width > x2 >= 0 && height > y2 >= 0)
    {
        get<0>(entities[id]) = x2;
        get<1>(entities[id]) = y2;
        return true;
    }
    return false;
}
bool Map::moveTow(int id, int x2, int y2)
{
    int entity2 = getEntityId(x2, y2);
    int tower2 = getTowerId(x2, y2);
    if (entity2 == -1 && tower2 == -1 && width > x2 >= 0 && height > y2 >= 0)
    {
        get<0>(towers[id]) = x2;
        get<1>(towers[id]) = y2;
        return true;
    }
    return false;
}
bool Map::tick()
{

    for (size_t i = 0; i < towers.size(); i++)
    {
        TowerBase tower = get<2>(towers[i]);
        int x = get<0>(towers[i]);
        int y = get<1>(towers[i]);
        vector<vector<int>> coords = tower.getRelativeCoord();
        for (size_t i1 = 0; i1 < coords.size(); i1++)
        {
            int shoot_x = x + coords[i1][0];
            int shoot_y = y + coords[i1][1];

            int ent_id = getEntityId(shoot_x, shoot_y);

            if (ent_id != -1)
            {
                EntityBase ent = *getEntityById(ent_id);
                bool alive = ent.takeDamage(tower.getDamage());
                // cout << "DEAD" << endl;
                *getEntityById(ent_id) = ent;

                break;
            }
        }
    }

    bool mind = false;
    for (size_t i = 0; i < entities.size(); i++)
    {
        EntityBase z = *get<2>(entities[i]);
        if (z.isAlive())
        {
            if (z.getIndPos(n_tick) >= path.size())
            {
                mind = true;
                break;
            };

            moveEnt(i, path[z.getIndPos(n_tick)][1], path[z.getIndPos(n_tick)][0]);
        }
        else
        {
            // cout << "DEAD_TRue" << endl;
        }
    }

    this->n_tick++;

    return mind;
}

int Map::get_tick()
{
    return this->n_tick;
}

void Map::generate()
{
    int local_tick = get_tick();
    int easy_zombie_tick_gen = (rand() % 4 + 1);
    int strong_zombie_tick_gen = (rand() % 10 + 1);
    if (local_tick % easy_zombie_tick_gen == 0)
    {
        addEntitiy(path[0][0], path[0][1], new Zombie('X', 1, local_tick, 1));
    }
    else if (local_tick % strong_zombie_tick_gen == 0)
    {
        addEntitiy(path[0][0], path[0][1], new Zombie('Z', 1, local_tick, 4));
    };
}