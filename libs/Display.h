#include <iostream>
#include "Map.h"
#include <Windows.h>
#include <string.h>


class Display
{
    private:
        int width = 0;
        int height = 0;
        HANDLE hConsole;
        CONSOLE_CURSOR_INFO cursor_info;
        COORD offsetMainMap;        
    public:
        Display(int, int);
        void draw(Map& map);
};

Display::Display(int width, int height, int xOffset = 0, int yOffset = 0)
{
    this->width = width;
    this->height = height;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleCursorInfo(hConsole, &cursor_info);
    cursor_info.bVisible = false;
    SetConsoleCursorInfo(hConsole, &cursor_info);
    offsetMainMap.x = xOffset;
    offsetMainMap.y = yOffset;
}   

Display::draw()
{
    std::ostringstream stream;
}
