#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <limits>
#include <math.h>
#include <GL/glut.h>

#include "matrix.h"

using namespace std;

class SelfOrganizingMaps{
	public:
		SelfOrganizingMaps(int size, int totalWeights, int maxEpochs,
			int totalSamples, double learningRate);
		~SelfOrganizingMaps();
		int getIterations();
		int getEpochs();
		int getSize();
		int getTotalWeights();
		Matrix* getMatrix();

		// Main functionality of the algorithm
		void train(vector<double> inputVector);

		// OpenGL needed functions
		void display();
		void reset();

	private:
		int _iterations;
		int _maxEpochs;
		int _size;
		int _totalWeigths;
		int _totalSamples;
		int _epochs;
		double _defaultLearningRate;
		double _initialNeighbourhoodRadius;
		double _radiusTimeConstant;
		double _learningRateTimeConstant;
		Matrix *_matrix;

		// Methods
		// Main functionality util  methods
		double getNeighbourhoodRadius();
		double getCurrenLearningRate();
		double getInfluence(double distanceToBMU, double radius);
};