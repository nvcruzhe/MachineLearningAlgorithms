#ifndef NEURON_H
#define NEURON_H

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <time.h>
#include <string>

#include "RGB.h"

using namespace std;

class Neuron{
	public:
		Neuron(int x, int y, int totalWeights);
		Neuron(int x, int y, vector<double> weigths);
		Neuron(int x, int y, int totalWeights, RGB* rgb);
		~Neuron();

		int getX();
		int getY();
		int getTotalWeights();
		vector<double> getWeights();
		RGB *getNeuronColor();

		void setX(int x);
		void setY(int y);
		void setWeigths(vector<double> weigths);
		void setNeuronColor(double red, double green, double blue);
		void setNeuronColor(vector<double> rgb);
		void setRGB(RGB *rgb);

		void info();
		string exportNeuronWeights();
		double distanceToNeuron(Neuron *neuron);
		double distanceToInputVector(vector<double> inputVector);

	private:
		int _x;
		int _y;
		int _totalWeights;
		vector<double> _weights;
		RGB *_neuronColor;

		// Methods
		void initializeNeuron();
};
#endif