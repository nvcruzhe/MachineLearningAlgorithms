#include <iostream>

#include "UtilsLibrary.h"

using namespace std;

class Point{
	public:
		// Contructors
		Point();
		Point(int);
		Point(double, double);
		
		// Destructor
		~Point();

		// Utilities
		bool equals(Point *);
		double getDistance(Point *);
		void toString();

		//Getters and Setters
		double getX();
		void setX(double);
		double getY();
		void setY(double);

	private:
		double x;
		double y;
};