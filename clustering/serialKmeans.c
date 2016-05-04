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
	return sqrt(pow((local.x - far.x),2) + pow((local.y - far.y),2));
}

void getNewCentroid(Cluster cluster, Point *newCentroid, Point *dataset){
	int i;
	double aveX = 0;
	double aveY = 0;
	int totalElements = cluster.totalElements;
	int *clusterElements = cluster.elements;
	int dataSetIndex = 0;

	if(totalElements == 0)
		return;

//#pragma omp paralle for reduction(+:aveA, aveB)
	for(i=0; i<totalElements; i++){
		dataSetIndex = clusterElements[i];
		Point p = dataset[dataSetIndex];
		aveX+=p.x;
		aveY+=p.y;
	}

	newCentroid->x=aveX/totalElements;
	newCentroid->y=aveY/totalElements;
}

void printElements(int *elements, int totalElements, Point *dataSet){
	int i,index;
	for(i=0; i<totalElements; i++){
		index = elements[i];
		printf("P(%f,%f)\n", dataSet[index].x, dataSet[index].y);
	}	
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

void refreshCentroids(Cluster *clusters, int totalClusters, Point *dataset){
	int i;
	for(i=0; i<totalClusters; i++){
		Point newCentroid;
		getNewCentroid(clusters[i], &newCentroid, dataset);
		clusters[i].lastCentroid.x = clusters[i].currentCentroid.x;
		clusters[i].lastCentroid.y = clusters[i].currentCentroid.y;
		clusters[i].currentCentroid.x = newCentroid.x;
		clusters[i].currentCentroid.y = newCentroid.y;
	}
}

void cleanClusters(Cluster *clusters, int totalClusters){
	int i,j;
	int clusterElements = 0;
	for(i=0; i<totalClusters; i++){
		clusterElements = clusters[i].totalElements;
		if(clusterElements!=0){
			for(j=0; j<clusterElements; j++){
				clusters[i].elements[j] = 0;
			}
			clusters[i].totalElements = 0;
		}
	}	
}


void printClustersNoElements(Cluster *clusters, int totalElements, Point *dataSet){
	int i = 0;
	for(i=0; i<totalElements; i++){
		printf("Cluster:%d, currentCentroid: (%f,%f) | lastCentroid:(%f,%f) , Total elements: %d\n",
			i+1, clusters[i].currentCentroid.x, clusters[i].currentCentroid.y,
			clusters[i].lastCentroid.x, clusters[i].lastCentroid.y,
			clusters[i].totalElements);
	}
}


void printClustersElements(Cluster *clusters, int totalElements, Point *dataSet){
	int i = 0;
	for(i=0; i<totalElements; i++){
		printf("Cluster:%d, currentCentroid: (%f,%f) | lastCentroid:(%f,%f) , Total elements: %d\n",
			i+1, clusters[i].currentCentroid.x, clusters[i].currentCentroid.y,
			clusters[i].lastCentroid.x, clusters[i].lastCentroid.y,
			clusters[i].totalElements);
		printElements(clusters[i].elements, clusters[i].totalElements, dataSet);
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

void kmeans(Point *dataset, int totalElementsDataSet, Cluster *clusters, int totalClusters){
	int i,j,winner, epochs, continueRunning;
	continueRunning = 1;
	epochs=0;
	while(continueRunning){
		if(epochs!=0)
			cleanClusters(clusters, totalClusters);

		for(i=0; i<totalElementsDataSet; i++){
			winner = winnerCluster(dataset[i], clusters, totalClusters);
			int *totalElements = &clusters[winner].totalElements;
			clusters[winner].elements[*totalElements] = i;
			*totalElements = *totalElements + 1;
		}

		refreshCentroids(clusters, totalClusters, dataset);
		epochs++;
		continueRunning = stopKmeans(clusters, totalClusters, epochs);
	}

	printClustersNoElements(clusters, totalClusters, dataset);
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
	struct timeval tval_before, tval_after, tval_result;
	gettimeofday(&tval_before, NULL);

	Point samples[N];
	Cluster clusters[K];
	
	initializeElements(samples, N);
	initializeClusters(clusters, K);
	
	kmeans(samples, N, clusters, K);
	
	gettimeofday(&tval_after, NULL);
	timersub(&tval_after, &tval_before, &tval_result);
	printf("Time elapsed: %ld.%06ld\n", (long int)tval_result.tv_sec, (long int)tval_result.tv_usec);
}