#pragma once
#include <iostream>
#include <vector>

using namespace std;

class AntSLF {
	int numberOfVertices;
	
	vector<int> * listaSasiedztwa; 
	int * c_min; //c_min[i] - minimalny koor jaki mo�e by� przyporz�dkowany wierzcho�kowi i
	int * dsat; //dsat[i] - storie� nasycenia wierzcho�ka i
	vector<int> verticesWithoutColor; //zbi�r wierzcho�k�w nie pokolorowanych
	vector<int> * subsetsOfVertices; //podzbiowy wierzcho�k�w
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

