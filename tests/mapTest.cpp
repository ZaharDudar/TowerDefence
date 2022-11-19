#include "..\libs\libsHeader.h"
#include "..\classes\Creatures.h"
#include <iostream>
#include <vector>
#include <conio.h>
/* Файл с тестом методов класса Map*/
using namespace std;

int main(){
    vector<vector<int>> inpMap{
        {1,1,1,1},
        {0,0,0,1},
        {1,0,0,0},
        {1,1,1,1}
    };
    int h = inpMap.size();
    int w = inpMap[0].size();
    Display disp(0,0);
    Map mapSt(w, h, inpMap);

    cout << mapSt.addEntitiy(1,2, testEntity('&', "34;45", 1)) << "\n"; 
    cout << mapSt.addTower(3,0, TowerBase()) << "\n";
    cout << mapSt.addTower(3,1, TowerBase()) << "\n";
    cout << mapSt.getTower(3,1).getType()<<"\n";
    cout << mapSt.getEntity(3,3).getType()<<"\n";
    while (true)
    {
        disp.draw(mapSt);
        getch();
        mapSt.moveEnt(0,2,2);
    }
    

}