#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <time.h>

#include "neuron.h"

using namespace std;

class Matrix{
	public:
		Matrix(int size, int totalWeights, bool initialize);
		Matrix(int size, int totalWeights, vector<RGB*> dataSet);
		~Matrix();
		int getSize();
		int getTotalNeurons();
		int getTotalWeights();
		Neuron* getNeuron(int x, int y);
		vector<vector<Neuron*> > getMatrix();
		void updateWeightVector(double influence, double learningRate,
			vector<double> inputVector, int x, int y);
		void updateWeightVector(vector<double> weightVector, int x, int y);
		void printMatrix();
		void setNeuron(Neuron *neuron);

	private:
		int _size; // Width and Heigth of the matrix
		int _totalNeurons;
		int _totalWeights;
		vector<vector<Neuron*> > _matrix;

		// Methods
		void initializeMatrix();
		void initializeMatrix(vector<RGB*> dataSet);
};
#endif