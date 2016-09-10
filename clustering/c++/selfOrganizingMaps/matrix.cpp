#include "matrix.h"

Matrix::Matrix(int size, int totalWeights) : _size(size),
	_totalWeights(totalWeights), _totalNeurons(size * size){
	initializeMatrix();
}

Matrix::~Matrix(){
	for(int row=0; row < _size; row++){
		for(int col=0; col < _size; col++){
			delete _matrix[row][col];
		}
	}	
}

int Matrix::getSize(){
	return _size;
}

int Matrix::getTotalNeurons(){
	return _totalNeurons;
}

int Matrix::getTotalWeights(){
	return _totalWeights;
}

Neuron* Matrix::getNeuron(int x, int y){
	return _matrix[x][y];
}

vector<vector<Neuron*> > Matrix::getMatrix(){
	return _matrix;
}

void Matrix::updateWeightVector(double influence, double learningRate,
	vector<double> inputVector, int x, int y){
	vector<double> updatedWeigths;
	double newWeight = 0.0;
	double difference = 0.0;
	Neuron *neuron = _matrix[x][y];
	vector<double> oldWeights = neuron->getWeights();
	updatedWeigths.resize(_totalWeights);
	for(int i=0; i<_totalWeights; i++){
		difference = (inputVector[i] - oldWeights[i]));
		newWeight = oldWeights[i] + ((influence * learningRate) * difference;
		updatedWeigths[i] = newWeight;
	}
	_matrix[x][y]->setWeigths(updatedWeigths);
}

void Matrix::printMatrix(){
	for(int row=0; row < _size; row++){
		for(int col=0; col < _size; col++){
			_matrix[row][col]->info();
		}
	}
}

// Private methods
void Matrix::initializeMatrix(){
	_matrix.resize(_size);
	for(int i=0; i<_size; i++){
		_matrix[i].resize(_size);
	}

	// Initiliazing neurons randomly
	for(int row=0; row < _size; row++){
		for(int col=0; col < _size; col++){
			Neuron *neuron = new Neuron(row, col, _totalWeights);
			_matrix[row][col] = neuron;
		}
	}
}