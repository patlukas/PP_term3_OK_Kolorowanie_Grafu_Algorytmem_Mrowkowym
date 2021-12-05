#pragma once
#include <iostream>
#include <vector>

using namespace std;

class AntSLF {
	int numberOfVertices;
	
	vector<int> * listaSasiedztwa; 
	int * c_min; //c_min[i] - minimalny koor jaki może być przyporządkowany wierzchołkowi i
	int * dsat; //dsat[i] - storień nasycenia wierzchołka i
	vector<int> verticesWithoutColor; //zbiór wierzchołków nie pokolorowanych
	vector<int> * subsetsOfVertices; //podzbiowy wierzchołków
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

