#include <format>
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
#include <tuple>

using namespace std;

void Game::start_game(int difficulty)
{
	this->difficulty = difficulty;
	this->money = 60;
	this->TICK_TIME = 1000;
	this->towersInfo = { {'@', 1, 1, 1, 10}, {'$', 1, 3, 2, 30}, {'¹', 2, 2, 3,  60}, {'%', 2, 5, 2, 120}, {'&', 3, 4, 4, 200}, {'?', 3, 6, 6, 240}};
	outInfo.push_back("Tick = " + to_string(0));
	outInfo.push_back("Score = " + to_string(0));
	outInfo.push_back("Your money = " + to_string(money));
	outInfo.push_back("");

	for (size_t i = 0; i < towersInfo.size(); i++)
	{
		tuple<char, int, int, int, int> tower = towersInfo[i];
		outInfo.push_back(format("{} tower: {}, range {}, damage {}, num targets {}, cost: {}", i+1, std::get<0>(tower), std::get<1>(tower), std::get<2>(tower), std::get<3>(tower), std::get<4>(tower)));
	}
	

	


	MapandPath map = create_map(30);
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
	t1.join();
	t2.join();
	t3.join();
}


void Game::cursor_func() {
	while (alive) {
		if (GetKeyState('W') & 0x800) {
			disp.move_cur(0, -1);
		}
		else if (GetKeyState('A') & 0x800) {
			disp.move_cur(-1, 0);
		}
		else if (GetKeyState('S') & 0x800) {
			disp.move_cur(0, 1);
		}
		else if (GetKeyState('D') & 0x800) {
			disp.move_cur(1, 0);
		}
		else if (GetKeyState(0x0D) & 0x800) {
			pair<int, int> p = disp.get_cur();
			if (mapSt.check_coord_for_tower(p.first, p.second) && selected_tower != 0 && money >= get<4>(towersInfo[selected_tower - 1])) {
				
				mapSt.addTower(p.first, p.second, Tower(get<0>(towersInfo[selected_tower - 1]), "32", selected_tower, get<1>(towersInfo[selected_tower - 1]), get<2>(towersInfo[selected_tower - 1]), get<3>(towersInfo[selected_tower - 1])));
				this->money = money - get<4>(towersInfo[selected_tower - 1]);
				
			}
		}
		else if (GetKeyState(0x1B) & 0x800) {
			alive = false;
			break;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	}
}


void Game::interface_func() {
	

	string can_buy_str;
	while (alive) {
		if (selected_tower != 0)
		{
			if (money >= get<4>(towersInfo[selected_tower-1])) {
				can_buy_str = " can buy";
			}
			else { can_buy_str = " can not buy"; }

			outInfo[3] = ("selected tower: " + to_string(selected_tower) + can_buy_str);

		}
		else
		{
			outInfo[3] = ("");
		}
		for (size_t i = 0; i < towersInfo.size(); i++)
		{
			if (GetKeyState(to_string(i+1).c_str()[0]) & 0x800)
			{
				this->selected_tower = i+1;
			}
		}
		
		
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
		disp.printInfo(outInfo);
		disp.draw(mapSt);

	}
}


void Game::game_func() {

	while (alive)
	{
		
		std::this_thread::sleep_for(std::chrono::milliseconds(TICK_TIME));
		
		if (TICK_TIME > 100) {
			TICK_TIME -= difficulty/10;
		}
		mapSt.generate(difficulty);
		if (mapSt.get_tick() % 5 == 0) {
			difficulty++;
		}
		

		pair<bool, int> mind_score = mapSt.tick();
		bool mind = mind_score.first;
		int score = mind_score.second;
		this->money = money + score * 2;
		if (mind)
		{
			alive = false;
			break;
		};

		

		outInfo[0] = ("Tick = " + to_string(mapSt.get_tick()));
		outInfo[1] = ("Score = " + to_string(mapSt.get_score()));
		outInfo[2] = ("Your money = " + to_string(money));


		

	}
	
}


MapandPath Game::create_map(int size) {
	std::vector<int> a(size, 1);
	std::vector<std::vector<int>> inpMap(size, a);
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