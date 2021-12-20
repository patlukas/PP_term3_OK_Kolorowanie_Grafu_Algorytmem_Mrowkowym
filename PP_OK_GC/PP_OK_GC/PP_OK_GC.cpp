// PP_OK_GC.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "ACO.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;

pair<vector<pair<int, int>>, int> getData() {
    int numberOfVertice;
    fstream file;
   // file.open("gc500.txt", ios::in); 
    file.open("gc1000_300013.txt", ios::in); 
    string k;
    getline(file, k);
    numberOfVertice = stoi(k);
    
    vector<pair<int, int>> v;
    while (getline(file, k)) {
        //cout << "L " << k << endl;
        int l1 = stoi(k.substr(0, k.find(" ")))-1, l2 = stoi(k.substr(k.find(" ") + 1))-1;
        if(l1 < l2) v.push_back(make_pair(l1, l2));
    }
    return make_pair(v, numberOfVertice);
}


int main() {
    //srand(time(NULL));
    srand(100);
    //srand((unsigned int)time(NULL));

    pair<vector<pair<int, int>>, int> r = getData();
    //cout << r.second << endl;
    //for (auto pp : r.first) cout <<"L " << pp.first << " " << pp.second << endl;
    vector<pair<int, int>> edges = r.first;
  //  edges.push_back(make_pair(1, 2));
    int numverOfVertive = r.second;
    ACO k(edges, numverOfVertive);
    cout << k.minNumberOfColor << endl;
    for (int i = 0; i < k.minNumberOfColor; i++) {
        cout << "Kolor " << i << ": ";
        for (auto v : k.bestSubsetsOfVertices[i]) cout << v << " ";
        cout << endl;
    }
    
    cout << "Hello World!\n";
}
