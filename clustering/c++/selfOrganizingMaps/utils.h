#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <time.h>

using namespace std;

class Utils{
	public:
		static int getRandomDoubleNumber();

		// DataSets
		static vector<vector<double> > createColorDataSet(int dataSetSize, int totalWeigths);
		static vector<vector<double> > createColorTestDataSet();
};