// PP_OK_GC.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "ACO.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include <math.h>

using namespace std;

pair<vector<pair<int, int>>, int> getData() {
    int numberOfVertice;
    fstream file;
    file.open("gc500.txt", ios::in); 
    string k;
    getline(file, k);
    numberOfVertice = stoi(k);
    
    vector<pair<int, int>> v;
    while (getline(file, k)) {
        int l1 = stoi(k.substr(0, k.find(" ")))-1, l2 = stoi(k.substr(k.find(" ") + 1))-1;
        if(l1 < l2) v.push_back(make_pair(l1, l2));
    }
    return make_pair(v, numberOfVertice);
}

int main() {
    srand(time(NULL));
    //srand(100);

    pair<vector<pair<int, int>>, int> r = getData();
    vector<pair<int, int>> edges = r.first;
    int numverOfVertive = r.second;
    /*fstream file;
    //file.open("result_gc500_4.txt", ios::out);

    /*for (int i = 0; i < 50; i++) {
        ACO k(edges, numverOfVertive, 0.4, 250, 25, 5000, 5 * 60 * 1000, 1, 1);
        file << i << ";" << k.minNumberOfColor << endl;
        cout <<i<<" " << k.minNumberOfColor << endl;
    }*/

    ACO k(edges, numverOfVertive, 0.4, 250, 25, 5000, 5 * 60 * 1000, 2.25, 1);
    
    cout << k.minNumberOfColor << endl;
    
    for (int i = 0; i < k.minNumberOfColor; i++) {
        cout << "Kolor " << i << ": ";
        for (auto v : k.bestSubsetsOfVertices[i]) cout << v << " ";
        cout << endl;
    }
    
    cout << "Hello World!\n";
}
