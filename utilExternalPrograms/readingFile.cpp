#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int main(){
	const char* fileName = "trainedMatrix.txt";
	std::ifstream infile(fileName);
	string line;
	vector<double> neuronRGB;
	cout << "Start reading file" << endl;
	getline(infile,line);
	int size = atoi(line.c_str());
	cout << "Size: " << size << endl;
	getline(infile,line);
	int executedEpochs = atoi(line.c_str());
	cout << "Executed epochs: " << executedEpochs << endl;
	getline(infile,line);
	int maxExpochs = atoi(line.c_str());
	cout << "MAX Epochs" << maxExpochs << endl;
	getline(infile,line);
	double initialLearningRate = atof(line.c_str());
	cout << "Initial Learning rate: " << initialLearningRate << endl;
	getline(infile,line);
	double currentLearningRate = atof(line.c_str());
	cout << "Current Learning rate: " << currentLearningRate << endl;
	getline(infile,line);
	int totalWeights = atoi(line.c_str());
	cout << "Total Weights: " << totalWeights << endl;
	neuronRGB.resize(totalWeights);
	for(int row=0; row<size; row++){ // For every row
		getline(infile,line);
		//cout << line << endl;
		stringstream ssin(line);
		for(int col=0; col<size; col++){
			for(int weigths=0; weigths<totalWeights; weigths++){
				ssin >> neuronRGB[weigths];
			}
			cout << "Row(" << row << ") Col(" << col << "): ";
			for(int element=0; element<totalWeights; element++){
				cout << neuronRGB[element] << " ";
			}
			cout << endl;
		}
	}
	cout << "Finish rading file" << endl;
	return 0;
}

/*
0....99
0: 0 1 2 | 3 4 5 | 
*/
