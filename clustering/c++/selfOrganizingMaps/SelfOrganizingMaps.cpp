#include "SelfOrganizingMaps.h"

SelfOrganizingMaps::SelfOrganizingMaps(int size, int totalWeights,
	int maxEpochs, int totalSamples, double defaultLearningRate):
	_iterations(0), _size(size), _totalWeigths(totalWeights),
	_maxEpochs(maxEpochs), _totalSamples(totalSamples),
	_epochs(0), _defaultLearningRate(defaultLearningRate),
	_initialNeighbourhoodRadius(size/2){
	_matrix =  new Matrix(_size, _totalWeigths);
	_radiusTimeConstant = _maxEpochs/log(_initialNeighbourhoodRadius);
	_learningRateTimeConstant = _maxEpochs/log(defaultLearningRate);
}

SelfOrganizingMaps::~SelfOrganizingMaps(){
	delete _matrix;
}

int SelfOrganizingMaps::getIterations(){
	return _iterations;
}

int SelfOrganizingMaps::getEpochs(){
	return _epochs;
}

int SelfOrganizingMaps::getSize(){
	return _size;
}

int SelfOrganizingMaps::getTotalWeights(){
	return _totalWeigths;
}

Matrix* SelfOrganizingMaps::getMatrix(){
	return _matrix;
}

// Main functionality of the algorithm
/*
void SelfOrganizingMaps::train(vector<double> inputVector){
	if(_epochs > _maxEpochs){
		return;
	}

	Neuron *currentNeuron = NULL;
	double distanceToNeuron = 0.0;
	double influence = 0.0;
	double distance = 0;
	double winnerNeuronX = 0.0;
	double winnerNeuronY = 0.0;
	double closestDistance = (255.0 * 255.0) + (255.0 * 255.0) + (255.0 * 255.0);

	// Getting BMU
	for(int row=0; row<_size; row++){
		for(int col=0; col<_size; col++){
			distance = _matrix->getNeuron(row, col)->distanceToInputVector(inputVector);
			if(distance < closestDistance){
				winnerNeuronX = row;
				winnerNeuronY = col;
				closestDistance = distance;
			}else if(distance == closestDistance){
				if(Utils::getRandomDoubleNumber(0, 1) < 0.5){
					winnerNeuronX = row;
					winnerNeuronY = col;
				}
			}
		}
	}

	// Adjusting weigths of neurons
	// Get current Learning Rate scientific method
	double currenLearningRate = getCurrenLearningRate();

	// Get neighbourhood radius scientific method
	double neighbourhoodRadius = getNeighbourhoodRadius();

	// Update the BMU neuron
	_matrix->updateWeightVector(1.0, currenLearningRate, inputVector, winnerNeuronX,
		winnerNeuronY);

	//Check which neurons should update its weight vector
	Neuron *bmu = _matrix->getNeuron(winnerNeuronX, winnerNeuronY);
	for(int row=0; row<_size; row++){
		for(int col=0; col<_size; col++){
			currentNeuron = _matrix->getNeuron(row, col);
			distanceToNeuron = bmu->distanceToNeuron(currentNeuron);
			if(distanceToNeuron <= neighbourhoodRadius){
				// The current neuron is going to be updated

				// Get influence of the neuron based in its distance to BMU scientific method
				influence = getInfluence(distanceToNeuron, neighbourhoodRadius);

				// Update neuron
				_matrix->updateWeightVector(influence, currenLearningRate, inputVector,
					row, col);
			}
		}
	}

	_iterations++;
	if(_iterations == _totalSamples){
		_epochs++;
		_iterations = 0;
		if(_epochs%100 == 0)
			cout << "Epoch: " << _epochs << endl;
	}
}
//*/

