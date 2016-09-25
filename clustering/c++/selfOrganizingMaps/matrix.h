#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "neuron.h"

using namespace std;

class Matrix{
	public:
		Matrix(int size, int totalWeights);
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

	private:
		int _size; // Width and Heigth of the matrix
		int _totalNeurons;
		int _totalWeights;
		vector<vector<Neuron*> > _matrix;

		// Methods
		void initializeMatrix();
};
#endif