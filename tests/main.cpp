#include "..\libs\libsHeader.h"
#include "..\classes\Creatures.h"
#include <iostream>
#include <sstream>
#include <chrono>
#include <thread>
#include <utility>
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

    /*Переменные для покупки и установки башен*/
    int money = 60;
    int selected_tower = 0;
    bool is_selected = false;
    bool key_down = false;
    vector<string> outInfo;
    std::string can_buy_str;

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

        if (path_y % 4 == 0 && path_x != h - 2)
        {
            path_x++;
        }
        else if ((path_x == 0 || path_x == h - 2))
        {
            path_y += 2;
            path.push_back(vector<int>{path_x, path_y - 1});
            path.push_back(vector<int>{path_x, path_y});
            if (path_y % 4 == 0)
            {
                path_x++;
            }
            else
            {
                path_x--;
            }
            path.push_back(vector<int>{path_x, path_y});
        }
        else
        {
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

        if (rand() % rand_level != 0 || path[i][0] == 0 || path[i][0] == h - 2)
        {
            continue;
        }

        mapSt.addTower(path[i][1] + 1, path[i][0], Tower('&', "32", 1, 1, 5));
    }
    while (true)
    {

        mapSt.generate(diff);
        bool mind = mapSt.tick();

        if (mind)
        {
            break;
        };
        outInfo.clear();
        disp.draw(mapSt);
        outInfo.push_back("Tick = " + to_string(mapSt.get_tick()));
        outInfo.push_back("Score = " + to_string(mapSt.get_score()));
        outInfo.push_back("Your money = " + to_string(money));
        outInfo.push_back("First tower: &, range 1, damage 5, cost: 30");
        outInfo.push_back("Secons tower: $, range 2, damage 3, cost: 10");
        //часть для выбора типа башни
        if (is_selected)
        {
            if (selected_tower == 1 && money >= 30 || (selected_tower == 2 && money >= 10)){can_buy_str = " Can buy";}
            else{can_buy_str = " Can not buy";}

            outInfo.push_back("Selected tower: " + to_string(selected_tower) + can_buy_str);

            if (GetKeyState('1') & 0x800 || GetKeyState('2') & 0x800)
            {
                is_selected = false;
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
        }
        else
        {
            outInfo.push_back("");
            if (GetKeyState('1') & 0x800)
            {
                is_selected = true;
                selected_tower = 1;
            }
            if (GetKeyState('2') & 0x800)
            {
                is_selected = true;
                selected_tower = 2;
            }
        }

        disp.printInfo(outInfo);
        Sleep(TICK_TIME);
    }

    cout << "GAME OVER";
    
}
