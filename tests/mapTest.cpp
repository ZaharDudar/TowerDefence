#include "../mainHeader.h"
#include <iostream>
#include <vector>
/* Файл с тестом методов класса Map*/
using namespace std;

int main(){
    vector<vector<int>> inpMap = {
        {1,1,1,1},
        {0,0,0,1},
        {1,0,0,0},
        {1,1,1,1}
    };
    int w = inpMap.size();
    int h = inpMap[0].size();
    Display disp(4,4,1,1);
    Map mapSt(w, h, inpMap);
    mapSt.DedugPrintMap();

    cout << mapSt.addEntitiy(1,2, EntityBase()) << "\n";
    cout << mapSt.addTower(3,0, TowerBase()) << "\n";
    cout << mapSt.addTower(3,1, TowerBase()) << "\n";
    cout << mapSt.getTower(3,1).getType()<<"\n";
    cout << mapSt.getEntity(3,3).getType()<<"\n";
    mapSt.DedugPrintMap();
    disp.draw(mapSt);


}