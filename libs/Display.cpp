#include <iostream>
#include <sstream>
#include "../mainHeader.h"
#include <Windows.h>
#include <string.h>




Display::Display(int width, int height, int xOffset = 0, int yOffset = 0)
{
    this->width = width;
    this->height = height;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleCursorInfo(hConsole, &cursor_info);
    cursor_info.bVisible = false;
    SetConsoleCursorInfo(hConsole, &cursor_info);
    offsetMainMap.X = xOffset;
    offsetMainMap.Y = yOffset;
}   

void Display::draw(Map& map)
{
    SetConsoleCursorPosition(hConsole, offsetMainMap);
    std::ostringstream outStream;
    for(int y = 0; y < height; y++){
        for (int x = 0; x < width; x++)
        {
            outStream << map.getPixel(x,y)<<" ";
        }
        outStream << "\n";
    }
    std::string string = outStream.str();
    std::cout << string;
}
