// PP_OK_GC.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "ACO.h"
#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<pair<int, int>> edges;
    edges.push_back(make_pair(0, 2));
    edges.push_back({1, 2 });
    edges.push_back({1, 2 });
    edges.push_back({1, 4 });
    edges.push_back({2, 3 });
    edges.push_back({0, 4 });
    
    ACO k(edges, 5);
    cout << k.minNumberOfColor << endl;
    for (int i = 0; i < k.minNumberOfColor; i++) {
        cout << "Kolor " << i << ": ";
        for (auto v : k.bestSubsetsOfVertices[i]) cout << v << " ";
        cout << endl;
    }
    
    cout << "Hello World!\n";
}

