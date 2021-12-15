#pragma once
#include <iostream>
#include <vector>
#include <math.h>
#include <cstdlib>
#include <ctime>

using namespace std;

class AntSLF {
	int numberOfVertices;
	
	vector<vector<int>> listaSasiedztwa; //lista s�siedztwa grafu
	vector<int> c_min; //c_min[x] - minimalny kolor jaki mo�e by� przyporz�dkowany wierzcho�kowi x
	vector<int> dsat; //dsat[x] - stopie� nasycenia wierzcho�ka x
	vector<int> verticesWithoutColor; //zbi�r wierzcho�k�w nie pokolorowanych
	vector<vector<int>> coloringQuality; //ilo�� feromoonu

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
	int numberOfColors; //ilo�� u�ytych kolor�w
	vector<vector<int>> subsetsOfVertices; //podzbiowy wierzcho�k�w
};

