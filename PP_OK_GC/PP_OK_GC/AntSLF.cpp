#include "AntSLF.h"

AntSLF::AntSLF(vector<vector<int>> listaSasiedztwa, int numberOfVertices, vector<vector<int>> coloringQuality) {
	this->numberOfColors = 1;
	
	this->coloringQuality = coloringQuality;
	this->listaSasiedztwa = listaSasiedztwa;
	this->numberOfVertices = numberOfVertices;

	this->arraysInicjalization(numberOfVertices);

	int color = 0;
	int verticesToColoring = this->znajdzWierzcholekONajwiekszymStopniu(verticesWithoutColor);
	this->coloringVertice(verticesToColoring, color);
	while(this->verticesWithoutColor.size() > 1) {
		for (int indexVertice : this->verticesWithoutColor) {
			this->c_min[indexVertice] = this->getMinValColorForVertice(indexVertice);
			this->dsat[indexVertice] = this->getDsat(indexVertice);
		}
		this->deleteColoredVerticeFromListVerticesWithoutColor(verticesToColoring);
		verticesToColoring = this->chooseVertice();//wybranie wierzcho³ka v 1. strategi¹
		color = this->c_min[verticesToColoring];//wybranie koloru 1. strategi¹
		this->coloringVertice(verticesToColoring, color);
		if (color == this->numberOfColors) this->numberOfColors+=1;
	}
}

int AntSLF::chooseVertice() {
	
	/*
	float alfa = 1, beta = 20;
	float n, t;
	vector<int> p(this->verticesWithoutColor.size());
	cout << "H";
	for (int i = 0; i < this->verticesWithoutColor.size(); i++) {
		p[i] = pow(this->chooseVertice_calculateT1(this->verticesWithoutColor[i]), alfa);
		p[i] *= pow(this->chooseVertice_calculateN1(this->verticesWithoutColor[i]), beta);
		float mian = 0;
		for (int i = 0; i < this->listSetColorVertices.size(); i++) {
			if (this->listSetColorVertices[i] == -1) continue;
			float k = pow(this->chooseVertice_calculateT1(i), alfa);
			k *= pow(this->chooseVertice_calculateN1(i), beta);
			mian += k;
		}
		//p[i] /= mian;
	}
	cout << "I" << endl;
	for (float i : p) { cout << i << endl; }
	cout << endl << endl;*/
	return this->verticesWithoutColor[0];
}

int AntSLF::chooseVertice_calculateN1(int vertice) {
	return this->dsat[vertice];
}
float AntSLF::chooseVertice_calculateT1(int vertice) {
	return this->chooseVertice_calculateT2(vertice, this->c_min[vertice]);
}
float AntSLF::chooseVertice_calculateT2(int vertice, int color) {
	if (this->subsetsOfVertices[color].size() == 0) return 1;
	else {
		float sum = 0;
		for (int ver : this->subsetsOfVertices[color]) {
			//?
			if (vertice < ver) sum += this->coloringQuality[vertice][ver];
			else sum += this->coloringQuality[ver][vertice];
		}
		cout << "S" << sum << endl;
		return sum / this->subsetsOfVertices[color].size();
	}
	
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
	int ver = listVertices[0];
	int stopien = 0;
	for (int vertice : listVertices) {
		if (this->listaSasiedztwa[vertice].size() > stopien) {
			ver = vertice;
			stopien = this->listaSasiedztwa[vertice].size();
		}
	}
	return ver;
}

void AntSLF::arraysInicjalization(int numberOfVertices) {
	vector<int> temp(numberOfVertices);
	this->c_min = temp;
	this->dsat = temp;
	this->listSetColorVertices = temp;
	vector<vector<int>> subsetsOfVertices(numberOfVertices);
	this->subsetsOfVertices = subsetsOfVertices;
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