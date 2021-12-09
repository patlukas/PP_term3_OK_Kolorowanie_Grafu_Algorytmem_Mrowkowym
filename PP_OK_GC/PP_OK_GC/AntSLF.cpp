#include "AntSLF.h"

AntSLF::AntSLF(vector<vector<int>> listaSasiedztwa, int numberOfVertices, vector<vector<int>> coloringQuality) {
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
	cout << verticesToColoring << " ";
	while(this->verticesWithoutColor.size() > 1) {
		//cout << "Details: " <<verticesToColoring<< endl;
		for (int indexVertice : this->verticesWithoutColor) {
			this->c_min[indexVertice] = this->getMinValColorForVertice(indexVertice);
			this->dsat[indexVertice] = this->getDsat(indexVertice);
			//cout << this->getMinValColorForVertice(indexVertice) << " " << this->getDsat(indexVertice) << endl;;
		}
		this->deleteColoredVerticeFromListVerticesWithoutColor(verticesToColoring);
		verticesToColoring = this->chooseVertice();//wybranie wierzcho³ka v 1. strategi¹
		cout << verticesToColoring << " ";
		color = this->c_min[verticesToColoring];//wybranie koloru 1. strategi¹
		this->coloringVertice(verticesToColoring, color);
		if (color == this->numberOfColors) this->numberOfColors+=1;
	}
	cout << "| " << this->numberOfColors << endl;
}

int AntSLF::chooseVertice() {
	double alfa = 2, beta = 2;
	vector<double> p(this->verticesWithoutColor.size());
	//cout << "H";
	for (int i = 0; i < this->verticesWithoutColor.size(); i++) {
		//cout << "Q" << this->verticesWithoutColor[i] << endl;
		//cout << this->chooseVertice_calculateT1(this->verticesWithoutColor[i]) << " " << this->chooseVertice_calculateN1(this->verticesWithoutColor[i]) << endl;
		p[i] = pow(this->chooseVertice_calculateT1(this->verticesWithoutColor[i]), alfa);
		p[i] *= pow(this->chooseVertice_calculateN1(this->verticesWithoutColor[i]), beta);
		float mian = 1;
		for (int j = 0; j < this->numberOfVertices; j++) {
			if (this->listSetColorVertices[i] != -1) continue;
			//cout << this->chooseVertice_calculateT1(this->verticesWithoutColor[i]) << " " << this->chooseVertice_calculateN1(this->verticesWithoutColor[i]) << endl;
			float k = pow(this->chooseVertice_calculateT1(j), alfa);
			k *= pow(this->chooseVertice_calculateN1(j), beta);
			mian += k;
		}
		//cout << "R" << p[i] << " " << mian << endl;
		p[i] /= mian;
	}
	//cout << "I" << endl;
	double s = 0;
	for (double ii : p) {
		//cout << "Y" << ii << endl;
		s += (double)ii;
	}
	//cout << s << endl;
	/*for (auto kk : this->verticesWithoutColor)

	cout << endl << endl;
	cout<<rand()<<endl;
	cout<<rand();*/
	int rr = rand() % 10000;
	double rrr = (double)rr / 10000;
	double random = rrr * s;
	//cout << "R " << random <<" "<<s<< endl;
	//cout << "Random: " << random << " " << s << endl;
	//random = (float(rand()) / float((RAND_MAX)) * s);
	//cout << "Random: " << random << " " << s << endl;
	s = 0;
	for (int ii = 0; ii < p.size(); ii++) {
		s += p[ii];
		if (s > random) {
			//cout << "return " << this->verticesWithoutColor[ii] << endl;
			return this->verticesWithoutColor[ii];
		}
	}
	return this->verticesWithoutColor[0];
}

int AntSLF::chooseVertice_calculateN1(int vertice) {
	//cout << "N1 "<<(this->dsat[vertice])<<endl;
	return this->dsat[vertice];//?
}
float AntSLF::chooseVertice_calculateT1(int vertice) {
	//cout << "T1 " << this->chooseVertice_calculateT2(vertice, this->c_min[vertice]) << endl;
	return this->chooseVertice_calculateT2(vertice, this->c_min[vertice]);
}
float AntSLF::chooseVertice_calculateT2(int vertice, int color) {
	if (this->subsetsOfVertices[color].size() == 0) return 1;
	else {
		float sum = 0;
		for (int ver : this->subsetsOfVertices[color]) {
			if (vertice < ver) sum += this->coloringQuality[vertice][ver];
			else sum += this->coloringQuality[ver][vertice];
		}
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
	//?
	this->c_min[indexVertice] = color;
}

void AntSLF::deleteColoredVerticeFromListVerticesWithoutColor(int verticeToDelete) {
	for (int j = 0; j < this->verticesWithoutColor.size(); j++) {
		if (this->verticesWithoutColor[j] == verticeToDelete) {
			this->verticesWithoutColor.erase(this->verticesWithoutColor.begin() + j);
		}
	}
}