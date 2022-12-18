#include "..\libs\libsHeader.h"
#include "..\classes\Creatures.h"
#include <iostream>
#include <vector>
#include <conio.h>
/* Файл с тестом методов класса Map*/
using namespace std;

int main()
{

    std::vector<int> a(48, 1);
    std::vector<std::vector<int>> inpMap(48, a);
    int h = inpMap.size();
    int w = inpMap[0].size();
    std::vector<std::vector<int>> path;
    int path_x = 0;
    int path_y = 0;
    while (1)
    {
        if ((path_x == w - 1) && (path_y == h - 1))
        {
            break;
        };

        path.push_back(vector<int>{path_x, path_y});

        if (path_x > path_y)
        {
            path_y++;
        }
        else
        {
            path_x++;
        }
    };

    int TICK_TIME = 100;

    for (int i = 0; i < path.size(); i++)
    {
        inpMap[path[i][0]][path[i][1]] = 0;
    }

    Display disp(0, 0);
    disp.setVisibleCursor(false);
    Map mapSt(w, h, inpMap, path);
    // Zombie z('X', "31", 1, mapSt.get_tick(), 1);
    // mapSt.addEntitiy(path[0][0], path[0][1], &z);
    for (size_t i = 0; i < path.size(); i++)
    {

        if (rand()%3!=0){
            continue;
        }

        if (path[i][0] == path[i][1])
        {
            mapSt.addTower(path[i][1]+1, path[i][0], Tower('*', "32", 1, 1, 1));
        }
        else
        {
            mapSt.addTower(path[i][1]-1, path[i][0], Tower('&', "32", 1, 1, 2));
        }
    }

    while (true)
    {

        mapSt.generate(20);
        bool mind = mapSt.tick();

        if (mind)
        {
            break;
        };

        disp.draw(mapSt);
        vector<string> outInfo;
        outInfo.push_back("Tick = " + to_string(mapSt.get_tick()));
        outInfo.push_back(string ("Your score is 12"));
        outInfo.push_back(string ("'_'"));


        disp.printInfo(outInfo);
        Sleep(TICK_TIME);
    }

    cout << "GAME OVER";
}