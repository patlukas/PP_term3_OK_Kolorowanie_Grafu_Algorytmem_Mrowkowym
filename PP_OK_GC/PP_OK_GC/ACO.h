#pragma once
#include <iostream>
#include <vector>
#include <ctime>
#include <Windows.h>

#include "AntSLF.h"

using namespace std;

class ACO{
	int wyparowywanie;
	int numberOfVertices;
	int numberOfCycle;
	int numberOfAnt;
	vector<vector<float>> coloringQuality;
	vector<vector<float>> coloringQualityDelta;
	vector<vector<int>> listaSasiedztwa;
	vector<vector<int>> listaNieSasiedztwa;
	vector<pair<int, int>> edges;

	void inicjalizationArrayQuality(int);
	void createListaSasiedztwa();
	void createListaNieSasiedztwa();
	void setQualityNieSasiadow();
	void setQualityDeltaNieSasiadow();
	void runAnt(vector<vector<int>>, int, vector<vector<float>>);
	
public:
	ACO(vector<pair<int, int>>, int);
	int minNumberOfColor;
	vector<vector<int>> bestSubsetsOfVertices;
};

