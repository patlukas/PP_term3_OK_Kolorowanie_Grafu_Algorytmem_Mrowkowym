#pragma once
#include <iostream>
#include <vector>
#include <math.h>
#include <cstdlib>
#include <ctime>

using namespace std;

class AntSLF {
	int numberOfVertices;
	float alfa;
	float beta;
	
	vector<vector<int>> listaSasiedztwa; //lista s¹siedztwa grafu
	vector<int> c_min; //c_min[x] - minimalny kolor jaki mo¿e byæ przyporz¹dkowany wierzcho³kowi x
	vector<int> dsat; //dsat[x] - stopieñ nasycenia wierzcho³ka x
	vector<int> verticesWithoutColor; //zbiór wierzcho³ków nie pokolorowanych
	vector<vector<float>> coloringQuality; //iloœæ feromoonu
	vector<float> verticesSumColoringQuality; //tablica sum potrzebnych do wyliczenia T2
	vector<vector<bool>> listUsedColorByNeigbours;

	void arraysInicjalization(int);
	void coloringVertice(int, int);
	void deleteColoredVerticeFromListVerticesWithoutColor(int);
	int chooseVertice();
	int chooseVertice_calculateN1(int);
	float chooseVertice_calculateT1(int);
	float chooseVertice_calculateT2(int, int);
	float getSumColoringQuality(int, int);
	void updateSumColoringQuality(int, int);
	void updateCminAndDsat(int, int);

public:
	AntSLF(vector<vector<int>>, int, vector<vector<float>>, int, float, float);
	vector<int> listSetColorVertices;
	int numberOfColors; //iloœæ u¿ytych kolorów
	vector<vector<int>> subsetsOfVertices; //podzbiowy wierzcho³ków
};

