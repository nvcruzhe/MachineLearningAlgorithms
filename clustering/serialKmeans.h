#define K 2				//Total expected clusters
#define N 400000		//Total samples
//#define N 50		//Total samples
#define MAXVALUE 100	//Max random value
#define EPOCHS 100000	//Max number of epochs


typedef struct{
	double x;
	double y;
} Point;

typedef struct{
	int totalElements;
	double xSum;
	double ySum;
	Point lastCentroid;
	Point currentCentroid;
} Cluster;

//Points actions
void initializeElements(Point *elements, int totalElements);
int comparePoints(Point a, Point b);
double getDistance(Point local, Point far);
void getNewCentroid(Cluster cluster, Point *newCentroid, Point *dataset);
void printElements(int *elements, int totalElements, Point *dataSet);
int winnerCluster(Point point, Cluster *clusters, int totalClusters);

//Clusters actions
void initializeClusters(Cluster *clusters, int totalElements);
void refreshCentroids(Cluster *clusters, int totalClusters, Point *dataset);
void cleanClusters(Cluster *clusters, int totalClusters, int *whichClusterIn);
void printClustersElements(Cluster *clusters, int totalElements, Point *dataSet);
void printClusters(Cluster *clusters, int totalElements, Point *dataSet);

//k-means algorithm actions
int stopKmeans(Cluster *clusters, int totalClusters, int epochs);
void kmeans(Point *dataset, int totalElementsDataSet, Cluster *clusters, int totalClusters, int *whichClusterIn);

