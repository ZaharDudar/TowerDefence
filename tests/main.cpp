#include "..\libs\libsHeader.h"
#include "..\classes\Creatures.h"
#include <iostream>
#include <vector>
#include <conio.h>
/* Файл с тестом методов класса Map*/
using namespace std;

int main()
{

    std::vector<int> a(10, 1);
    std::vector<std::vector<int>> inpMap(10, a);

    std::vector<std::vector<int>> path{
        {0, 0},
        {0, 1},
        {1, 1},
        {1, 2},
        {2, 2},
        {2, 3},
        {3, 3},
        {3, 4},
        {4, 4},
        {4, 5},
        {5, 5},
        {5, 6},
        {6, 6},
        {6, 7},
        {7, 7},
        {7, 8},
        {8, 8},
        {8, 9},
        {9, 9},
    };

    

    int TICK_TIME = 1000;

    int h = inpMap.size();
    int w = inpMap[0].size();

    for (int i = 0; i < path.size(); i++)
    {
        inpMap[path[i][0]][path[i][1]] = 0;
    }

    Display disp(0, 0);
    Map mapSt(w, h, inpMap, path);
    // Zombie z('X', "31", 1, mapSt.get_tick(), 1);
    // mapSt.addEntitiy(path[0][0], path[0][1], &z);
    mapSt.addTower(2, 4, Tower('*', "32", 1, 1, 1));
    mapSt.addTower(5, 2, Tower('*', "32", 1, 1, 1));
    mapSt.addTower(6, 8, Tower('*', "32", 1, 1, 1));
    while (true)
    {

        mapSt.generate();
        bool mind = mapSt.tick();

        if (mind)
        {
            break;
        };

        disp.draw(mapSt);

        cout << endl << mapSt.get_tick() << endl;
        Sleep(TICK_TIME);
    }

    cout << "GAME OVER";
}