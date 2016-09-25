#include "Classes.h"

int Utils::getRandomDoubleNumber(){
    return (double)rand() / RAND_MAX;
}

void Utils::exportMatrixToFile(Matrix *matrix, int completedEpochs,
			int maxEpochs, double initialLearningRate,
			double finalLearningRate){
	string fileName = Utils::buildFileName();
	ofstream file;
	file.open (fileName);
	int matrixSize = matrix->getSize();
	int totalWeigths =  matrix->getTotalWeights();
	file << matrixSize << "\n" << completedEpochs << "\n" << maxEpochs << "\n";
	file << initialLearningRate << "\n" << finalLearningRate << "\n";
	file << totalWeigths << "\n";
	for(int row=0; row<matrixSize; row++){
		string line = matrix->getNeuron(row, 0)->exportNeuronWeights();
		for(int col=1; col<matrixSize; col++){
			line += " " + matrix->getNeuron(row, col)->exportNeuronWeights();
		}
		line += "\n";
		file << line;
	}
	file.close();
	cout << "Se ha terminado de guardar el entrenamiento" << endl;
}

void Utils::importMatrixFromFile(char *fileName, SelfOrganizingMaps *som){
	//const char* fileName = "trainedMatrix.txt";
	std::ifstream infile(fileName);
	string line;
	vector<double> neuronRGB;
	//cout << "Start reading file" << endl;
	getline(infile,line);
	int size = atoi(line.c_str());
	//cout << "Size: " << size << endl;
	getline(infile,line);
	int executedEpochs = atoi(line.c_str());
	//cout << "Executed epochs: " << executedEpochs << endl;
	getline(infile,line);
	int maxEpochs = atoi(line.c_str());
	//cout << "MAX Epochs" << maxEpochs << endl;
	getline(infile,line);
	double initialLearningRate = atof(line.c_str());
	//cout << "Initial Learning rate: " << initialLearningRate << endl;
	getline(infile,line);
	double currentLearningRate = atof(line.c_str());
	//cout << "Current Learning rate: " << currentLearningRate << endl;
	getline(infile,line);
	int totalWeights = atoi(line.c_str());
	//cout << "Total Weights: " << totalWeights << endl;
	neuronRGB.resize(totalWeights);
	som->reConstructSelfOrganizingMap(size, totalWeights, maxEpochs,
		initialLearningRate, executedEpochs);
	for(int row=0; row<size; row++){ // For every row
		getline(infile,line);
		stringstream ssin(line);
		for(int col=0; col<size; col++){ // for each column
			// Get all the weights of the neuron in (row, col)
			for(int weigths=0; weigths<totalWeights; weigths++){
				ssin >> neuronRGB[weigths];
			}
			som->setWeightVector(neuronRGB, row, col);
		}
	}
	//cout << "Finish reading file" << endl;
}

