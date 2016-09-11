#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <time.h>

#include "utils.h"

using namespace std;

class Neuron{
	public:
		Neuron(int x, int y, int totalWeights);
		Neuron(int x, int y, vector<double> weigths);
		~Neuron();

		int getX();
		int getY();
		int getTotalWeights();
		vector<double> getWeights();

		void setX(int x);
		void setY(int y);
		void setWeigths(vector<double> weigths);

		void info();
		double distanceToNeuron(Neuron *neuron);
		double distanceToInputVector(vector<double> inputVector);

	private:
		int _x;
		int _y;
		int _totalWeights;
		vector<double> _weights;

		// Methods
		void initializeWeights();
};