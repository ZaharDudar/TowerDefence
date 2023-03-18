#include "..\libs\libsHeader.h"
#include "..\classes\Creatures.h"
#include <iostream>
#include <vector>
#include <conio.h>
/* Файл с тестом методов класса Map*/
using namespace std;

int main()
{
    cout << "Введите вероятность генерации башень\n";
    int rand_level;
    cin >> rand_level;

    cout << "Введите сложность мобов\n";
    int diff;
    cin >> diff;

    std::vector<int> a(48, 1);
    std::vector<std::vector<int>> inpMap(48, a);
    int h = inpMap.size();
    int w = inpMap[0].size();
    std::vector<std::vector<int>> path;
    int path_x = 0;
    int path_y = 0;
    while (1)
    {
        if (path_y >= w - 1)
        {
            break;
        };

        path.push_back(vector<int>{path_x, path_y});

        if (path_y % 4==0 && path_x != h-2 ){
            path_x++;
        }
        else if((path_x == 0 || path_x == h-2)){
            path_y+=2;
            path.push_back(vector<int>{path_x, path_y-1});
            path.push_back(vector<int>{path_x, path_y});
            if (path_y%4==0){
                path_x++;

            }
            else {
                path_x--;

            }
            path.push_back(vector<int>{path_x, path_y});

        }
        else{
            path_x--;
        }
        // if (path_x > path_y)
        // {
        //     path_y++;
        // }
        // else
        // {
        //     path_x++;
        // }
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

        if (rand()%rand_level!=0 || path[i][0] == 0 || path[i][0] == h-2){
            continue;
        }

        
        
        mapSt.addTower(path[i][1]+1, path[i][0], Tower('&', "32", 1, 1, 5));
        
    }

    while (true)
    {

        mapSt.generate(diff);
        bool mind = mapSt.tick();

        if (mind)
        {
            break;
        };

        disp.draw(mapSt);
        vector<string> outInfo;
        outInfo.push_back("Tick = " + to_string(mapSt.get_tick()));
        outInfo.push_back("Score = " + to_string(mapSt.get_score()));
        outInfo.push_back(string ("Your score is 12"));
        outInfo.push_back(string ("Happy new year!"));
        outInfo.push_back(string ("Happy new year!"));
        outInfo.push_back(string ("Happy new year!"));
        outInfo.push_back(string ("Happy new year!"));
        outInfo.push_back(string ("Happy new year!"));
        outInfo.push_back(string ("Happy new year!"));

        disp.printInfo(outInfo);
        Sleep(TICK_TIME);
    }

    cout << "GAME OVER";
}