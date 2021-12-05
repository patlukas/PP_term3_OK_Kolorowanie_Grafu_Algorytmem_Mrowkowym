#pragma once
#include <iostream>
#include <vector>

using namespace std;

class AntSLF {
	int numberOfVertices;
	
	vector<int> * listaSasiedztwa; 
	int * c_min; //c_min[i] - minimalny koor jaki mo¿e byæ przyporz¹dkowany wierzcho³kowi i
	int * dsat; //dsat[i] - storieñ nasycenia wierzcho³ka i
	vector<int> verticesWithoutColor; //zbiór wierzcho³ków nie pokolorowanych
	vector<int> * subsetsOfVertices; //podzbiowy wierzcho³ków
	vector<vector<int>*> allSolutions;

	int znajdzWierzcholekONajwiekszymStopniu(vector<int>);
	void arraysInicjalization(int);
	void coloringVertice(int, int);
	void deleteColoredVerticeFromListVerticesWithoutColor(int);
	void saveSolution();
	int chooseVertice();
	int getMinValColorForVertice(int);
	int getDsat(int);

public:
	AntSLF(vector<int>*, int);
	int* listSetColorVertices;
	int numberOfColors;
};