vector<vector<double> > Utils::createColorDataSet(int dataSetSize, int totalWeigths){
	vector<vector<double> > dataSet;
	dataSet.resize(dataSetSize);
	
	for(int i=0; i<48; i++){
		dataSet[i].resize(totalWeigths);
	}

	dataSet[0][0] = 255;
	dataSet[0][1] = 0;
	dataSet[0][2] = 0;

	dataSet[1][0] = 0;
	dataSet[1][1] = 255;
	dataSet[1][2] = 0;

	dataSet[2][0] = 0;
	dataSet[2][1] = 0;
	dataSet[2][2] = 255;

	dataSet[3][0] = 255;
	dataSet[3][1] = 255;
	dataSet[3][2] = 0;

	dataSet[4][0] = 255;
	dataSet[4][1] = 0;
	dataSet[4][2] = 255;

	dataSet[5][0] = 0;
	dataSet[5][1] = 255;
	dataSet[5][2] = 255;

	dataSet[6][0] = 255;
	dataSet[6][1] = 128;
	dataSet[6][2] = 0;

	dataSet[7][0] = 255;
	dataSet[7][1] = 0;
	dataSet[7][2] = 128;

	dataSet[8][0] = 128;
	dataSet[8][1] = 255;
	dataSet[8][2] = 0;

	dataSet[9][0] = 0;
	dataSet[9][1] = 255;
	dataSet[9][2] = 128;

	dataSet[10][0] = 128;
	dataSet[10][1] = 0;
	dataSet[10][2] = 255;

	dataSet[11][0] = 0;
	dataSet[11][1] = 128;
	dataSet[11][2] = 255;

	  // Bright
	dataSet[12][0] = 192;
	dataSet[12][1] = 0;
	dataSet[12][2] = 0;

	dataSet[13][0] = 0;
	dataSet[13][1] = 192;
	dataSet[13][2] = 0;

	dataSet[14][0] = 0;
	dataSet[14][1] = 0;
	dataSet[14][2] = 192;

	dataSet[15][0] = 192;
	dataSet[15][1] = 192;
	dataSet[15][2] = 0;

	dataSet[16][0] = 192;
	dataSet[16][1] = 0;
	dataSet[16][2] = 192;

	dataSet[17][0] = 0;
	dataSet[17][1] = 192;
	dataSet[17][2] = 192;

	dataSet[18][0] = 192;
	dataSet[18][1] = 92;
	dataSet[18][2] = 0;

	dataSet[19][0] = 192;
	dataSet[19][1] = 0;
	dataSet[19][2] = 92;

	dataSet[20][0] = 92;
	dataSet[20][1] = 192;
	dataSet[20][2] = 0;

	dataSet[21][0] = 0;
	dataSet[21][1] = 192;
	dataSet[21][2] = 92;

	dataSet[22][0] = 92;
	dataSet[22][1] = 0;
	dataSet[22][2] = 192;

	dataSet[23][0] = 0;
	dataSet[23][1] = 92;
	dataSet[23][2] = 192;

	  // Medium
	dataSet[24][0] = 128;
	dataSet[24][1] = 0;
	dataSet[24][2] = 0;

	dataSet[25][0] = 0;
	dataSet[25][1] = 128;
	dataSet[25][2] = 0;

	dataSet[26][0] = 0;
	dataSet[26][1] = 0;
	dataSet[26][2] = 128;

	dataSet[27][0] = 128;
	dataSet[27][1] = 128;
	dataSet[27][2] = 0;

	dataSet[28][0] = 128;
	dataSet[28][1] = 0;
	dataSet[28][2] = 128;

	dataSet[29][0] = 0;
	dataSet[29][1] = 128;
	dataSet[29][2] = 128;

	dataSet[30][0] = 128;
	dataSet[30][1] = 64;
	dataSet[30][2] = 0;

	dataSet[31][0] = 128;
	dataSet[31][1] = 0;
	dataSet[31][2] = 64;

	dataSet[32][0] = 64;
	dataSet[32][1] = 128;
	dataSet[32][2] = 0;

	dataSet[33][0] = 0;
	dataSet[33][1] = 128;
	dataSet[33][2] = 64;

	dataSet[34][0] = 64;
	dataSet[34][1] = 0;
	dataSet[34][2] = 128;

	dataSet[35][0] = 0;
	dataSet[35][1] = 64;
	dataSet[35][2] = 128;

	  // Dark
	dataSet[36][0] = 64;
	dataSet[36][1] = 0;
	dataSet[36][2] = 0;

	dataSet[37][0] = 0;
	dataSet[37][1] = 64;
	dataSet[37][2] = 0;

	dataSet[38][0] = 0;
	dataSet[38][1] = 0;
	dataSet[38][2] = 64;

	dataSet[39][0] = 64;
	dataSet[39][1] = 64;
	dataSet[39][2] = 0;

	dataSet[40][0] = 64;
	dataSet[40][1] = 0;
	dataSet[40][2] = 64;

	dataSet[41][0] = 0;
	dataSet[41][1] = 64;
	dataSet[41][2] = 64;

	dataSet[42][0] = 64;
	dataSet[42][1] = 32;
	dataSet[42][2] = 0;

	dataSet[43][0] = 64;
	dataSet[43][1] = 0;
	dataSet[43][2] = 32;

	dataSet[44][0] = 32;
	dataSet[44][1] = 64;
	dataSet[44][2] = 0;

	dataSet[45][0] = 0;
	dataSet[45][1] = 64;
	dataSet[45][2] = 32;

	dataSet[46][0] = 32;
	dataSet[46][1] = 0;
	dataSet[46][2] = 64;

	dataSet[47][0] = 0;
	dataSet[47][1] = 32;
	dataSet[47][2] = 64;

	return dataSet;
}

vector<vector<double> > Utils::createColorTestDataSet(){
	vector<vector<double> > dataSet;
	dataSet.resize(4);
	
	for(int i=0; i<4; i++){
		dataSet[i].resize(3);
	}

	// Azul
	dataSet[0][0] = 0;
	dataSet[0][1] = 0;
	dataSet[0][2] = 255;

	// Rojo
	dataSet[1][0] = 255;
	dataSet[1][1] = 0;
	dataSet[1][2] = 0;
	
	// Violeta
	dataSet[2][0] = 204;
	dataSet[2][1] = 0;
	dataSet[2][2] = 204;
	
	// Verde
	dataSet[3][0] = 0;
	dataSet[3][1] = 255;
	dataSet[3][2] = 0;

	return dataSet;
}

string Utils::currentTime(){
	time_t now = time(0);
	struct tm tstruct;
	char buf[80];
	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), "%H:%M:%S", &tstruct);
	return buf;
}

string Utils::currentDate(){
	time_t now = time(0);
	struct tm tstruct;
	char buf[80];
	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), "%B %A ", &tstruct);
	return buf;
}

string Utils::buildFileName(){
	time_t t = time(0);
	struct tm * now = localtime( & t );
	int month = (now->tm_mon + 1);
    int day = (now->tm_mday  + 1);
    int year = (now->tm_year + 1900);
    string fileName = to_string(year) + "." + to_string(month) + "." +
		to_string(day) + "-" + Utils::currentTime() + ".txt";
	return fileName;
}