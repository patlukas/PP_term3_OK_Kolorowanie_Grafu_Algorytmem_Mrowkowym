#include "AntSLF.h"

AntSLF::AntSLF(vector<vector<int>> listaSasiedztwa, int numberOfVertices, vector<vector<float>> coloringQuality) {
	this->numberOfColors = 1;
	
	this->coloringQuality = coloringQuality;
	this->listaSasiedztwa = listaSasiedztwa;
	this->numberOfVertices = numberOfVertices;

	this->arraysInicjalization(numberOfVertices);

	int color = 0;
	int verticesToColoring = this->znajdzWierzcholekONajwiekszymStopniu();
	this->coloringVertice(verticesToColoring, color);
	while(this->verticesWithoutColor.size() > 1) {
		this->updateCminAndDsat(verticesToColoring, color);
		this->deleteColoredVerticeFromListVerticesWithoutColor(verticesToColoring);
		this->updateSumColoringQuality(verticesToColoring, color);
		verticesToColoring = this->chooseVertice();//wybranie wierzcho³ka v 1. strategi¹
		color = this->c_min[verticesToColoring];//wybranie koloru 1. strategi¹
		this->coloringVertice(verticesToColoring, color);
		if (color == this->numberOfColors) this->numberOfColors += 1;
	}
}

int AntSLF::chooseVertice() {
	float alfa = 4, beta = 1 ;
	vector<float> p(this->verticesWithoutColor.size());
	float mianownik = 0;
	
	for (int i = 0; i < this->verticesWithoutColor.size(); i++) {
		p[i] = pow(this->chooseVertice_calculateT1(this->verticesWithoutColor[i]), alfa);
		p[i] *= pow(this->chooseVertice_calculateN1(this->verticesWithoutColor[i]), beta);
		mianownik += p[i];
	}
	float random = (rand() % 10000);
	random /= 10000;
	float sum = 0;
	for (int i = 0; i < p.size(); i++) {
		sum += p[i] / mianownik;
		if (sum >= random) return this->verticesWithoutColor[i];
	}
	return this->verticesWithoutColor[0];
}

int AntSLF::chooseVertice_calculateN1(int vertice) {
	return this->dsat[vertice];
}

float AntSLF::chooseVertice_calculateT1(int vertice) {
	return this->chooseVertice_calculateT2(vertice, this->c_min[vertice]);
}

float AntSLF::getSumColoringQuality(int vertice, int color) {
	float sum = 0;
	for (int ver : this->subsetsOfVertices[color]) {
		if (vertice < ver) sum += this->coloringQuality[vertice][ver];
		else sum += this->coloringQuality[ver][vertice];
	}
	return sum;
}

void AntSLF::updateSumColoringQuality(int vertice, int color) {
	for (int verticeWithoutColor : this->verticesWithoutColor) {
		if (c_min[verticeWithoutColor] == color) {
			int quality;
			if (vertice > verticeWithoutColor) quality = this->coloringQuality[verticeWithoutColor][vertice];
			else quality = this->coloringQuality[vertice][verticeWithoutColor];
			verticesSumColoringQuality[verticeWithoutColor] += quality;
		}
	}
}

void AntSLF::updateCminAndDsat(int verticeToColoring, int color) {
	for (int indexVertice : this->listaSasiedztwa[verticeToColoring]) {
		if (listSetColorVertices[indexVertice] != -1) continue; // czy wierzcho³ek jest ju¿ pokolorowany
		if (this->listUsedColorByNeigbours[indexVertice][color]) continue; // czy ten kolor jest ju¿ u¿yty przez s¹siada wierzcho³ka, je¿eli tak to nie zmieni siê c_min i dsat
		this->listUsedColorByNeigbours[indexVertice][color] = true;
		this->dsat[indexVertice] += 1;
		if (this->c_min[indexVertice] == color) { //czy kolor u¿yty w s¹siednim wierzcho³ku by³ minimalny dla tego wierzcho³ka
			for (int i = 0; i < this->listUsedColorByNeigbours[indexVertice].size(); i++) { //szukanie nowego c_min
				if (this->listUsedColorByNeigbours[indexVertice][i] == false) {
					this->c_min[indexVertice] = i;
					this->verticesSumColoringQuality[indexVertice] = this->getSumColoringQuality(indexVertice, i);
					break;
				}
			}
		}
	}
}

float AntSLF::chooseVertice_calculateT2(int vertice, int color) {
	if (this->subsetsOfVertices[color].size() == 0) return 1;
	else return this->verticesSumColoringQuality[vertice] / this->subsetsOfVertices[color].size();
}

int AntSLF::znajdzWierzcholekONajwiekszymStopniu() {
	// *DO* Do optymalizacji mo¿na wysy³¹æ z ACO.cpp wierzcho³ek od ktorego trzeba rozpocz¹æ
	int ver = this->verticesWithoutColor[0];
	int stopien = 0;
	for (int vertice : this->verticesWithoutColor) {
		if (this->listaSasiedztwa[vertice].size() > stopien) {
			ver = vertice;
			stopien = this->listaSasiedztwa[vertice].size();
		}
	}
	return ver;
}

void AntSLF::arraysInicjalization(int numberOfVertices) {
	vector<bool> tempBool(numberOfVertices);
	vector<int> tempInt(numberOfVertices);
	vector<float> tempFloat(numberOfVertices);
	vector<vector<int>> tempVectorInt(numberOfVertices);
	
	this->c_min = tempInt;
	this->dsat = tempInt;
	this->listSetColorVertices = tempInt;
	this->verticesSumColoringQuality = tempFloat;
	this->subsetsOfVertices = tempVectorInt;

	for (int i = 0; i < numberOfVertices; i++) {
		this->listSetColorVertices[i] = -1;
		this->verticesWithoutColor.push_back(i);
		this->listUsedColorByNeigbours.push_back(tempBool);
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
			return;
		}
	}
}