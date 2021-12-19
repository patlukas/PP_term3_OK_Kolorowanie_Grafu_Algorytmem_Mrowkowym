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
	vector<vector<float>> coloringQuality; //ilo�� feromoonu
	vector<float> verticesSumColoringQuality; //tablica sum potrzebnych do wyliczenia T2

	int znajdzWierzcholekONajwiekszymStopniu(vector<int>);
	void arraysInicjalization(int);
	void coloringVertice(int, int);
	void deleteColoredVerticeFromListVerticesWithoutColor(int);
	int chooseVertice();
	int chooseVertice_calculateN1(int);
	float chooseVertice_calculateT1(int);
	float chooseVertice_calculateT2(int, int);
	float getSumColoringQuality(int, int);
	void updateSumColoringQuality(int, int);
	pair<int, int> getMinColorAndDsat(int); //zwraca <minColor, Dsat>

public:
	AntSLF(vector<vector<int>>, int, vector<vector<float>>);
	vector<int> listSetColorVertices;
	int numberOfColors; //ilo�� u�ytych kolor�w
	vector<vector<int>> subsetsOfVertices; //podzbiowy wierzcho�k�w
};

