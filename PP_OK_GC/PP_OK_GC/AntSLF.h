#pragma once
#include <iostream>
#include <vector>
#include <math.h>
#include <cstdlib>
#include <ctime>

using namespace std;

class AntSLF {
	int numberOfVertices;
	
	vector<vector<int>> listaSasiedztwa; //lista s¹siedztwa grafu
	vector<int> c_min; //c_min[x] - minimalny kolor jaki mo¿e byæ przyporz¹dkowany wierzcho³kowi x
	vector<int> dsat; //dsat[x] - stopieñ nasycenia wierzcho³ka x
	vector<int> verticesWithoutColor; //zbiór wierzcho³ków nie pokolorowanych
	vector<vector<int>> coloringQuality; //iloœæ feromoonu

	int znajdzWierzcholekONajwiekszymStopniu(vector<int>);
	void arraysInicjalization(int);
	void coloringVertice(int, int);
	void deleteColoredVerticeFromListVerticesWithoutColor(int);
	int chooseVertice();
	int getMinValColorForVertice(int);
	int getDsat(int);
	int chooseVertice_calculateN1(int);
	float chooseVertice_calculateT1(int);
	float chooseVertice_calculateT2(int, int);

public:
	AntSLF(vector<vector<int>>, int, vector<vector<int>>);
	vector<int> listSetColorVertices;
	int numberOfColors; //iloœæ u¿ytych kolorów
	vector<vector<int>> subsetsOfVertices; //podzbiowy wierzcho³ków
};

