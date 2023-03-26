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

    cout << "Select difficulty:\n";
    int diff;
    cin >> diff;
    
    system("cls");
    Game game;
    game.start_game(diff);
    
   
    cout << "GAME OVER";
    
}
