#ifndef UTILS_H
#define UTILS_H

#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>
#include <time.h>
#include <string>
#include <ctime>

#include "matrix.h"

using namespace std;

class Utils{
	public:
		static int getRandomDoubleNumber();
		static void exportMatrixToFile(Matrix *matrix, int epochs);
		static void importMatrixFromFile(char *filename);

		// DataSets
		static vector<vector<double> > createColorDataSet(int dataSetSize, int totalWeigths);
		static vector<vector<double> > createColorTestDataSet();
		static string currentTime();
		static string currentDate();
		static string buildFileName();
};
#endif