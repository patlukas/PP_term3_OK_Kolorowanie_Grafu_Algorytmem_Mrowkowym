#include "ACO.h"
void runAnt() {
	cout << "POLSKA";
}
ACO::ACO(vector<pair<int, int>> edges, int numberOfVertices) {
	
	this->wyparowywanie = 0.5;
	this->minNumberOfColor = numberOfVertices;
	this->numberOfCycle = 250;
	this->numberOfAnt = 20;
	vector<vector<int>> bestSubsetsOfVertices(numberOfVertices);
	this->bestSubsetsOfVertices = bestSubsetsOfVertices;

	this->edges = edges;

	this->numberOfVertices = numberOfVertices;

	this->createListaSasiedztwa();

	this->createListaNieSasiedztwa();
	this->inicjalizationArrayQuality(numberOfVertices);

	this->setQualityNieSasiadow(); 
	for (int cycle = 0; cycle < this->numberOfCycle; cycle++) {
		cout <<"Cykl "<< cycle << endl;
		this->setQualityDeltaNieSasiadow();
		int i = 0;
		float kkk = 0;

		for (int ant = 0; ant < this->numberOfAnt; ant++) {	
			//cout << "\tAnt " << ant << endl;
			//clock_t s = clock();
			AntSLF slf(this->listaSasiedztwa, this->numberOfVertices, this->coloringQuality);
			kkk += slf.numberOfColors;
			//cout << "\t\tKolorow " << slf.numberOfColors <<" Czas: "<< ((clock() - s) / (double)CLOCKS_PER_SEC) << endl;
			if (slf.numberOfColors < this->minNumberOfColor) {
				cout << "\t\t\tREKORD " << slf.numberOfColors<<endl;
				this->bestSubsetsOfVertices = slf.subsetsOfVertices;
				this->minNumberOfColor = slf.numberOfColors;
			}
			for (int i = 0; i < this->numberOfVertices; i++) {
				int j;
				for (j = 0; j < this->numberOfVertices; j++) {
					bool inSubsets = false;
					for (auto vertice : slf.subsetsOfVertices[j]) {
						if (vertice == i) {
							inSubsets = true;
							break;
						}
					}
					if (inSubsets) break;
				}
				for (auto nieSasiad : this->listaNieSasiedztwa[i]) {
					if (i > nieSasiad) continue;
					for (auto vertice : slf.subsetsOfVertices[j]) {
						if (vertice == nieSasiad) this->coloringQualityDelta[i][nieSasiad] += (1 / (float)slf.numberOfColors);
					}
				}
			}
		}
		cout << "\t" << kkk / numberOfAnt << endl;
		for (int i = 0; i < this->numberOfVertices; i++) {
			for (auto vertice : this->listaNieSasiedztwa[i]) {
				if (vertice > i)
					this->coloringQuality[i][vertice] = this->wyparowywanie * this->coloringQuality[i][vertice] + this->coloringQualityDelta[i][vertice];
				//cout << this->coloringQuality[i][vertice] << " ";
			}
			//cout << endl;
		}
	}
}

void ACO::runAnt(vector<vector<int>> listaSasiedztwa, int numberOfVertices, vector<vector<float>> coloringQuality) {

}

void ACO::inicjalizationArrayQuality(int numberOfVertices) {
	for (int i = 0; i < numberOfVertices; i++) {
		vector<float> temp(numberOfVertices);
		this->coloringQuality.push_back(temp);
		this->coloringQualityDelta.push_back(temp);
	}
}

void ACO::createListaSasiedztwa() {
	vector<vector<int>> listaSasiedztwa(this->numberOfVertices);
	this->listaSasiedztwa = listaSasiedztwa;
	for (auto edge : this->edges) {
		this->listaSasiedztwa[edge.first].push_back(edge.second);
		this->listaSasiedztwa[edge.second].push_back(edge.first);
	}
}

void ACO::createListaNieSasiedztwa() {
	vector<vector<int>> listaNieSasiedztwa(this->numberOfVertices);
	this->listaNieSasiedztwa = listaNieSasiedztwa;
	for (int i = 0; i < this->numberOfVertices; i++) {
		for (int j = 0; j < this->numberOfVertices; j++) {
			if (i >= j) continue;
			bool isSasiad = false;
			for (auto sasiad : this->listaSasiedztwa[i]) {
				if (sasiad == j) {
					isSasiad = true;
					break;
				}
			}
			if (!isSasiad) this->listaNieSasiedztwa[i].push_back(j);
		}
	}
}

void ACO::setQualityNieSasiadow() {
	for (int i = 0; i < this->numberOfVertices; i++)
		for (int nieSasiad : this->listaNieSasiedztwa[i])
			this->coloringQuality[i][nieSasiad] = 1;
}

void ACO::setQualityDeltaNieSasiadow() {
	for (int i = 0; i < this->numberOfVertices; i++)
		for (auto nieSasiad : this->listaNieSasiedztwa[i])
			this->coloringQualityDelta[i][nieSasiad] = 0;
}