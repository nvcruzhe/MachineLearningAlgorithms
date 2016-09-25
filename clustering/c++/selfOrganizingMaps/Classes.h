#ifndef CLASSES_H
#define CLASSES_H

#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>
#include <time.h>
#include <string>
#include <ctime>
#include <sstream>
#include <map>
#include <limits>
#include <math.h>
#include <GL/glut.h>

#include "matrix.h"

using namespace std;

class Utils;
class SelfOrganizingMaps;

class Utils{
	public:
		static int getRandomDoubleNumber();
		static void exportMatrixToFile(Matrix *matrix, int completedEpochs,
			int maxEpochs, double initialLearningRate,
			double finalLearningRate);
		static void importMatrixFromFile(char *fileName, SelfOrganizingMaps *som);

		// DataSets
		static vector<vector<double> > createColorDataSet(int dataSetSize, int totalWeigths);
		static vector<vector<double> > createColorTestDataSet();
		static vector<RGB* > createBlueColorDataSet();
		static vector<RGB* > createRedColorDataSet();
		static vector<RGB* > createGreenColorDataSet();
		static vector<RGB* > createYellowColorDataSet();

		// Time functions
		static string currentTime();
		static string currentDate();

		// Others
		static string buildFileName();
};

class SelfOrganizingMaps{
	public:
		SelfOrganizingMaps(int size, int totalWeights, int maxEpochs,
			double learningRate);
		SelfOrganizingMaps(int size, int totalWeights,
			int maxEpochs, double initialLearningRate, vector<RGB* > dataSet);
		~SelfOrganizingMaps();
		void reConstructSelfOrganizingMap(int size, int totalWeights,
			int maxEpochs, double initialLearningRate, int epochs);
		int getIterations();
		int getEpochs();
		int getSize();
		int getTotalWeights();
		Matrix* getMatrix();

		// Setters
		void setSize(int size){_size = size;}
		void setEpochs(int epochs){_epochs = epochs;}
		void setMaxEpochs(int maxEpochs){_maxEpochs = maxEpochs;}
		void setInitialLearningRate(double initialLearningRate){
			_initialLearningRate = initialLearningRate;
		}
		void setTotalWeights(int totalWeights){_totalWeigths =  totalWeights;}

		// Main functionality of the algorithm
		void train(vector<double> inputVector);
		void trainPlainCode(vector<double> inputVector);
		void trainSegmentedFunctions(vector<double> inputVector);
		double getCurrenLearningRate();

		// OpenGL needed functions
		void displayUsingWeigths();
		void displayUsingNeuronColor();
		void reset();

		// Testing cases
		void evaluateIndependentVector(vector<double> inputVector);

		// Import trained matrix
		void setWeightVector(vector<double> weightVector, int x, int y);

	private:
		int _iterations;
		int _maxEpochs;
		int _size;
		int _totalWeigths;
		int _totalSamples;
		int _epochs;
		double _initialLearningRate;
		double _initialNeighbourhoodRadius;
		double _radiusTimeConstant;
		double _learningRateTimeConstant;
		Matrix *_matrix;
		map<Neuron *, Neuron *> _bmuTestCases;

		// Methods
		// Main functionality util  methods
		double getNeighbourhoodRadius();
		double getInfluence(double distanceToBMU, double radius);
		Neuron* getBMU(vector<double> inputVector);
		void updateMatrixWeigths(Neuron *bmu, vector<double> inputVector);
};

#endif