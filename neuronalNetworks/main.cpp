#include <cstdio>
#include <iostream>

#include "Perceptron.h"

using namespace std;

vector < vector<int> > createTrainingMatrix(){
	vector < vector<int> > container;

	vector<int> v = {0,1,1,1,0,0,1,0,1,0,0,1,0,1,0,0,1,0,1,0,0,1,1,1,0}; // 0
	vector<int> v2 = {1,0,0,0,1,0,1,0,1,0,0,0,1,0,0,0,1,0,1,0,1,0,0,0,1}; // X
	vector<int> v3 = {0,1,1,1,0,0,1,1,1,0,0,1,0,1,0,0,1,1,1,0,0,1,1,1,0}; // 0
	vector<int> v4 = {1,0,0,0,1,0,1,1,1,0,0,0,1,0,0,0,1,0,1,0,1,0,0,0,1}; // X
	vector<int> v5 = {0,0,1,0,0,0,1,0,1,0,0,1,0,1,0,0,1,0,1,0,0,0,1,0,0}; // 0
	vector<int> v6 = {1,0,0,0,1,0,1,0,1,0,0,0,1,0,0,0,1,1,1,0,1,0,0,0,1}; // X
	vector<int> v7 = {1,0,0,0,1,0,1,0,1,0,0,1,1,0,0,0,1,0,1,0,1,0,0,0,1}; // X
	vector<int> v8 = {1,0,0,0,1,0,1,0,1,0,0,0,1,1,0,0,1,0,1,0,1,0,0,0,1}; // X
	vector<int> v9 = {0,1,1,1,0,1,1,0,1,1,1,1,0,1,1,1,1,0,1,1,0,1,1,1,0}; // 0
	vector<int> v10 = {1,1,0,1,1,1,1,1,1,1,0,0,1,0,0,1,1,1,1,1,1,1,0,1,1}; // X
	vector<int> v11 = {0,1,1,1,0,1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,0,1,1,1,0}; // 0
	vector<int> v12 = {0,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,0}; // 0

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

void printSet(vector<vector<int> > &dataSet, vector<int> &results, bool hasResults){
	int dataSetSize =  dataSet.size();
	vector<int> currentVector;
	for(int i=0; i<dataSetSize; i++){
		cout << "The " << i  <<  " element " << endl;
		currentVector = dataSet[i];
		int size = currentVector.size();
		for(int j=0; j<size; j++){
			cout << currentVector[j] << " ";
			if(j>0 && (j+1)%5 == 0){
				cout << "" << endl;
			}
		}
		if(hasResults){
			cout << "This vector represents a ";
			if(results[i] == 0)
				cout << "0" << endl;
			else
				cout << "X" << endl;
		}
	}
}

int main(){
	int inputLayerSize = 25;
	int hiddenLayerSize = 13;
	int epochsRequired = 1000;
	double learningRate = 1.0;

	Perceptron *perceptron = new Perceptron(inputLayerSize, hiddenLayerSize, epochsRequired, learningRate);

	cout << "Training data set initialization..." << endl;
	vector < vector <int> > trainingMatrix = createTrainingMatrix();
	vector<int> results = {0,1,0,1,0,1,1,1,0,1,0,0}; // 0's represent a 0 in the matrix, 1 represents a X in the matrix

	printSet(trainingMatrix, results, true);

	cout << "ANN training begin..." << endl;
	perceptron->train(&trainingMatrix, &results);

	vector < vector <int> > realMatrix;
	vector<int> rv = {0,1,1,1,0,0,1,0,1,0,0,1,0,1,0,0,1,1,1,0,0,1,1,1,0}; // 0
	vector<int> rv2 = {0,1,1,1,0,1,0,0,1,1,1,0,0,1,1,1,0,0,1,1,0,1,1,1,0}; // 0
	vector<int> rv3 = {1,1,0,1,1,1,1,1,1,1,0,1,1,1,0,1,1,1,1,1,1,1,0,1,1}; // X
	vector<int> rv4 = {1,0,0,0,1,1,1,0,1,1,0,1,1,1,0,0,1,1,1,0,1,1,0,1,1}; // X

	realMatrix.push_back(rv);
	realMatrix.push_back(rv2);
	realMatrix.push_back(rv3);
	realMatrix.push_back(rv4);

	results.clear();

	cout << "Other set is goiing to be tested, and the ANN should get the results correctly" << endl;
	cout << "The real set representation:" << endl;
	printSet(realMatrix, results, false);

	cout << "Obtained results: " << endl;
	for(int i=0; i<4; i++){
		double result = perceptron->execute(&realMatrix.at(i));
		cout << "The " << i  <<  " vector result is " << result << " so it is a:";
		if(result < 0.5)
				cout << "0" << endl;
			else
				cout << "X" << endl;
	}
}