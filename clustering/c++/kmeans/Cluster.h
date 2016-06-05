#include <iostream>
#include <vector>

#include "Point.h"

using namespace std;

class Cluster{
	public:
		// Constructor
		Cluster();
		Cluster(int);

		//Destructor
		~Cluster();

		// Utilities
		void updateCentroid();
		void cleanCluster();
		void toString();
		void incrementX(double);
		void incrementY(double);
		void addSample(Point *);
		bool hasChanged();

		//Getters and Setters
		double getX();
		void setX(double);
		double getY();
		void setY(double);
		Point * getCentroid();
		Point * getLastCentroid();

	private:
		Point *centroid;
		Point *lastCentroid;
		vector<Point *> samples;
		double x;
		double y;
};