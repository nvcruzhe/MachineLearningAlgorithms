#include "neuron.h"

Neuron::Neuron(int x, int y, int totalWeights) : _x(x), _y(y),
	_totalWeights(totalWeights){
	_weights.resize(_totalWeights);
	_neuronColor = new RGB();
	initializeNeuron();
}

Neuron::Neuron(int x, int y, vector<double> weigths) :
	_x(x), _y(y){
		_totalWeights = weigths.size();
		_weights.resize(_totalWeights);
		_neuronColor = new RGB();
		for(int i = 0; i < _totalWeights; i++){
			_weights[i] = weigths[i];
		}
}

Neuron::~Neuron(){
	delete _neuronColor;
}

int Neuron::getX(){
	return _x;
}

int Neuron::getY(){
	return _y;
}

int Neuron::getTotalWeights(){
	return _totalWeights;
}

vector<double> Neuron::getWeights(){
	return _weights;
}

RGB *Neuron::getNeuronColor(){
	return _neuronColor;
}

void Neuron::setX(int x){
	_x = x;
}

void Neuron::setY(int y){
	_y = y;
}

void Neuron::setNeuronColor(double red, double green, double blue){
	_neuronColor->setRGB(red, green, blue);
}

void Neuron::info(){
	cout << "Postion in matrix (" << _x << "," << _y << ") Total weigths: " << _totalWeights << "\n";
	for(int i=0; i<_totalWeights; i++){
		cout << "Weight " << i << ": " << _weights[i] << "\n";
	}
	cout << "\n";
}

/*
string Neuron::exportNeuronWeights(){
	string weigths = "[" + to_string(_weights[0]);
	for(int i=1; i<_totalWeights; i++){
		weigths += "," + to_string(_weights[i]);
	}
	weigths += "]";
	return weigths;
}
*/

string Neuron::exportNeuronWeights(){
	string weigths = "" + to_string(_weights[0]);
	for(int i=1; i<_totalWeights; i++){
		weigths += " " + to_string(_weights[i]);
	}
	weigths += "";
	return weigths;
}

/*
* Gets the euclidean distance from any neuron to this neuron
* This method is used to check if this neuron is going to be affected
* by the update of the weights
*/
double Neuron::distanceToNeuron(Neuron *neuron){
	double xDistance =  neuron->getX() - _x;
	xDistance *= xDistance;
	double yDistance = neuron->getY() - _y;
	yDistance *= yDistance;
	return xDistance + yDistance;
}

/*
* Gets the distance from an input vector with a total of N weights
* to this neuron.
* If the total weights of the input vector are not the same, the operation
* is not done, and the execution fails.
* This methos is used to get the BMU.
*/
double Neuron::distanceToInputVector(vector<double> inputVector){
	double totalDistance = 0.0;
	double currentWeight = 0.0;
	
	if(inputVector.size() != _totalWeights){
		// TODO:
		// Lanzar una excepcion de pesos diferentes
		cout << "ERROR: The total weights in the input vector differ from the ones in the neuron";
		return 1;
	}

	for(int i=0; i<_totalWeights; i++){
		//cout << inputVector[i] << " " << _weights[i] << endl; 
		currentWeight = inputVector[i] - _weights[i];
		currentWeight *= currentWeight;
		totalDistance += currentWeight;
	}

	return totalDistance;
}

void Neuron::setWeigths(vector<double> weigths){
	for(int i=0; i<_totalWeights; i++){
		_weights[i] = weigths[i];
	}
}

void Neuron::setNeuronColor(vector<double> rgb){
	if(_totalWeights>=3){
		_neuronColor->setRGB(rgb[0], rgb[1], rgb[2]);
	}
}

// Private methods

void Neuron::initializeNeuron(){
	for(int i=0; i<_totalWeights; i++){
		_weights[i] = (double)rand() / (double)RAND_MAX;
	}

	// Setting neuron initial color
	if(_totalWeights >= 3){
		_neuronColor->setRGB(_weights[0], _weights[1], _weights[2]);
	}
}