#define K 4		//Total expected clusters
#define N 1000	//Total samples
#define MAXVALUE 100	//Max random value
#define EPOCHS 100000	//Max number of epochs

typedef struct{
	double x;
	double y;
} Point;

typedef struct{
	int totalElements;
	Point elements[N];
	Point lastCentroid;
	Point currentCentroid;
} Cluster;

//Points actions
void initializeElements(Point *elements, int totalElements);
int comparePoints(Point a, Point b);
double getDistance(Point local, Point far);
void getMean(Point *elements, int totalElements, Point *newCentroid);
void printElements(Point *elements, int totalElements);

//Clusters actions
void initializeClusters(Cluster *clusters, int totalElements);
void refreshCentroids(Cluster *clusters, int totalClusters);
void cleanClusters(Cluster *clusters, int totalClusters);
double printClusters(Cluster *clusters, int totalElements);

//k-means algorithm actions
int stopKmeans(Cluster *clusters, int totalClusters, int epochs);
void kmeans(Point *dataset, int totalElementsDataSet, Cluster *clusters, int totalClusters);

