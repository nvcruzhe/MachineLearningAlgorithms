#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

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
	double in = pow(x,2) + pow(y,2);
	double distance =  sqrt(in);
	return distance;
}

void getMean(Point *elements, int totalElements, Point *newCentroid){
	int i;
	double x=0.0, y=0.0;
	for(i=0; i<totalElements; i++){
		x+=elements[i].x;
		y+=elements[i].y;
	}
	x = x/totalElements;
	y = y/totalElements;
	newCentroid->x = x;
	newCentroid->y = y;
}

void printElements(Point *elements, int totalElements){
	int i;
	for(i=0; i<totalElements; i++){
		printf("%f,%f\n",elements[i].x, elements[i].y);
	}	
}

//Clusters actions

void initializeClusters(Cluster *clusters, int totalElements){
	int i;
	for(i=0; i<totalElements; i++){
		clusters[i].lastCentroid.x = 0.0;
		clusters[i].lastCentroid.y = 0.0;
		clusters[i].currentCentroid.x = getRandomNumber(MAXVALUE);
		clusters[i].currentCentroid.y = getRandomNumber(MAXVALUE);
		clusters[i].totalElements = 0;
	}
}

void refreshCentroids(Cluster *clusters, int totalClusters){
	int i;
	for(i=0; i<totalClusters; i++){
		Point newCentroid;
		getMean(clusters[i].elements, clusters[i].totalElements, &newCentroid);
		clusters[i].lastCentroid.x = clusters[i].currentCentroid.x;
		clusters[i].lastCentroid.y = clusters[i].currentCentroid.y;
		clusters[i].currentCentroid.x = newCentroid.x;
		clusters[i].currentCentroid.y = newCentroid.y;
	}
}

void cleanClusters(Cluster *clusters, int totalClusters){
	int i,j;
	int totalElements = 0;
	for(i=0; i<totalClusters; i++){
		totalElements = clusters[i].totalElements;
		if(totalElements!=0){
			for(j=0; j<totalElements; j++){
				clusters[i].elements[j].x = 0.0;
				clusters[i].elements[j].y = 0.0;
			}
			clusters[i].totalElements = 0;
		}
	}	
}

double printClusters(Cluster *clusters, int totalElements){
	int i = 0;
	for(i=0; i<totalElements; i++){
		printf("Cluster:%d, currentCentroid: (%f,%f) | lastCentroid:(%f,%f) , Total elements: %d\n",
			i+1, clusters[i].currentCentroid.x, clusters[i].currentCentroid.y,
			clusters[i].lastCentroid.x, clusters[i].lastCentroid.y,
			clusters[i].totalElements);
		//printElements(clusters[i].elements, clusters[i].totalElements);
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

void kmeans(Point *dataset, int totalElementsDataSet, Cluster *clusters, int totalClusters){
	int i,j, winner, epochs, continueRunning;
	continueRunning = 1;
	epochs=0;
	while(continueRunning){
		cleanClusters(clusters, totalClusters);
		//TODO:
		/*
		* Es posible hacerlo de esta forma? Ya que en la forma que se agregan los elementos a los diferentes
		* clusters, tenemos una seccion critica y el aumento del total de los elementos
		*
		* La otra forma seria, por cada cluster mandar a evaluar todos los elementos y ver si 
		* entran en el cluster que los mando a llamar donde el numero de hilos seria igual al numero
		* de clusters que deseamos encontrar.
		*/
		for(i=0; i<totalElementsDataSet; i++){
			double distance = getDistance(dataset[i], clusters[0].currentCentroid);
			double distanceToCentroid = distance;
			winner = 0;
			for(j=1; j<totalClusters; j++){
				distance = getDistance(dataset[i], clusters[j].currentCentroid);
				if(distanceToCentroid > distance){
					distanceToCentroid = distance;
					winner = j;
				}
			}
			//int *indexInCluster = &clusters[winner].totalElements;
			clusters[winner].elements[clusters[winner].totalElements] = dataset[i];
			clusters[winner].totalElements++;
		}
		refreshCentroids(clusters, K);
		epochs++;
		continueRunning = stopKmeans(clusters, K, epochs);	
	}
	printClusters(clusters, K);
	printf("continueRunning: %d, Epochs: %d\n", continueRunning, epochs);
}

/*
* K-Means algorithm example
*
* Compile: gcc serialKmeans.c utils.c -o skm -lm
* Run: ./skm
*/
int main(int argc, char *argv[]){
	Point samples[N];
	Cluster clusters[K];
	initializeElements(samples, N);
	initializeClusters(clusters, K);
	kmeans(samples, N, clusters, K);
}