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

SelfOrganizingMaps* Utils::importMatrixFromFile(char *fileName){
    std::ifstream infile(fileName);
    string line;
    vector<double> neuronRGB;
    getline(infile,line);
    int size = atoi(line.c_str());
    getline(infile,line);
    int executedEpochs = atoi(line.c_str());
    getline(infile,line);
    int maxEpochs = atoi(line.c_str());
    getline(infile,line);
    double initialLearningRate = atof(line.c_str());
    getline(infile,line);
    double currentLearningRate = atof(line.c_str());
    getline(infile,line);
    int totalWeights = atoi(line.c_str());
    neuronRGB.resize(totalWeights);
    SelfOrganizingMaps *som = new SelfOrganizingMaps(size, totalWeights,
		maxEpochs, initialLearningRate, 0, false);
	for(int row=0; row<size; row++){ // For every row
		getline(infile,line);
        stringstream ssin(line);
        for(int col=0; col<size; col++){ // for each column
			// Get all the weights of the neuron in (row, col)
            for(int weigths=0; weigths<totalWeights; weigths++){
				ssin >> neuronRGB[weigths];
            }
            RGB *rgb = new RGB(neuronRGB[0], neuronRGB[1], neuronRGB[2]);
            som->setNeuron(new Neuron(row, col, totalWeights, rgb));
        }
    }
    return som;
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

vector<RGB* > Utils::createBlueColorBuildMatrixDataSet(){
	vector<RGB* > colorDataSet;
	colorDataSet.resize(36);

	colorDataSet[0] = new RGB((9/(double)255),(28/(double)255),(87/(double)255));
	colorDataSet[1] = new RGB((24/(double)255),(41/(double)255),(88/(double)255));
	colorDataSet[2] = new RGB((40/(double)255),(62/(double)255),(102/(double)255));
	colorDataSet[3] = new RGB((60/(double)255),(92/(double)255),(126/(double)255));
	colorDataSet[4] = new RGB((78/(double)255),(111/(double)255),(135/(double)255));
	colorDataSet[5] = new RGB((96/(double)255),(124/(double)255),(141/(double)255));
	colorDataSet[6] = new RGB((123/(double)255),(156/(double)255),(169/(double)255));
	colorDataSet[7] = new RGB((143/(double)255),(172/(double)255),(180/(double)255));
	colorDataSet[8] = new RGB((174/(double)255),(194/(double)255),(198/(double)255));
	colorDataSet[9] = new RGB((8/(double)255),(96/(double)255),(168/(double)255));
	colorDataSet[10] = new RGB((45/(double)255),(114/(double)255),(178/(double)255));
	colorDataSet[11] = new RGB((80/(double)255),(133/(double)255),(188/(double)255));
	colorDataSet[12] = new RGB((104/(double)255),(149/(double)255),(197/(double)255));
	colorDataSet[13] = new RGB((128/(double)255),(166/(double)255),(206/(double)255));
	colorDataSet[14] = new RGB((166/(double)255),(189/(double)255),(219/(double)255));
	colorDataSet[15] = new RGB((191/(double)255),(209/(double)255),(229/(double)255));
	colorDataSet[16] = new RGB((217/(double)255),(229/(double)255),(240/(double)255));
	colorDataSet[17] = new RGB((242/(double)255),(242/(double)255),(248/(double)255));
	colorDataSet[18] = new RGB((7/(double)255),(87/(double)255),(152/(double)255));
	colorDataSet[19] = new RGB((40/(double)255),(103/(double)255),(160/(double)255));
	colorDataSet[20] = new RGB((72/(double)255),(120/(double)255),(170/(double)255));
	colorDataSet[21] = new RGB((99/(double)255),(141/(double)255),(187/(double)255));
	colorDataSet[22] = new RGB((121/(double)255),(158/(double)255),(196/(double)255));
	colorDataSet[23] = new RGB((157/(double)255),(179/(double)255),(208/(double)255));
	colorDataSet[24] = new RGB((185/(double)255),(202/(double)255),(222/(double)255));
	colorDataSet[25] = new RGB((210/(double)255),(221/(double)255),(233/(double)255));
	colorDataSet[26] = new RGB((234/(double)255),(235/(double)255),(240/(double)255));
	colorDataSet[27] = new RGB((6/(double)255),(77/(double)255),(135/(double)255));
	colorDataSet[28] = new RGB((36/(double)255),(91/(double)255),(142/(double)255));
	colorDataSet[29] = new RGB((64/(double)255),(106/(double)255),(151/(double)255));
	colorDataSet[30] = new RGB((88/(double)255),(127/(double)255),(167/(double)255));
	colorDataSet[31] = new RGB((109/(double)255),(141/(double)255),(175/(double)255));
	colorDataSet[32] = new RGB((141/(double)255),(161/(double)255),(186/(double)255));
	colorDataSet[33] = new RGB((172/(double)255),(188/(double)255),(207/(double)255));
	colorDataSet[34] = new RGB((195/(double)255),(206/(double)255),(217/(double)255));
	colorDataSet[35] = new RGB((218/(double)255),(219/(double)255),(224/(double)255));

	return colorDataSet;
}

vector<RGB* > Utils::createRedColorBuildMatrixDataSet(){
	vector<RGB* > colorDataSet;
	colorDataSet.resize(36);
	
	colorDataSet[0] = new RGB((230/(double)255),(0/(double)255),(0/(double)255));
	colorDataSet[1] = new RGB((228/(double)255),(160/(double)255),(136/(double)255));
	colorDataSet[2] = new RGB((205/(double)255),(78/(double)255),(55/(double)255));
	colorDataSet[3] = new RGB((161/(double)255),(0/(double)255),(0/(double)255));
	colorDataSet[4] = new RGB((182/(double)255),(128/(double)255),(109/(double)255));
	colorDataSet[5] = new RGB((202/(double)255),(82/(double)255),(61/(double)255));
	colorDataSet[6] = new RGB((229/(double)255),(38/(double)255),(23/(double)255));
	colorDataSet[7] = new RGB((228/(double)255),(184/(double)255),(165/(double)255));
	colorDataSet[8] = new RGB((205/(double)255),(100/(double)255),(75/(double)255));
	colorDataSet[9] = new RGB((160/(double)255),(27/(double)255),(16/(double)255));
	colorDataSet[10] = new RGB((182/(double)255),(147/(double)255),(132/(double)255));
	colorDataSet[11] = new RGB((202/(double)255),(106/(double)255),(84/(double)255));
	colorDataSet[12] = new RGB((228/(double)255),(63/(double)255),(41/(double)255));
	colorDataSet[13] = new RGB((229/(double)255),(209/(double)255),(197/(double)255));
	colorDataSet[14] = new RGB((205/(double)255),(122/(double)255),(97/(double)255));
	colorDataSet[15] = new RGB((160/(double)255),(44/(double)255),(29/(double)255));
	colorDataSet[16] = new RGB((195/(double)255),(178/(double)255),(168/(double)255));
	colorDataSet[17] = new RGB((202/(double)255),(129/(double)255),(107/(double)255));
	colorDataSet[18] = new RGB((228/(double)255),(86/(double)255),(60/(double)255));
	colorDataSet[19] = new RGB((196/(double)255),(0/(double)255),(0/(double)255));
	colorDataSet[20] = new RGB((216/(double)255),(152/(double)255),(129/(double)255));
	colorDataSet[21] = new RGB((170/(double)255),(65/(double)255),(45/(double)255));
	colorDataSet[22] = new RGB((204/(double)255),(0/(double)255),(0/(double)255));
	colorDataSet[23] = new RGB((202/(double)255),(153/(double)255),(134/(double)255));
	colorDataSet[24] = new RGB((227/(double)255),(111/(double)255),(83/(double)255));
	colorDataSet[25] = new RGB((194/(double)255),(32/(double)255),(19/(double)255));
	colorDataSet[26] = new RGB((216/(double)255),(175/(double)255),(156/(double)255));
	colorDataSet[27] = new RGB((170/(double)255),(83/(double)255),(62/(double)255));
	colorDataSet[28] = new RGB((203/(double)255),(36/(double)255),(23/(double)255));
	colorDataSet[29] = new RGB((203/(double)255),(176/(double)255),(153/(double)255));
	colorDataSet[30] = new RGB((227/(double)255),(135/(double)255),(108/(double)255));
	colorDataSet[31] = new RGB((194/(double)255),(53/(double)255),(35/(double)255));
	colorDataSet[32] = new RGB((217/(double)255),(198/(double)255),(187/(double)255));
	colorDataSet[33] = new RGB((170/(double)255),(101/(double)255),(81/(double)255));
	colorDataSet[34] = new RGB((203/(double)255),(59/(double)255),(41/(double)255));
	colorDataSet[35] = new RGB((203/(double)255),(188/(double)255),(167/(double)255));
	
	return colorDataSet;	
}

vector<RGB* > Utils::createGreenColorBuildMatrixDataSet(){
	vector<RGB* > colorDataSet;
	colorDataSet.resize(36);
	
	colorDataSet[0] = new RGB((0/(double)255),(82/(double)255),(33/(double)255));
	colorDataSet[1] = new RGB((125/(double)255),(164/(double)255),(120/(double)255));
	colorDataSet[2] = new RGB((115/(double)255),(195/(double)255),(108/(double)255));
	colorDataSet[3] = new RGB((24/(double)255),(134/(double)255),(45/(double)255));
	colorDataSet[4] = new RGB((174/(double)255),(217/(double)255),(167/(double)255));
	colorDataSet[5] = new RGB((98/(double)255),(166/(double)255),(92/(double)255));
	colorDataSet[6] = new RGB((26/(double)255),(102/(double)255),(46/(double)255));
	colorDataSet[7] = new RGB((153/(double)255),(184/(double)255),(147/(double)255));
	colorDataSet[8] = new RGB((140/(double)255),(207/(double)255),(127/(double)255));
	colorDataSet[9] = new RGB((58/(double)255),(153/(double)255),(68/(double)255));
	colorDataSet[10] = new RGB((198/(double)255),(228/(double)255),(191/(double)255));
	colorDataSet[11] = new RGB((119/(double)255),(176/(double)255),(108/(double)255));
	colorDataSet[12] = new RGB((42/(double)255),(111/(double)255),(55/(double)255));
	colorDataSet[13] = new RGB((185/(double)255),(204/(double)255),(179/(double)255));
	colorDataSet[14] = new RGB((166/(double)255),(218/(double)255),(149/(double)255));
	colorDataSet[15] = new RGB((81/(double)255),(164/(double)255),(82/(double)255));
	colorDataSet[16] = new RGB((223/(double)255),(238/(double)255),(218/(double)255));
	colorDataSet[17] = new RGB((141/(double)255),(186/(double)255),(127/(double)255));
	colorDataSet[18] = new RGB((63/(double)255),(128/(double)255),(70/(double)255));
	colorDataSet[19] = new RGB((26/(double)255),(148/(double)255),(49/(double)255));
	colorDataSet[20] = new RGB((179/(double)255),(225/(double)255),(172/(double)255));
	colorDataSet[21] = new RGB((109/(double)255),(185/(double)255),(102/(double)255));
	colorDataSet[22] = new RGB((21/(double)255),(119/(double)255),(40/(double)255));
	colorDataSet[23] = new RGB((162/(double)255),(203/(double)255),(155/(double)255));
	colorDataSet[24] = new RGB((81/(double)255),(137/(double)255),(82/(double)255));
	colorDataSet[25] = new RGB((65/(double)255),(169/(double)255),(76/(double)255));
	colorDataSet[26] = new RGB((204/(double)255),(235/(double)255),(197/(double)255));
	colorDataSet[27] = new RGB((133/(double)255),(196/(double)255),(120/(double)255));
	colorDataSet[28] = new RGB((52/(double)255),(136/(double)255),(60/(double)255));
	colorDataSet[29] = new RGB((184/(double)255),(212/(double)255),(178/(double)255));
	colorDataSet[30] = new RGB((105/(double)255),(155/(double)255),(103/(double)255));
	colorDataSet[31] = new RGB((89/(double)255),(182/(double)255),(91/(double)255));
	colorDataSet[32] = new RGB((230/(double)255),(245/(double)255),(226/(double)255));
	colorDataSet[33] = new RGB((158/(double)255),(207/(double)255),(141/(double)255));
	colorDataSet[34] = new RGB((72/(double)255),(146/(double)255),(73/(double)255));
	colorDataSet[35] = new RGB((208/(double)255),(221/(double)255),(203/(double)255));
	
	return colorDataSet;
}

vector<RGB* > Utils::createYellowColorBuildMatrixDataSet(){
	vector<RGB* > colorDataSet;
	colorDataSet.resize(36);
	
	colorDataSet[0] = new RGB((255/(double)255),(242/(double)255),(0/(double)255));
	colorDataSet[1] = new RGB((255/(double)255),(255/(double)255),(153/(double)255));
	colorDataSet[2] = new RGB((242/(double)255),(242/(double)255),(37/(double)255));
	colorDataSet[3] = new RGB((204/(double)255),(194/(double)255),(0/(double)255));
	colorDataSet[4] = new RGB((230/(double)255),(230/(double)255),(138/(double)255));
	colorDataSet[5] = new RGB((179/(double)255),(179/(double)255),(28/(double)255));
	colorDataSet[6] = new RGB((255/(double)255),(247/(double)255),(0/(double)255));
	colorDataSet[7] = new RGB((255/(double)255),(255/(double)255),(191/(double)255));
	colorDataSet[8] = new RGB((242/(double)255),(242/(double)255),(73/(double)255));
	colorDataSet[9] = new RGB((204/(double)255),(198/(double)255),(0/(double)255));
	colorDataSet[10] = new RGB((230/(double)255),(230/(double)255),(172/(double)255));
	colorDataSet[11] = new RGB((179/(double)255),(179/(double)255),(54/(double)255));
	colorDataSet[12] = new RGB((255/(double)255),(255/(double)255),(0/(double)255));
	colorDataSet[13] = new RGB((255/(double)255),(255/(double)255),(230/(double)255));
	colorDataSet[14] = new RGB((242/(double)255),(242/(double)255),(109/(double)255));
	colorDataSet[15] = new RGB((204/(double)255),(204/(double)255),(0/(double)255));
	colorDataSet[16] = new RGB((230/(double)255),(230/(double)255),(207/(double)255));
	colorDataSet[17] = new RGB((191/(double)255),(191/(double)255),(86/(double)255));
	colorDataSet[18] = new RGB((255/(double)255),(255/(double)255),(39/(double)255));
	colorDataSet[19] = new RGB((255/(double)255),(218/(double)255),(0/(double)255));
	colorDataSet[20] = new RGB((255/(double)255),(232/(double)255),(52/(double)255));
	colorDataSet[21] = new RGB((217/(double)255),(217/(double)255),(33/(double)255));
	colorDataSet[22] = new RGB((153/(double)255),(145/(double)255),(0/(double)255));
	colorDataSet[23] = new RGB((191/(double)255),(191/(double)255),(115/(double)255));
	colorDataSet[24] = new RGB((255/(double)255),(255/(double)255),(77/(double)255));
	colorDataSet[25] = new RGB((230/(double)255),(223/(double)255),(0/(double)255));
	colorDataSet[26] = new RGB((247/(double)255),(247/(double)255),(185/(double)255));
	colorDataSet[27] = new RGB((217/(double)255),(217/(double)255),(66/(double)255));
	colorDataSet[28] = new RGB((166/(double)255),(161/(double)255),(0/(double)255));
	colorDataSet[29] = new RGB((204/(double)255),(204/(double)255),(153/(double)255));
	colorDataSet[30] = new RGB((255/(double)255),(255/(double)255),(115/(double)255));
	colorDataSet[31] = new RGB((186/(double)255),(165/(double)255),(0/(double)255));
	colorDataSet[32] = new RGB((247/(double)255),(247/(double)255),(223/(double)255));
	colorDataSet[33] = new RGB((217/(double)255),(217/(double)255),(98/(double)255));
	colorDataSet[34] = new RGB((166/(double)255),(166/(double)255),(0/(double)255));
	colorDataSet[35] = new RGB((217/(double)255),(217/(double)255),(196/(double)255));
	
	return colorDataSet;
}

vector<RGB* > Utils::createBlueColorTrainMatrixDataSet(){
	vector<RGB* > colorDataSet;
	colorDataSet.resize(26);

	colorDataSet[0] = new RGB((24/(double)255),(48/(double)255),(100/(double)255));
	colorDataSet[1] = new RGB((35/(double)255),(77/(double)255),(160/(double)255));
	colorDataSet[2] = new RGB((10/(double)255),(80/(double)255),(161/(double)255));
	colorDataSet[3] = new RGB((5/(double)255),(113/(double)255),(176/(double)255));
	colorDataSet[4] = new RGB((37/(double)255),(52/(double)255),(148/(double)255));
	colorDataSet[5] = new RGB((30/(double)255),(135/(double)255),(180/(double)255));
	colorDataSet[6] = new RGB((1/(double)255),(155/(double)255),(196/(double)255));
	colorDataSet[7] = new RGB((1/(double)255),(159/(double)255),(191/(double)255));
	colorDataSet[8] = new RGB((0/(double)255),(158/(double)255),(187/(double)255));
	colorDataSet[9] = new RGB((128/(double)255),(206/(double)255),(207/(double)255));
	colorDataSet[10] = new RGB((0/(double)255),(153/(double)255),(155/(double)255));
	colorDataSet[11] = new RGB((118/(double)255),(42/(double)255),(145/(double)255));
	colorDataSet[12] = new RGB((72/(double)255),(48/(double)255),(147/(double)255));
	colorDataSet[13] = new RGB((84/(double)255),(39/(double)255),(143/(double)255));
	colorDataSet[14] = new RGB((85/(double)255),(30/(double)255),(138/(double)255));
	colorDataSet[15] = new RGB((40/(double)255),(162/(double)255),(102/(double)255));
	colorDataSet[16] = new RGB((31/(double)255),(120/(double)255),(180/(double)255));
	colorDataSet[17] = new RGB((29/(double)255),(143/(double)255),(177/(double)255));
	colorDataSet[18] = new RGB((217/(double)255),(240/(double)255),(220/(double)255));
	colorDataSet[19] = new RGB((217/(double)255),(241/(double)255),(232/(double)255));
	colorDataSet[20] = new RGB((179/(double)255),(226/(double)255),(218/(double)255));
	colorDataSet[21] = new RGB((146/(double)255),(213/(double)255),(208/(double)255));
	colorDataSet[22] = new RGB((106/(double)255),(188/(double)255),(190/(double)255));
	colorDataSet[23] = new RGB((56/(double)255),(160/(double)255),(166/(double)255));
	colorDataSet[24] = new RGB((18/(double)255),(121/(double)255),(131/(double)255));
	colorDataSet[25] = new RGB((0/(double)255),(83/(double)255),(98/(double)255));

	return colorDataSet;
}

vector<RGB* > Utils::createRedColorTrainMatrixDataSet(){
	vector<RGB* > colorDataSet;
	colorDataSet.resize(23);

	colorDataSet[0] = new RGB((255/(double)255),(140/(double)255),(0/(double)255));
	colorDataSet[1] = new RGB((255/(double)255),(127/(double)255),(0/(double)255));
	colorDataSet[2] = new RGB((254/(double)255),(90/(double)255),(18/(double)255));
	colorDataSet[3] = new RGB((255/(double)255),(166/(double)255),(137/(double)255));
	colorDataSet[4] = new RGB((254/(double)255),(77/(double)255),(17/(double)255));
	colorDataSet[5] = new RGB((254/(double)255),(27/(double)255),(28/(double)255));
	colorDataSet[6] = new RGB((255/(double)255),(40/(double)255),(37/(double)255));
	colorDataSet[7] = new RGB((250/(double)255),(0/(double)255),(38/(double)255));
	colorDataSet[8] = new RGB((228/(double)255),(0/(double)255),(25/(double)255));
	colorDataSet[9] = new RGB((225/(double)255),(0/(double)255),(51/(double)255));
	colorDataSet[10] = new RGB((180/(double)255),(0/(double)255),(51/(double)255));
	colorDataSet[11] = new RGB((249/(double)255),(129/(double)255),(162/(double)255));
	colorDataSet[12] = new RGB((251/(double)255),(52/(double)255),(46/(double)255));
	colorDataSet[13] = new RGB((251/(double)255),(18/(double)255),(34/(double)255));
	colorDataSet[14] = new RGB((246/(double)255),(29/(double)255),(98/(double)255));
	colorDataSet[15] = new RGB((243/(double)255),(1/(double)255),(102/(double)255));
	colorDataSet[16] = new RGB((229/(double)255),(2/(double)255),(127/(double)255));
	colorDataSet[17] = new RGB((223/(double)255),(2/(double)255),(127/(double)255));
	colorDataSet[18] = new RGB((210/(double)255),(1/(double)255),(89/(double)255));
	colorDataSet[19] = new RGB((163/(double)255),(25/(double)255),(137/(double)255));
	colorDataSet[20] = new RGB((203/(double)255),(19/(double)255),(133/(double)255));
	colorDataSet[21] = new RGB((226/(double)255),(29/(double)255),(139/(double)255));
	colorDataSet[22] = new RGB((152/(double)255),(25/(double)255),(137/(double)255));

	return colorDataSet;
}

vector<RGB* > Utils::createGreenColorTrainMatrixDataSet(){
	vector<RGB* > colorDataSet;
	colorDataSet.resize(24);

	colorDataSet[0] = new RGB((0/(double)255),(153/(double)255),(155/(double)255));
	colorDataSet[1] = new RGB((1/(double)255),(149/(double)255),(133/(double)255));
	colorDataSet[2] = new RGB((57/(double)255),(170/(double)255),(135/(double)255));
	colorDataSet[3] = new RGB((40/(double)255),(161/(double)255),(103/(double)255));
	colorDataSet[4] = new RGB((1/(double)255),(144/(double)255),(105/(double)255));
	colorDataSet[5] = new RGB((1/(double)255),(117/(double)255),(96/(double)255));
	colorDataSet[6] = new RGB((51/(double)255),(166/(double)255),(94/(double)255));
	colorDataSet[7] = new RGB((32/(double)255),(125/(double)255),(57/(double)255));
	colorDataSet[8] = new RGB((0/(double)255),(150/(double)255),(141/(double)255));
	colorDataSet[9] = new RGB((102/(double)255),(185/(double)255),(52/(double)255));
	colorDataSet[10] = new RGB((66/(double)255),(120/(double)255),(34/(double)255));
	colorDataSet[11] = new RGB((150/(double)255),(159/(double)255),(51/(double)255));
	colorDataSet[12] = new RGB((104/(double)255),(172/(double)255),(45/(double)255));
	colorDataSet[13] = new RGB((89/(double)255),(181/(double)255),(72/(double)255));
	colorDataSet[14] = new RGB((140/(double)255),(204/(double)255),(76/(double)255));
	colorDataSet[15] = new RGB((153/(double)255),(208/(double)255),(44/(double)255));
	colorDataSet[16] = new RGB((153/(double)255),(207/(double)255),(22/(double)255));
	colorDataSet[17] = new RGB((204/(double)255),(215/(double)255),(10/(double)255));
	colorDataSet[18] = new RGB((186/(double)255),(228/(double)255),(188/(double)255));
	colorDataSet[19] = new RGB((153/(double)255),(201/(double)255),(169/(double)255));
	colorDataSet[20] = new RGB((111/(double)255),(169/(double)255),(204/(double)255));
	colorDataSet[21] = new RGB((74/(double)255),(129/(double)255),(87/(double)255));
	colorDataSet[22] = new RGB((19/(double)255),(53/(double)255),(34/(double)255));
	colorDataSet[23] = new RGB((8/(double)255),(21/(double)255),(17/(double)255));

	return colorDataSet;
}

vector<RGB* > Utils::createYellowColorTrainMatrixDataSet(){
	vector<RGB* > colorDataSet;
	colorDataSet.resize(36);

	colorDataSet[0] = new RGB((230/(double)255),(243/(double)255),(4/(double)255));
	colorDataSet[1] = new RGB((255/(double)255),(191/(double)255),(0/(double)255));
	colorDataSet[2] = new RGB((250/(double)255),(175/(double)255),(0/(double)255));
	colorDataSet[3] = new RGB((204/(double)255),(139/(double)255),(6/(double)255));
	colorDataSet[4] = new RGB((191/(double)255),(134/(double)255),(0/(double)255));
	colorDataSet[5] = new RGB((161/(double)255),(120/(double)255),(32/(double)255));
	colorDataSet[6] = new RGB((114/(double)255),(73/(double)255),(32/(double)255));
	colorDataSet[7] = new RGB((127/(double)255),(63/(double)255),(10/(double)255));
	colorDataSet[8] = new RGB((255/(double)255),(242/(double)255),(99/(double)255));
	colorDataSet[9] = new RGB((247/(double)255),(25/(double)255),(1/(double)255));
	colorDataSet[10] = new RGB((255/(double)255),(255/(double)255),(0/(double)255));
	colorDataSet[11] = new RGB((255/(double)255),(235/(double)255),(0/(double)255));
	colorDataSet[12] = new RGB((255/(double)255),(217/(double)255),(0/(double)255));
	colorDataSet[13] = new RGB((255/(double)255),(179/(double)255),(0/(double)255));
	colorDataSet[14] = new RGB((240/(double)255),(249/(double)255),(145/(double)255));
	colorDataSet[15] = new RGB((255/(double)255),(255/(double)255),(227/(double)255));
	colorDataSet[16] = new RGB((255/(double)255),(255/(double)255),(179/(double)255));
	colorDataSet[17] = new RGB((255/(double)255),(255/(double)255),(125/(double)255));
	colorDataSet[18] = new RGB((255/(double)255),(255/(double)255),(79/(double)255));
	colorDataSet[19] = new RGB((255/(double)255),(255/(double)255),(34/(double)255));
	colorDataSet[20] = new RGB((240/(double)255),(240/(double)255),(0/(double)255));
	colorDataSet[21] = new RGB((232/(double)255),(232/(double)255),(0/(double)255));
	colorDataSet[22] = new RGB((255/(double)255),(255/(double)255),(227/(double)255));
	colorDataSet[23] = new RGB((255/(double)255),(255/(double)255),(179/(double)255));
	colorDataSet[24] = new RGB((240/(double)255),(240/(double)255),(118/(double)255));
	colorDataSet[25] = new RGB((232/(double)255),(232/(double)255),(72/(double)255));
	colorDataSet[26] = new RGB((227/(double)255),(227/(double)255),(17/(double)255));
	colorDataSet[27] = new RGB((209/(double)255),(209/(double)255),(0/(double)255));
	colorDataSet[28] = new RGB((179/(double)255),(179/(double)255),(0/(double)255));
	colorDataSet[29] = new RGB((240/(double)255),(240/(double)255),(204/(double)255));
	colorDataSet[30] = new RGB((240/(double)255),(240/(double)255),(175/(double)255));
	colorDataSet[31] = new RGB((232/(double)255),(232/(double)255),(153/(double)255));
	colorDataSet[32] = new RGB((209/(double)255),(209/(double)255),(111/(double)255));
	colorDataSet[33] = new RGB((168/(double)255),(168/(double)255),(16/(double)255));
	colorDataSet[34] = new RGB((135/(double)255),(135/(double)255),(0/(double)255));
	colorDataSet[35] = new RGB((112/(double)255),(105/(double)255),(0/(double)255));

	return colorDataSet;
}

vector<RGB* > Utils::createMultipleColorBuildMatrixDataSet(){
	vector<RGB*> multipleColors;
	vector<RGB*> redColors = Utils::createRedColorBuildMatrixDataSet();
	vector<RGB*> greenColors = Utils::createGreenColorBuildMatrixDataSet();
	vector<RGB*> blueColors = Utils::createBlueColorBuildMatrixDataSet();
	vector<RGB*> yellowColors = Utils::createYellowColorBuildMatrixDataSet();
	int multipleColorsSize = redColors.size() + greenColors.size() +
		blueColors.size() + yellowColors.size();
	multipleColors.resize(multipleColorsSize);
	int multipleColorsIndex = 0;

	// Red
	for(int colorIndex=0; colorIndex<redColors.size(); colorIndex++, multipleColorsIndex++){
		multipleColors[multipleColorsIndex] = redColors[colorIndex];
	}

	// Green
	for(int colorIndex=0; colorIndex<greenColors.size(); colorIndex++, multipleColorsIndex++){
		multipleColors[multipleColorsIndex] = greenColors[colorIndex];
	}

	// Blue
	for(int colorIndex=0; colorIndex<blueColors.size(); colorIndex++, multipleColorsIndex++){
		multipleColors[multipleColorsIndex] = blueColors[colorIndex];
	}

	// Yellow
	for(int colorIndex=0; colorIndex<yellowColors.size(); colorIndex++, multipleColorsIndex++){
		multipleColors[multipleColorsIndex] = yellowColors[colorIndex];
	}

	return multipleColors;
}

vector<RGB* > Utils::createMultipleColorTrainMatrixDataSet(){
		vector<RGB*> multipleColors;
	vector<RGB*> redColors = Utils::createRedColorTrainMatrixDataSet();
	vector<RGB*> greenColors = Utils::createGreenColorTrainMatrixDataSet();
	vector<RGB*> blueColors = Utils::createBlueColorTrainMatrixDataSet();
	vector<RGB*> yellowColors = Utils::createYellowColorTrainMatrixDataSet();
	int multipleColorsSize = redColors.size() + greenColors.size() +
		blueColors.size() + yellowColors.size();
	multipleColors.resize(multipleColorsSize);
	int multipleColorsIndex = 0;

	// Red
	for(int colorIndex=0; colorIndex<redColors.size(); colorIndex++, multipleColorsIndex++){
		multipleColors[multipleColorsIndex] = redColors[colorIndex];
	}

	// Green
	for(int colorIndex=0; colorIndex<greenColors.size(); colorIndex++, multipleColorsIndex++){
		multipleColors[multipleColorsIndex] = greenColors[colorIndex];
	}

	// Blue
	for(int colorIndex=0; colorIndex<blueColors.size(); colorIndex++, multipleColorsIndex++){
		multipleColors[multipleColorsIndex] = blueColors[colorIndex];
	}

	// Yellow
	for(int colorIndex=0; colorIndex<yellowColors.size(); colorIndex++, multipleColorsIndex++){
		multipleColors[multipleColorsIndex] = yellowColors[colorIndex];
	}

	return multipleColors;
}

/*
vector<RGB* > Utils::createColorDataSet(){
	vector<RGB* > colorDataSet;
	colorDataSet.resize(36);

	colorDataSet[0] = new RGB((/(double)255),(/(double)255),(/(double)255));
	colorDataSet[1] = new RGB((/(double)255),(/(double)255),(/(double)255));
	colorDataSet[2] = new RGB((/(double)255),(/(double)255),(/(double)255));
	colorDataSet[3] = new RGB((/(double)255),(/(double)255),(/(double)255));
	colorDataSet[4] = new RGB((/(double)255),(/(double)255),(/(double)255));
	colorDataSet[5] = new RGB((/(double)255),(/(double)255),(/(double)255));
	colorDataSet[6] = new RGB((/(double)255),(/(double)255),(/(double)255));
	colorDataSet[7] = new RGB((/(double)255),(/(double)255),(/(double)255));
	colorDataSet[8] = new RGB((/(double)255),(/(double)255),(/(double)255));
	colorDataSet[9] = new RGB((/(double)255),(/(double)255),(/(double)255));
	colorDataSet[10] = new RGB((/(double)255),(/(double)255),(/(double)255));
	colorDataSet[11] = new RGB((/(double)255),(/(double)255),(/(double)255));
	colorDataSet[12] = new RGB((/(double)255),(/(double)255),(/(double)255));
	colorDataSet[13] = new RGB((/(double)255),(/(double)255),(/(double)255));
	colorDataSet[14] = new RGB((/(double)255),(/(double)255),(/(double)255));
	colorDataSet[15] = new RGB((/(double)255),(/(double)255),(/(double)255));
	colorDataSet[16] = new RGB((/(double)255),(/(double)255),(/(double)255));
	colorDataSet[17] = new RGB((/(double)255),(/(double)255),(/(double)255));
	colorDataSet[18] = new RGB((/(double)255),(/(double)255),(/(double)255));
	colorDataSet[19] = new RGB((/(double)255),(/(double)255),(/(double)255));
	colorDataSet[20] = new RGB((/(double)255),(/(double)255),(/(double)255));
	colorDataSet[21] = new RGB((/(double)255),(/(double)255),(/(double)255));
	colorDataSet[22] = new RGB((/(double)255),(/(double)255),(/(double)255));
	colorDataSet[23] = new RGB((/(double)255),(/(double)255),(/(double)255));
	colorDataSet[24] = new RGB((/(double)255),(/(double)255),(/(double)255));
	colorDataSet[25] = new RGB((/(double)255),(/(double)255),(/(double)255));
	colorDataSet[26] = new RGB((/(double)255),(/(double)255),(/(double)255));
	colorDataSet[27] = new RGB((/(double)255),(/(double)255),(/(double)255));
	colorDataSet[28] = new RGB((/(double)255),(/(double)255),(/(double)255));
	colorDataSet[29] = new RGB((/(double)255),(/(double)255),(/(double)255));
	colorDataSet[30] = new RGB((/(double)255),(/(double)255),(/(double)255));
	colorDataSet[31] = new RGB((/(double)255),(/(double)255),(/(double)255));
	colorDataSet[32] = new RGB((/(double)255),(/(double)255),(/(double)255));
	colorDataSet[33] = new RGB((/(double)255),(/(double)255),(/(double)255));
	colorDataSet[34] = new RGB((/(double)255),(/(double)255),(/(double)255));
	colorDataSet[35] = new RGB((/(double)255),(/(double)255),(/(double)255));

	return colorDataSet;
}
*/

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