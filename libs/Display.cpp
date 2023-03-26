#include <iostream>
#include <sstream>
#include ".\libsHeader.h"
#include <Windows.h>
#include <string.h>
#include <utility>
#include <functional>



Display::Display(int xOffset = 0, int yOffset = 0)
{
    // system("chcp 850");
    system("cls");
    this->hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    this->hWnd = GetConsoleWindow();
    ShowWindow(hWnd, SW_SHOWMAXIMIZED);
    GetConsoleCursorInfo(hConsole, &cursor_info);
    offsetMainMap.X = xOffset;
    offsetMainMap.Y = yOffset;
}   


void Display::move_cur(int x, int y) {
    int new_x = x_cur + x;
    int new_y = y_cur + y;

    if ((new_x >= 0 && new_y >= 0 && new_x < width && new_y <  height)) {
        x_cur = new_x;
        y_cur = new_y;
    }
}


pair<int,int> Display::get_cur() {
    pair<int, int> a;
    
    return std::make_pair(x_cur, y_cur);
}


void Display::draw(Map& map)
{
    std::pair<int, int> size = map.getSize();
    this->height = get<0>(size);
    this->width = get<1>(size);
    SetConsoleCursorPosition(hConsole, COORD {0,0});
    SetConsoleCursorInfo(hConsole, &cursor_info);
    std::ostringstream outStream;
    for(int y = 0; y < height; y++){
        for (int x = 0; x < width; x++)
        {
            if ((x == x_cur) && (y == y_cur)){
                outStream << "\033[102m" << map.getPixel(x, y) << "\033[0m" << " ";
            }
            else {
                outStream << map.getPixel(x, y) << " ";
            }
            /*outStream << map.getPixel(x, y) << " ";*/
        }
        outStream << "\n";
    }
    std::string string = outStream.str();
    std::cout << string;
}
void Display::printInfo(vector<string>& info)
{
    SetConsoleCursorPosition(hConsole, COORD {(short)(this->width*2),0});
    int maxLenght = 0;
    for(int i = 0; i < info.size(); i++){
        if (maxLenght < info[i].length()){
            maxLenght = info[i].length();
        }
    }
    std::ostringstream outStream;
    cout << " ";
    for (int i = 0; i < maxLenght+2; i++)
    {
        cout << "_";
    }

    for(int y = 0; y < info.size(); y++){
        SetConsoleCursorPosition(hConsole, COORD {(short)(this->width*2),(short)(y+1)});
        cout << "| " << info[y];
        int lenght = (maxLenght - info[y].size());
        if(lenght > 0)
        {
            for(int space = 0; space < lenght; space++)
            {
                cout << " ";
            }
        }
        cout << " |";
    }
    SetConsoleCursorPosition(hConsole, COORD {(short)(this->width*2),(short)(info.size()+1)});
    cout << " ";
    for (int i = 0; i < maxLenght+2; i++)
    {
        cout << "_";
    }

    /*  ⌜‾⌝
        |  |
        ⌞_⌟
        __
       |  |
       |  |
        ‾‾⌟
    */
}
void Display::setVisibleCursor(bool isVisible){
    cursor_info.bVisible = isVisible;
}