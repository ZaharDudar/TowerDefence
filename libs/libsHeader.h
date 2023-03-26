#if !defined(libsHeader_h)
#define libsHeader_h

#include "..\classes\Creatures.h"
#include <Windows.h>
#include <string>
#include <tuple>
#include <vector>
#include <thread>
using namespace std;

class Map
{
private:
	int width = 0;
	int height = 0;
	int n_tick = 0;
	int score = 0;
	vector<vector<int>> path;
	vector<vector<int>> map;
	vector<std::tuple<int, int, EntityBase*>> entities;
	vector<std::tuple<int, int, TowerBase>> towers;
	vector<char> charOfMapObjects{ '.','#' };
	vector<string> colorsOfMapObjects{ "35", "95" };
public:
	Map() {};
	Map(int, int, vector<vector<int>>&, vector<vector<int>>&);//Конструктор, передаю размеры поля , само поле формата vector<vector<int>>, путь по которому идут зомбаки
	bool move(int, int, int, int);//Пока что не реализовал
	bool moveEnt(int, int, int);// Передвинет entity с id на новые x y. (id, x2, y2)
	bool moveTow(int, int, int);// Передвинет tower с id на новые x y. (id, x2, y2)
	TowerBase getTower(int, int);//По координате возвращает Башню на полe, если башни на клетке нет, вернёт дефолтный класс башни
	// EntityBase* getEntity(int, int);//По координате возвращает Существо на поле, если существа на клетке нет, вернёт дефолтный класс существа
	void generate(int); // Генерация мобов в начале пути
	EntityBase* getEntityById(int);
	pair<bool, int> tick(); //возращает bool. False - игра продолжается, True - ты лох.
	int get_tick(); //возращает номер тика.
	int getTowerId(int, int);//По координате возвращает индекс Башни на полe, если башни на клетке нет, вернёт -1
	int getEntityId(int, int);//По координате возвращает индекс Существа на поле, если существа на клетке нет, вернёт -1
	int addTower(int, int, TowerBase);//Добавляет Башню на поле в заданное место, вернёт количество свой индекс в towers
	int addEntitiy(int, int, EntityBase*);//Добавляет Существо на поле в заданное место, вернёт количество свой индекс entities
	void DedugPrintMap();//Выводит в консоль карту, сама карта - цифрами, башня - #, существо - @. ТОЛЬКО ДЛЯ ДЕБАГА, ВЫВОД В КОНСОЛЬ БУДЕТ ОСУЩЕСТВЛЯТЬСЯ С ПОМОШЬЮ КЛАССА Display
	int setStyleToElement(int, char, string&); // Меняет или добавляет (в случае, если объекта на карте с таким индексом нет) цвет и символ элемента
	std::pair<char, string> getStyleOfElement(int); // Возвращает символ и цвет элемента, если его нет, вернёт пару с пустыми строками
	string getPixel(int, int); //Вернёт строку формата "\x1B[" + selfColor + "m" + selfChar + "\033[0m" для конкретной точки на катре
	void loadStyle(); //Пока не реализованно
	int get_score() { return score; };
	std::pair<int, int> getSize(); // Вернёт Height, Width
	bool check_coord_for_tower(int, int);
};

class Display
{
private:
	int width = 0;
	int height = 0;
	int x_cur = 0;
	int y_cur = 0;
	HANDLE hConsole;
	CONSOLE_CURSOR_INFO cursor_info;
	COORD offsetMainMap;
	HWND hWnd;
public:
	Display() {};
	Display(int, int);
	void move_cur(int, int);
	void draw(Map&);
	void printInfo(vector<string>&);
	void setVisibleCursor(bool);
	pair<int, int> get_cur();
};

class MapandPath {
public:
	vector<vector<int>> path;
	vector<vector<int>> map;

};

class Game
{
private:
	vector<string> outInfo;
	vector<tuple<char, int, int, int, int>> towersInfo;
	bool alive = true;
	int selected_tower = 0;
	int money;
	int difficulty;
	int TICK_TIME;
	void game_func();
	void interface_func();
	void cursor_func();
	MapandPath create_map(int);
	Map mapSt;
	Display disp;

public:
	void start_game(int);
};



#endif // libsHeader.h
