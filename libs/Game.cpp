#include <iostream>
#include <sstream>
#include ".\libsHeader.h"
#include <Windows.h>
#include <string.h>
#include <thread>
#include <chrono>
#include <utility>
#include <vector>
#include <conio.h>

using namespace std;

void Game::start_game(int difficulty)
{
	this->difficulty = difficulty;
	this->money = 60;
	this->TICK_TIME = 100;
	outInfo.push_back("Tick = " + to_string(0));
	outInfo.push_back("Score = " + to_string(0));
	outInfo.push_back("Your money = " + to_string(money));
	outInfo.push_back("First tower: &, range 1, damage 5, cost: 30");
	outInfo.push_back("Secons tower: $, range 2, damage 3, cost: 10");
	outInfo.push_back("");


	MapandPath map = create_map();
	int h = map.map.size();
	int w = map.map[0].size();
	Map mapSt1(w, h, map.map, map.path);
	this->mapSt = mapSt1;
	Display disp1(0, 0);
	this->disp = disp1;
	disp.setVisibleCursor(false);
	thread t1(&Game::game_func, this);
	thread t2(&Game::interface_func, this);
	thread t3(&Game::cursor_func, this);
	t2.join();
}


void Game::cursor_func() {
	while (1) {
		if (GetKeyState('W') & 0x800) {
			disp.move_cur(0, -1);
		}
		else if (GetKeyState('A') & 0x800) {
			disp.move_cur(-1, 0);
		}
		else if (GetKeyState('S') & 0x800) {
			disp.move_cur(0, +1);
		}
		else if (GetKeyState('D') & 0x800) {
			disp.move_cur(1, 0);
		}
		else if (GetKeyState(0x0D) & 0x800) {
			pair<int, int> p = disp.get_cur();
			if (mapSt.check_coord_for_tower(p.first, p.second)) {
				if (selected_tower == 1 && money>= 30) {
					mapSt.addTower(p.first, p.second, Tower('&', "32", 1, 1, 5));
					this->money = money - 30;
				}
				else if (selected_tower == 2 && money >= 10) {
					mapSt.addTower(p.first, p.second, Tower('$', "32", 1, 2, 3));
					this->money = money - 10;
				}
			}
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}
}


void Game::interface_func() {
	
	bool key_down = false;
	string can_buy_str;
	while (1) {
		if (selected_tower != 0)
		{
			if ((selected_tower == 1 && money >= 30) || (selected_tower == 2 && money >= 10)) {
				can_buy_str = " can buy";
			}
			else { can_buy_str = " can not buy"; }

			outInfo[5] = ("selected tower: " + to_string(selected_tower) + can_buy_str);

		}
		else
		{
			outInfo[5] = ("");
		}
		if (GetKeyState('1') & 0x800)
		{
			this->selected_tower = 1;
		}
		if (GetKeyState('2') & 0x800)
		{
			this->selected_tower = 2;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
		disp.printInfo(outInfo);
		disp.draw(mapSt);

	}
}


void Game::game_func() {
	int tick = 0;
	while (true)
	{
		
		std::this_thread::sleep_for(std::chrono::milliseconds(TICK_TIME));
		

		mapSt.generate(difficulty);

		pair<bool, int> mind_score = mapSt.tick();
		bool mind = mind_score.first;
		int score = mind_score.second;
		this->money = money + score * 2;
		if (mind)
		{
			break;
		};

		

		outInfo[0] = ("Tick = " + to_string(mapSt.get_tick()));
		outInfo[1] = ("Score = " + to_string(mapSt.get_score()));
		outInfo[2] = ("Your money = " + to_string(money));
		outInfo[3] = ("First tower: &, range 1, damage 5, cost: 30");
		outInfo[4] = ("Secons tower: $, range 2, damage 3, cost: 10");

		

	}

}


MapandPath Game::create_map() {
	std::vector<int> a(49, 1);
	std::vector<std::vector<int>> inpMap(49, a);
	int h = inpMap.size();
	int w = inpMap[0].size();
	std::vector<std::vector<int>> path;
	int path_x = 1;
	int path_y = 1;
	while (1)
	{
		if (path_y >= w - 1)
		{
			break;
		};

		path.push_back(vector<int>{path_x, path_y});

		if (path_y % 4 == 1 && path_x != h - 2)
		{
			path_x++;
		}
		else if ((path_x == 1 || path_x == h - 2))
		{
			path_y++;
			if (path_y > w - 1)
			{
				break;
			};
			path.push_back(vector<int>{path_x, path_y});

			path_y++;
			if (path_y > w - 1)
			{
				break;
			};
			path.push_back(vector<int>{path_x, path_y});
			if (path_y % 4 == 1)
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
	};


	for (int i = 0; i < path.size(); i++)
	{
		cout << path[i][0] << ' ' << path[i][1] << endl;
		inpMap[path[i][0]][path[i][1]] = 0;
	}
	MapandPath return_type;
	return_type.map = inpMap;
	return_type.path = path;
	return return_type;
}