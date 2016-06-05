#include "Kmeans.h"

Kmeans::Kmeans(){}

Kmeans::Kmeans(int pEpochs):epochs(pEpochs){}

void Kmeans::runKmeansAlgorithm(vector<Point *> *pointsToClassify, vector<Cluster *> *clusters){
	int elementsToClassify = pointsToClassify->size();
	int totalClusters = clusters->size();
	int epochs = 0;
	bool continueRunning = true;

	while(continueRunning){
		for(int i=0; i<elementsToClassify; i++){
			Point *current = pointsToClassify->at(i);
			int clusterIndex = winnerCluster(current, clusters, totalClusters);
			Cluster *winnerCluster =  clusters->at(clusterIndex);
			winnerCluster -> incrementX(current->getX());
			winnerCluster -> incrementY(current->getY());
			winnerCluster -> addSample(current);
		}

		for(int i=0; i<totalClusters; i++){
			clusters->at(i)->updateCentroid();
		}

		epochs++;
		continueRunning = stop(clusters, totalClusters, epochs);
		if(continueRunning){
			for(int i=0; i<totalClusters; i++){
				clusters->at(i)->cleanCluster();
			}
		}
	}
}

int Kmeans::winnerCluster(Point *point, vector<Cluster *> *clusters, int totalClusters){
	double x =  point->getX();
	double y = point->getY();
	double distance = FLT_MAX;
	double localDistance = 0.0;
	int winner = 0;

	for(int i=0; i<totalClusters; i++){
		localDistance = point->getDistance(clusters->at(i)->getCentroid());
		if(localDistance < distance){
			distance = localDistance;
			winner = i;
		}
	}

	return winner; 
}

int Kmeans::stop(vector<Cluster *> *pClusters, int pTotalClusters, int pEpochs){
	bool stop = true;
	if(pEpochs >= epochs)
		return false;

	for(int i=0; i<pTotalClusters; i++){
		stop = stop && pClusters->at(i)->hasChanged();
	}

	if(stop){
		return false;
	}

	return true;
}