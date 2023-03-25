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
    this->hWnd = GetConsoleWindow();
    ShowWindow(hWnd, SW_SHOWMAXIMIZED);
    GetConsoleCursorInfo(hConsole, &cursor_info);
    offsetMainMap.X = xOffset;
    offsetMainMap.Y = yOffset;
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
            outStream << map.getPixel(x,y) << " ";
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
        cout << "‾";
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