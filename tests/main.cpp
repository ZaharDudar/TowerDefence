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
    SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE),CONSOLE_FULLSCREEN_MODE,0);
    
    system("cls");
    Game game;
    game.start_game(0);
    
   
    cout << "GAME OVER";
    
}
