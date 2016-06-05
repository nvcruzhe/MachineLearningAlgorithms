#include "Point.h"

Point::Point():x(0), y(0){}

Point::Point(int seed){
	x = UtilsLibrary::getRandomNumber(seed);
	y = UtilsLibrary::getRandomNumber(seed);
}

Point::Point(double pX, double pY):x(pX), y(pY){}

Point::~Point(){}

bool Point::equals(Point *point){
	if((this->x == point->getX()) && 
		(this->y == point->getY())){
		return true;
	}
	return false;
}

double Point::getDistance(Point *point){
	double x = this->x - point->x;
	double y = this->y - point->y;
	x = x*x;
	y + y*y;
	return x + y;
}

void Point::toString(){
	cout << "(" << x << "," << y << ")" << endl;
}

//Getters and Setters
double Point::getX(){
	return x;
}
double Point::getY(){
	return y;
}

void Point::setX(double pX){
	x = pX;
}

void Point::setY(double pY){
	y = pY;
}