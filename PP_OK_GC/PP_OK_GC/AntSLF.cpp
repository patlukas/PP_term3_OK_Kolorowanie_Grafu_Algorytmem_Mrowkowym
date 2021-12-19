#include "AntSLF.h"

AntSLF::AntSLF(vector<vector<int>> listaSasiedztwa, int numberOfVertices, vector<vector<float>> coloringQuality) {
	//rand();
	//srand((unsigned int)time(NULL));
	/*
	double s = 0;
	double rrr;
	double rrrLast = -1;
	for (int i = 0; i < 10000000; i++) {
		int rr = rand() % 1000;
		
		rrr = (double)rr / 1000;
		if (rrr == rrrLast) cout << i<<" "<<rrr << endl;
		s += rrr;
		rrrLast = rrr;
	}
	cout << s << " " << rrr << endl;*/
	this->numberOfColors = 1;
	
	this->coloringQuality = coloringQuality;
	this->listaSasiedztwa = listaSasiedztwa;
	this->numberOfVertices = numberOfVertices;

	this->arraysInicjalization(numberOfVertices);

	int color = 0;
	int verticesToColoring = this->znajdzWierzcholekONajwiekszymStopniu(verticesWithoutColor);
	this->coloringVertice(verticesToColoring, color);
	//cout << verticesToColoring << " ";
	while(this->verticesWithoutColor.size() > 1) {
		for (int indexVertice : this->verticesWithoutColor) {
			if (indexVertice == verticesToColoring) continue;
			if (find(this->listaSasiedztwa[indexVertice].begin(), this->listaSasiedztwa[indexVertice].end(), verticesToColoring) != this->listaSasiedztwa[indexVertice].end()) {
				pair<int, int> minColorAndDsat = this->getMinColorAndDsat(indexVertice);
				if (minColorAndDsat.first != this->c_min[indexVertice]) {
					this->c_min[indexVertice] = minColorAndDsat.first;
					this->verticesSumColoringQuality[indexVertice] = this->getSumColoringQuality(indexVertice, minColorAndDsat.first);
				}
				this->dsat[indexVertice] = minColorAndDsat.second;
			}
		}
		this->deleteColoredVerticeFromListVerticesWithoutColor(verticesToColoring);
		this->updateSumColoringQuality(verticesToColoring, color);
		verticesToColoring = this->chooseVertice();//wybranie wierzcho³ka v 1. strategi¹
		//cout << verticesToColoring << " ";
		color = this->c_min[verticesToColoring];//wybranie koloru 1. strategi¹
		this->coloringVertice(verticesToColoring, color);
		if (color == this->numberOfColors) this->numberOfColors+=1;
	}
	//cout << "| " << this->numberOfColors << endl;
}

int AntSLF::chooseVertice() {
	float alfa = 2, beta = 1 ;
	vector<float> p(this->verticesWithoutColor.size());
	float mianownik = 0;
	
	for (int i = 0; i < this->verticesWithoutColor.size(); i++) {
		p[i] = pow(this->chooseVertice_calculateT1(this->verticesWithoutColor[i]), alfa);
		p[i] *= pow(this->chooseVertice_calculateN1(this->verticesWithoutColor[i]), beta);
		mianownik += p[i];
	}
	for (int i = 0; i < this->verticesWithoutColor.size(); i++) p[i] /= mianownik;
	float random = (rand() % 10000);// / 10000;
	random /= 10000;
	//cout << "\t\t\t\t\t\t\t\t" << random<< endl;
	float sum = 0;
	for (int i = 0; i < p.size(); i++) {
		sum += p[i];
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
			if (vertice > verticeWithoutColor) 
				quality = this->coloringQuality[verticeWithoutColor][vertice];
			else quality = this->coloringQuality[vertice][verticeWithoutColor];
			verticesSumColoringQuality[verticeWithoutColor] += quality;
		}
	}
}

float AntSLF::chooseVertice_calculateT2(int vertice, int color) {
	if (this->subsetsOfVertices[color].size() == 0) return 1;
	else return this->verticesSumColoringQuality[vertice] / this->subsetsOfVertices[color].size();
}

pair<int, int> AntSLF::getMinColorAndDsat(int indexVertice) {
	int minColor = this->numberOfColors, Dsat=0;
	vector<bool> neighborsUsedColors(this->numberOfColors);
	for (int sasiedniWierzcholek : this->listaSasiedztwa[indexVertice]) {
		int color = listSetColorVertices[sasiedniWierzcholek];
		if (color > -1) neighborsUsedColors[color] = true;
	}
	for (int i = 0; i < neighborsUsedColors.size(); i++) {
		if (!neighborsUsedColors[i] && minColor == this->numberOfColors) minColor = i;
		else Dsat++;
	}
	return make_pair(minColor, Dsat);
}

int AntSLF::znajdzWierzcholekONajwiekszymStopniu(vector<int> listVertices) {
	// *DO* Do optymalizacji mo¿na wysy³¹æ z ACO.cpp wierzcho³ek od ktorego trzeba rozpocz¹æ
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
	vector<float> verticesSumColoringQuality(numberOfVertices);
	this->verticesSumColoringQuality = verticesSumColoringQuality;
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
	//?
	this->c_min[indexVertice] = color;
}

void AntSLF::deleteColoredVerticeFromListVerticesWithoutColor(int verticeToDelete) {
	for (int j = 0; j < this->verticesWithoutColor.size(); j++) {
		if (this->verticesWithoutColor[j] == verticeToDelete) {
			this->verticesWithoutColor.erase(this->verticesWithoutColor.begin() + j);
			return;
		}
	}
}