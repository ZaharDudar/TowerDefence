#include <iostream>
#include <sstream>
#include ".\libsHeader.h"
#include <Windows.h>
#include <string.h>




Display::Display(int xOffset = 0, int yOffset = 0)
{
    // system("chcp 850");
    system("cls");
    this->hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleCursorInfo(hConsole, &cursor_info);
    cursor_info.bVisible = false;
    SetConsoleCursorInfo(hConsole, &cursor_info);
    offsetMainMap.X = xOffset;
    offsetMainMap.Y = yOffset;
}   

void Display::draw(Map& map)
{
    std::pair<int, int> size = map.getSize();
    this->height = get<0>(size);
    this->width = get<1>(size);
    SetConsoleCursorPosition(hConsole, COORD {0,0});
    std::ostringstream outStream;
    for(int y = 0; y < height; y++){
        for (int x = 0; x < width; x++)
        {
            outStream << map.getPixel(x,y) << " ";
        }
        outStream << "\n";
    }
    std::string string = outStream.str();
    std::cout << string;
}