void SelfOrganizingMaps::train(vector<double> inputVector){
	if(_epochs > _maxEpochs){
		return;
	}

	Neuron *currentNeuron = NULL;
	double distanceToNeuron = 0.0;
	double influence = 0.0;
	double distance = 0;
	double winnerNeuronX = 0.0;
	double winnerNeuronY = 0.0;
	double gaussian = 0.0;
	double closestDistance = (255.0 * 255.0) + (255.0 * 255.0) + (255.0 * 255.0);

	// Getting BMU
	for(int row=0; row<_size; row++){
		for(int col=0; col<_size; col++){
			distance = _matrix->getNeuron(row, col)->distanceToInputVector(inputVector);
			if(distance < closestDistance){
				winnerNeuronX = row;
				winnerNeuronY = col;
				closestDistance = distance;
			}else if(distance == closestDistance){
				if(Utils::getRandomDoubleNumber(0, 1) < 0.5){
					winnerNeuronX = row;
					winnerNeuronY = col;
				}
			}
		}
	}

	// Adjusting weigths of neurons
	// Get current Learning Rate
	double currenLearningRate = ((double)_epochs/_maxEpochs);
	if(currenLearningRate >= 1){
		currenLearningRate = 0.99;
	}
	currenLearningRate = 1 - currenLearningRate;

	// Update the BMU neuron
	_matrix->updateWeightVector(1.0, currenLearningRate, inputVector, winnerNeuronX,
		winnerNeuronY);

	//Check which neurons should update its weight vector
	int debug = 0;
	Neuron *bmu = _matrix->getNeuron(winnerNeuronX, winnerNeuronY);
	for(int row=0; row<_size; row++){
		for(int col=0; col<_size; col++){
			currentNeuron = _matrix->getNeuron(row, col);
			distanceToNeuron = bmu->distanceToNeuron(currentNeuron);
			// The current neuron is going to be updated

			// Get influence of the neuron based in its distance to BMU scie
			
			//influence = exp(-(distanceToNeuron/(10 - ((double)_epochs/10.0))));
			influence = exp(-(distanceToNeuron/(_initialNeighbourhoodRadius - (_epochs/_radiusTimeConstant))));
			// Update neuron
			_matrix->updateWeightVector(influence, currenLearningRate, inputVector, row, col);
		}
		debug = 0;
	}

	_iterations++;
	if(_iterations == _totalSamples){
		_epochs++;
		_iterations = 0;
		cout << "Epoch: " << _epochs << endl;
	}
}

// OpenGL needed functions

void SelfOrganizingMaps::display(){
	vector<double> weigths;
	for(int row=0; row<_size; row++){
		for(int col=0; col<_size; col++){
			weigths = _matrix->getNeuron(row, col)->getWeights();
			glColor3f(weigths[0], weigths[1], weigths[2]);
			glBegin(GL_QUADS);
				glVertex3f(row, col, 0);			// upper left
				glVertex3f(row, col-1, 0);			// lower left
				glVertex3f(row+1, col-1, 0);		// lower right
				glVertex3f(row+1, col, 0);			// upper right
			glEnd();
		}
	}
}

void SelfOrganizingMaps::reset(){
	_matrix =  new Matrix(_size, _totalWeigths);
	_iterations = 0;
	_epochs = 0;
}


// Private methods
/*
* The SOM algorithm uses de exponential decay function, for getting
* the influence radius once the BMU is obtained.
* Over time the neighbourhood will shrink to the size of just one node.
*/
double SelfOrganizingMaps::getNeighbourhoodRadius(){
	return _initialNeighbourhoodRadius * exp(-(double)_epochs/_radiusTimeConstant);
}

/*
* The SOM algorithm uses de exponential decay function, for getting
* the learning rate.
* Over time the learning rate will be reduced close to 0.
*/
double SelfOrganizingMaps::getCurrenLearningRate(){
	return _defaultLearningRate * exp(-(double)_epochs/_learningRateTimeConstant);
}

/*
* Determines the influence that the input vector will have in a neuron
* based in its distance.
*/
double SelfOrganizingMaps::getInfluence(double distanceToBMU, double radius){
	double exponent = - ((distanceToBMU * distanceToBMU) / 2 * (radius * radius));
	return exp(exponent);
}