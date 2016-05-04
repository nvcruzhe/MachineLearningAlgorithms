#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <sys/time.h>
#include <omp.h>
#include <float.h>

#include "utils.h"
#include "serialKmeans.h"

//Points actions

void initializeElements(Point *elements, int totalElements){
	int i;
	for(i=0; i<totalElements; i++){
		elements[i].x = getRandomNumber(MAXVALUE);
		elements[i].y = getRandomNumber(MAXVALUE);
	}
}

int comparePoints(Point a, Point b){
	if((a.x == b.x) && (a.y == b.y))
		return 1;
	return 0;
}

double getDistance(Point local, Point far){
	double x = local.x - far.x;
	double y = local.y - far.y;
	x = x*x;
	y = y*y;
	return x+y;
}

//Clusters actions

void initializeClusters(Cluster *clusters, int totalElements){
	int i;
	for(i=0; i<totalElements; i++){
		clusters[i].lastCentroid.x = 0.0;
		clusters[i].lastCentroid.y = 0.0;
		clusters[i].totalElements = 0;
		clusters[i].currentCentroid.x = getRandomNumber(MAXVALUE);
		clusters[i].currentCentroid.y = getRandomNumber(MAXVALUE);
		//printf("Cluster: %d, (%f,%f)\n", i, clusters[i].currentCentroid.x, clusters[i].currentCentroid.y);
	}
}

void cleanClusters(Cluster *clusters, int totalClusters, int *whichClusterIn){
	int i;
//#pragma omp parallel for private(i)
	for(i=0; i<totalClusters; i++){
		clusters[i].xSum = 0.0;
		clusters[i].ySum = 0.0;
		clusters[i].totalElements = 0;
	}
//#pragma omp parallel for private(i)
	for(i=0; i<N; i++){
		whichClusterIn[i] = -1;
	}
}


void printClusters(Cluster *clusters, int totalElements, Point *dataSet){
	int i = 0;
	for(i=0; i<totalElements; i++){
		printf("Cluster:%d, currentCentroid: (%f,%f) | lastCentroid:(%f,%f) , Total elements: %d\n",
			i+1, clusters[i].currentCentroid.x, clusters[i].currentCentroid.y,
			clusters[i].lastCentroid.x, clusters[i].lastCentroid.y,
			clusters[i].totalElements);
	}
}

//k-means algorithm actions

int stopKmeans(Cluster *clusters, int totalClusters, int epochs){
	int continueRunning = 1;
	int i;
	if(epochs > EPOCHS)
		return 0;
	for(i=0; i<totalClusters; i++){
		continueRunning = continueRunning & comparePoints(clusters[i].lastCentroid, clusters[i].currentCentroid);
	}
	if(continueRunning)
		return 0;
	return 1;
}

int winnerCluster(Point point, Cluster *clusters, int totalClusters){
	double x = point.x;
	double y = point.y;
	double distance = FLT_MAX, localdistance=0.0;
	double distances[totalClusters];
	int i,winner=0;

	for(i=0; i<totalClusters; i++){
		localdistance = getDistance(point,clusters[i].currentCentroid);

		if(localdistance<distance){
			distance = localdistance;
			winner = i;
		}
	}
	
	return winner;
}

void kmeans(Point *dataset, int totalElementsDataSet, Cluster *clusters, int totalClusters, int *whichClusterIn){
	int i,j,winner, epochs, continueRunning;
	continueRunning = 1;
	epochs=0;
	while(continueRunning){
		if(epochs!=0)
			cleanClusters(clusters, totalClusters, whichClusterIn);

		//Check which centroid is the nearest for the coordinate 
		for(i=0; i<totalElementsDataSet; i++){
			winner = winnerCluster(dataset[i], clusters, totalClusters);
			clusters[winner].totalElements++;
			clusters[winner].xSum += dataset[i].x;
			clusters[winner].ySum += dataset[i].y;
			whichClusterIn[i] = winner;
		}

		//Refresh and recalculate centroids
		for(i=0; i<totalClusters; i++){
			double x = clusters[i].xSum/clusters[i].totalElements;
			double y = clusters[i].ySum/clusters[i].totalElements;
			clusters[i].lastCentroid.x =  clusters[i].currentCentroid.x;
			clusters[i].lastCentroid.y =  clusters[i].currentCentroid.y;
			clusters[i].currentCentroid.x = x;
			clusters[i].currentCentroid.y = y;
		}

		epochs++;
		continueRunning = stopKmeans(clusters, totalClusters, epochs);
	}

	printClusters(clusters, totalClusters, dataset);
	printf("continueRunning: %d, Epochs: %d\n", continueRunning, epochs);
}

/*
* K-Means algorithm example
*
* Compile: gcc serialKmeans.c utils.c -o skm -lm
* Compile parallel: gcc serialKmeans.c utils.c -o skm -lm -fopenmp -g -O0
* Execute: export OMP_NUM_THREADS=X
* gcc serialKmeans.c utils.c -o skm -fopenmp -lm  -Debug -openmp
* Run: ./skm
*/
int main(int argc, char *argv[]){
	//Variables
	struct timeval tval_before, tval_after, tval_result;
	Point samples[N];
	Cluster clusters[K];
	int whichClusterIn[N];
	
	//Initialize variables
	initializeElements(samples, N);
	initializeClusters(clusters, K);

	//Start processing
	gettimeofday(&tval_before, NULL);
	kmeans(samples, N, clusters, K, whichClusterIn);
	gettimeofday(&tval_after, NULL);

	//Results
	timersub(&tval_after, &tval_before, &tval_result);
	printf("Time elapsed: %ld.%06ld\n", (long int)tval_result.tv_sec, (long int)tval_result.tv_usec);
}