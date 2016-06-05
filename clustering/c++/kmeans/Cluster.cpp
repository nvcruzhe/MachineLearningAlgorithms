#include "Cluster.h"

Cluster::Cluster(){
	centroid = new Point();
	lastCentroid = new Point();
	x = 0.0;
	y = 0.0;
}

Cluster::Cluster(int element){
	centroid = new Point(element);
	lastCentroid = new Point();
	x = 0.0;
	y = 0.0;
}

Cluster::~Cluster(){
	delete(centroid);
	delete(lastCentroid);
}

void Cluster::updateCentroid(){
	int totalElements = samples.size();
	lastCentroid->setX(centroid->getX());
	lastCentroid->setY(centroid->getY());
	centroid->setX(x/totalElements);
	centroid->setY(y/totalElements);
}

void Cluster::cleanCluster(){
	x = 0.0;
	y = 0.0;
	samples.clear();
}

Point * Cluster::getCentroid(){
	return centroid;
}

Point * Cluster::getLastCentroid(){
	return lastCentroid;
}

void Cluster::toString(){
	cout << "Cluster" << endl;
	cout << "Centroid: ";
	centroid->toString();
	cout << "lastCentroid: ";
	lastCentroid->toString();
	cout << "Total elements in this cluster" << samples.size() << endl;
	cout << "sumX: " << x << " sumY: " << y << endl;
}

double Cluster::getX(){
	return x;
}

void Cluster::setX(double pX){
	x = pX;
}

void Cluster::incrementX(double pX){
	x += pX;
}

double Cluster::getY(){
	return y;
}

void Cluster::setY(double pY){
	y = pY;
}

void Cluster::incrementY(double pY){
	y += pY;
}

void Cluster::addSample(Point *pPoint){
	samples.push_back(pPoint);
}

bool Cluster::hasChanged(){
	if(centroid->equals(lastCentroid)){
		return false;
	}
	return true;
}