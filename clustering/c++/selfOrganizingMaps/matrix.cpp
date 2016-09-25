#include "matrix.h"

Matrix::Matrix(int size, int totalWeights) : _size(size),
	_totalWeights(totalWeights), _totalNeurons(size * size){
	initializeMatrix();
}

Matrix::Matrix(int size, int totalWeights, vector<RGB*> dataSet) :
	_size(size), _totalWeights(totalWeights), _totalNeurons(size * size){
	initializeMatrix(dataSet);
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
		difference = (inputVector[i] - oldWeights[i]);
		newWeight = oldWeights[i] + ((influence * learningRate) * difference);
		updatedWeigths[i] = newWeight;
	}
	_matrix[x][y]->setWeigths(updatedWeigths);
	_matrix[x][y]->setNeuronColor(updatedWeigths);
}

void Matrix::updateWeightVector(vector<double> weightVector, int x, int y){
	_matrix[x][y]->setWeigths(weightVector);
	_matrix[x][y]->setNeuronColor(weightVector);
}

void Matrix::printMatrix(){
	for(int row=0; row < _size; row++){
		for(int col=0; col < _size; col++){
			_matrix[row][col]->info();
		}
	}
}

// Private methods
// Initialize the matrix with random values of colors
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

// Initializa the matrix from a dataSet, selecting randomly the index
// of the dataSet to be uploaded to the matrix
void Matrix::initializeMatrix(vector<RGB*> dataSet){
	_matrix.resize(_size);
	for(int i=0; i<_size; i++){
		_matrix[i].resize(_size);
	}

	int dataSetSize = dataSet.size();
	int dataSetIndex = 0;

	srand (time(0));
	// Initiliazing neurons randomly
	for(int row=0; row < _size; row++){
		for(int col=0; col < _size; col++){
			dataSetIndex = rand() % dataSetSize;
			//cout << dataSetIndex<<": "<< dataSet[dataSetIndex][0] << "," << dataSet[dataSetIndex][1] << "," << dataSet[dataSetIndex][2] << endl; 
			Neuron *neuron = new Neuron(row, col, _totalWeights, dataSet[dataSetIndex]);
			_matrix[row][col] = neuron;
		}
	}
}