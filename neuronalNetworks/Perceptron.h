#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <cmath>

#include "Neuron.h"

using namespace std;

class Perceptron{
	public:
		Perceptron(int, int, int, double);
		double execute(vector<int> *);
		void train(vector < vector<int> > *, vector<int> *);

	private:
		void initWeights();
		double randomNumber();
		double randomWeight();
		double sigmoidFunction(double);
		double sigmoidDerivate(double);
		void backPropagation(vector<int> *, double, double);

		int inputLayerSize;
		int hiddenLayerSize;
		int epochsRequired;
		double learningRate;
		vector< vector<double> > inputHiddenWeights;
		vector<double> hiddenOutputWeights;
		vector<Neuron *> hiddenLayerNeurons;
};