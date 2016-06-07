#include <cstdio>
#include <iostream>

#include "Perceptron.h"

using namespace std;

vector < vector<int> > createTrainingMatrix(){
	vector < vector<int> > container;

	vector<int> v = {0,1,1,1,0,0,1,0,1,0,0,1,0,1,0,0,1,0,1,0,0,1,1,1,0};
	vector<int> v2 = {1,0,0,0,1,0,1,0,1,0,0,0,1,0,0,0,1,0,1,0,1,0,0,0,1};
	vector<int> v3 = {0,1,1,1,0,0,1,1,1,0,0,1,0,1,0,0,1,1,1,0,0,1,1,1,0};
	vector<int> v4 = {1,0,0,0,1,0,1,1,1,0,0,0,1,0,0,0,1,0,1,0,1,0,0,0,1};
	vector<int> v5 = {0,0,1,0,0,0,1,0,1,0,0,1,0,1,0,0,1,0,1,0,0,0,1,0,0};
	vector<int> v6 = {1,0,0,0,1,0,1,0,1,0,0,0,1,0,0,0,1,1,1,0,1,0,0,0,1};
	vector<int> v7 = {1,0,0,0,1,0,1,0,1,0,0,1,1,0,0,0,1,0,1,0,1,0,0,0,1};
	vector<int> v8 = {1,0,0,0,1,0,1,0,1,0,0,0,1,1,0,0,1,0,1,0,1,0,0,0,1};
	vector<int> v9 = {0,1,1,1,0,1,1,0,1,1,1,1,0,1,1,1,1,0,1,1,0,1,1,1,0};
	vector<int> v10 = {1,1,0,1,1,1,1,1,1,1,0,0,1,0,0,1,1,1,1,1,1,1,0,1,1};
	vector<int> v11 = {0,1,1,1,0,1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,0,1,1,1,0};
	vector<int> v12 = {0,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,0};

	container.push_back(v);
	container.push_back(v2);
	container.push_back(v3);
	container.push_back(v4);
	container.push_back(v5);
	container.push_back(v6);
	container.push_back(v7);
	container.push_back(v8);
	container.push_back(v9);
	container.push_back(v10);
	container.push_back(v11);
	container.push_back(v12);

	return container;
}

int main(){
	int inputLayerSize = 25;
	int hiddenLayerSize = 13;
	int epcohsRequired = 1000;
	double learningRate = 1.0;

	Perceptron *perceptron = new Perceptron(inputLayerSize, hiddenLayerSize, epcohsRequired, learningRate);
	vector < vector <int> > trainingMatrix = createTrainingMatrix();
	vector<int> results = {0,1,0,1,0,1,1,1,0,1,0,0};
	printf("Inicia entrenamiento de red neuronal\n");
	perceptron->train(&trainingMatrix, &results);
	printf("Termina entrenamiento de red neuronal\n");

	vector < vector <int> > realMatrix;
	vector<int> rv = {0,1,1,1,0,0,1,0,1,0,0,1,0,1,0,0,1,1,1,0,0,1,1,1,0}; //0
	vector<int> rv2 = {0,1,1,1,0,1,0,0,1,1,1,0,0,1,1,1,0,0,1,1,0,1,1,1,0}; //0
	vector<int> rv3 = {1,1,0,1,1,1,1,1,1,1,0,1,1,1,0,1,1,1,1,1,1,1,0,1,1}; //X
	vector<int> rv4 = {1,0,0,0,1,1,1,0,1,1,0,1,1,1,0,0,1,1,1,0,1,1,0,1,1}; //X

	realMatrix.push_back(rv);
	realMatrix.push_back(rv2);
	realMatrix.push_back(rv3);
	realMatrix.push_back(rv4);

	printf("Resultados obtenidos con una red entrenada previamente\n");
	for(int i=0; i<4; i++){
		double result = perceptron->execute(&realMatrix.at(i));
		cout << result << endl;
	}
}