#include "AntSLF.h"

AntSLF::AntSLF(vector<int> * listaSasiedztwa, int numberOfVertices) {
	this->numberOfColors = 1;
	
	this->listaSasiedztwa = listaSasiedztwa;
	this->numberOfVertices = numberOfVertices;

	this->arraysInicjalization(numberOfVertices);

	int color = 0;
	int verticesToColoring = this->znajdzWierzcholekONajwiekszymStopniu(verticesWithoutColor);
	this->coloringVertice(verticesToColoring, color);
	
	for (int i = 0; i < numberOfVertices; i++) {
		for (int indexVertice : this->verticesWithoutColor) {
			this->c_min[indexVertice] = this->getMinValColorForVertice(indexVertice);
			this->dsat[indexVertice] = this->getDsat(indexVertice);
		}
		this->deleteColoredVerticeFromListVerticesWithoutColor(verticesToColoring);
		this->saveSolution();
		verticesToColoring = this->chooseVertice(); //wybranie wierzcho³ka v 1. strategi¹
		color = this->c_min[verticesToColoring]; //wybranie koloru 1. strategi¹
		this->coloringVertice(verticesToColoring, color);
		if (color == this->numberOfColors) this->numberOfColors++;
	}
}

int AntSLF::chooseVertice() {
	return this->verticesWithoutColor[0];
}

int AntSLF::getMinValColorForVertice(int indexVertice) {
	int nr = 0;
	int nr_new= 0;
	do {
		nr = nr_new;
		for (int sasiedniWierzcholek : this->listaSasiedztwa[indexVertice]) {
			if (this->listSetColorVertices[sasiedniWierzcholek] == nr_new) nr_new++;
		}
	} while (nr != nr_new);
	return nr;
}

int AntSLF::getDsat(int indexVertice) {
	int nasycenie = 0;
	for (int i = 0; i < this->numberOfVertices; i++) {
		for (int sasiedniWierzcholek : this->listaSasiedztwa[indexVertice]) {
			if (this->listSetColorVertices[sasiedniWierzcholek] == i) {
				nasycenie++;
				break;
			}
		}
	}
	return nasycenie;
}

int AntSLF::znajdzWierzcholekONajwiekszymStopniu(vector<int> listVertices) {
	return 2;
}

void AntSLF::arraysInicjalization(int numberOfVertices) {
	this->c_min = new int[numberOfVertices];
	this->dsat = new int[numberOfVertices];
	this->listSetColorVertices = new int[numberOfVertices];
	this->subsetsOfVertices = new vector<int>[numberOfVertices];

	for (int i = 0; i < numberOfVertices; i++) {
		this->c_min[i] = 0;
		this->dsat[i] = 0;
		this->listSetColorVertices[i] = -1;
		this->verticesWithoutColor.push_back(i);
	}
}

void AntSLF::coloringVertice(int indexVertice, int color) {
	this->subsetsOfVertices[color].push_back(indexVertice);
	this->listSetColorVertices[indexVertice] = color;
}
void AntSLF::deleteColoredVerticeFromListVerticesWithoutColor(int verticeToDelete) {
	for (int j = 0; j < this->verticesWithoutColor.size(); j++) {
		if (this->verticesWithoutColor[j] == verticeToDelete) {
			this->verticesWithoutColor.erase(this->verticesWithoutColor.begin() + j);
		}
	}
}
void AntSLF::saveSolution() {
	if (this->allSolutions.size() < this->numberOfColors) this->allSolutions.push_back(this->subsetsOfVertices);
	else this->allSolutions[this->numberOfColors - 1] = this->subsetsOfVertices;
}