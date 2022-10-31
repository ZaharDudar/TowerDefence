#include "..\libs\Map.h"
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
    Map map1(w, h, inpMap);
    map1.DedugPrintMap();

    cout << map1.addEntitiy(1,2) << "\n";
    cout << map1.addTower(3,0) << "\n";
    cout << map1.addTower(3,1) << "\n";
    cout << map1.getIndexOfTower(3,1)<<"\n";
    cout << map1.getIndexOfEntity(3,3)<<"\n";
    map1.DedugPrintMap();

}