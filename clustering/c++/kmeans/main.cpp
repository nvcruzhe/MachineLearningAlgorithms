#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>

#include "Kmeans.h"

int main(int argc, char *argv[]){
	int k = atoi(argv[1]); // Total expected clusters
	int n = atoi(argv[2]); // Total samples;
	int maxValue = atoi(argv[3]); // Max random value;
	int epochs = atoi(argv[4]); //Max number of epochs
	vector<Point *> pointsToClassify;
	vector<Cluster *> clusters;
	Kmeans *kmeans = new Kmeans(epochs);

	//Initialize points
	for(int i=0; i<n; i++){
		Point *point = new Point(maxValue);
		pointsToClassify.push_back(point);
	}

	//Initialize clusters
	for(int i=0; i<k; i++){
		Cluster *cluster = new Cluster(maxValue);
		clusters.push_back(cluster);
	}

	kmeans->runKmeansAlgorithm(&pointsToClassify, &clusters);

	for(int i=0; i<k; i++){
		clusters.at(i)->toString();
	}
}