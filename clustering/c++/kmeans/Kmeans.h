#include <iostream>

#include <float.h>

#include "Cluster.h"

class Kmeans{
	public:
		// Constructor
		Kmeans(int);

		// Functionality
		void runKmeansAlgorithm(vector<Point *> *, vector<Cluster *> *);

	private:
		// Utilities
		int winnerCluster(Point *, vector<Cluster *> *, int);
		int stop(vector<Cluster *> *, int, int);
		
		//Constructor
		Kmeans();

		
		int epochs;

};