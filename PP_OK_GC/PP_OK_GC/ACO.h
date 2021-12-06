#pragma once
#include <iostream>
#include <vector>
#include "AntSLF.h"

using namespace std;

class ACO{
	int wyparowywanie;
	int numberOfVertices;
	int numberOfCycle;
	int numberOfAnt;
	vector<vector<int>> coloringQuality;
	vector<vector<int>> coloringQualityDelta;
	vector<vector<int>> listaSasiedztwa;
	vector<vector<int>> listaNieSasiedztwa;
	vector<pair<int, int>> edges;

	void inicjalizationArrayQuality(int);
	void createListaSasiedztwa();
	void createListaNieSasiedztwa();
	void setQualityNieSasiadow();
	void setQualityDeltaNieSasiadow();
	
public:
	ACO(vector<pair<int, int>>, int);
	int minNumberOfColor;
	vector<vector<int>> bestSubsetsOfVertices;
};

