#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <GL/glut.h>

#include "Classes.h"

#define TOTALWEIGHTS 3
#define MAXEPOCHS 1000
#define SIZE 100
#define DATASETSIZE 48
#define INITIALLEARNINGRATE 0.1
#define WINDOWTITLE "Self Organizing Maps"

using namespace std;

// Global variables
vector<vector<double> > _trainingDataSet;
vector<vector<double> > _testDataset;
vector<RGB* > _initializationDataSet;
vector<RGB *> _rgbTrainingDataSet;
SelfOrganizingMaps *_som;
bool _training;
int _dataSetType;
int _executionType;
int _dataSetSize;
int _argc;
int _width;
int _height;
double _openGLFovy;
char *_fileName;

// main methods
void algorithmInitialization(int dataSetType, int size);

// OpenGl methods
void display(void);
void reshape(int width, int height);
void keyboard(unsigned char key, int x, int y);
void idle(void);
void init();

int main(int argc, char **argv){
	// Check if argv has more than one argument
	// 0 program name
	// 1 select matrix color formation, dataSet for training, dataSet for evaluation
	// 2 file to import matrix
	if(argc != 3 ){
		cout << "Se requieren 3 argumentos para iniciar el programa" << endl;
		cout << "1: programa, 2: tipo de ejecucion 0) Dataset 1) Cargar matrix entrenada";
		cout << "2: Nombre del archivo para cargar matriz entrenada o DataSet" << endl;
		return 0;
	}

	_executionType = atoi(argv[1]);

	_training = false;

	switch(_executionType){
		case 0: // Dataset
			_dataSetType = atoi(argv[2]);
			algorithmInitialization(_dataSetType,100);
			_width = 400;
			_height = 400;
			_openGLFovy = 45.0;
			break;
		case 1: // Load Matrix
			_fileName = argv[2];
			_width = 800;
			_height = 800;
			_openGLFovy = 90.0;
			break;
	}

	// OpenGL window configuration
	glutInitWindowSize(_width, _height);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow(WINDOWTITLE);


	// OpenGL register callback functions
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(idle);

	// OpenGL initalize parameters
	init();

	// OpenGL loop
	glutMainLoop();

	// Release memory
	delete _som;

	return 0;
}

void algorithmInitialization(int dataSetType, int size){
	switch(dataSetType){
		// Many colors dataset
		case 1:
			_trainingDataSet = Utils::createColorDataSet(DATASETSIZE, TOTALWEIGHTS);
			_dataSetSize = _trainingDataSet.size();
			_testDataset = Utils::createColorTestDataSet();
			_som = new SelfOrganizingMaps(size, TOTALWEIGHTS, MAXEPOCHS, INITIALLEARNINGRATE, _dataSetSize);
			break;

		// Blue colors dataset
		case 2:
			_initializationDataSet = Utils::createBlueColorBuildMatrixDataSet();
			_rgbTrainingDataSet = Utils::createBlueColorTrainMatrixDataSet();
			_dataSetSize = _rgbTrainingDataSet.size();
			_som = new SelfOrganizingMaps(size, TOTALWEIGHTS, MAXEPOCHS, INITIALLEARNINGRATE, _initializationDataSet, _dataSetSize);
			break;
		case 3:
			_initializationDataSet = Utils::createRedColorBuildMatrixDataSet();
			_rgbTrainingDataSet = Utils::createRedColorTrainMatrixDataSet();
			_dataSetSize = _rgbTrainingDataSet.size();
			_som = new SelfOrganizingMaps(size, TOTALWEIGHTS, MAXEPOCHS, INITIALLEARNINGRATE, _initializationDataSet, _dataSetSize);
			break;
		case 4:
			_initializationDataSet = Utils::createGreenColorBuildMatrixDataSet();
			_rgbTrainingDataSet = Utils::createGreenColorTrainMatrixDataSet();
			_dataSetSize = _rgbTrainingDataSet.size();
			_som = new SelfOrganizingMaps(size, TOTALWEIGHTS, MAXEPOCHS, INITIALLEARNINGRATE, _initializationDataSet, _dataSetSize);
			break;
		case 5:
			_initializationDataSet = Utils::createYellowColorBuildMatrixDataSet();
			_rgbTrainingDataSet = Utils::createYellowColorTrainMatrixDataSet();
			_dataSetSize = _rgbTrainingDataSet.size();
			_som = new SelfOrganizingMaps(size, TOTALWEIGHTS, MAXEPOCHS, INITIALLEARNINGRATE, _initializationDataSet, _dataSetSize);
			break;
		case 6:
			_initializationDataSet = Utils::createMultipleColorBuildMatrixDataSet();
			_rgbTrainingDataSet = Utils::createBlueColorTrainMatrixDataSet();
			_dataSetSize = _rgbTrainingDataSet.size();
			_som = new SelfOrganizingMaps(size, TOTALWEIGHTS, MAXEPOCHS, INITIALLEARNINGRATE, _initializationDataSet, _dataSetSize);
			break;
	}
}

void display(){
	// Clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Compute eye position
	glLoadIdentity();

	// TODO: check what does this function do
	gluLookAt(50,50,200, 50,50,0, 0,1,0);

	// Draw the current map
	_som->displayUsingNeuronColor();

	// Draw to screen
	glutSwapBuffers();
}

void reshape(int width, int height){
	glViewport(0, 0, (GLsizei) width, (GLsizei) height);
}

void keyboard(unsigned char key, int mouseX, int mouseY){ 
	switch (key){
		case 't':
			_training = !_training;
			if(_training)
				cout << "Training..." << endl;
			else
				cout << "Stopped training" << endl;
			break;
		case 'r':
			_training = false;
			_som->reset();
			cout << "Map reset" << endl;
			glutPostRedisplay();
			break;
		case '0':
			cout << "0" << endl;
			//0 0 255 Azul
			_som->evaluateIndependentVector(_testDataset[0]);
			glutPostRedisplay();
			break;
		case '1':
			cout << "1" << endl;
			// 255 0 0 Rojo
			_som->evaluateIndependentVector(_testDataset[1]);
			glutPostRedisplay();
			break;
		case '2':
			// 204 0 204 Violeta
			cout << "2" << endl;
			_som->evaluateIndependentVector(_testDataset[2]);
			glutPostRedisplay();
			break;
		case '3':
			// 0 255 0 Verde 
			cout << "3" << endl;
			_som->evaluateIndependentVector(_testDataset[3]);
			glutPostRedisplay();
			break;
		case 's':
			if(_training)
				_training = !_training;
			break;
		case 'e':
			Utils::exportMatrixToFile(_som->getMatrix(), _som->getEpochs(),
				MAXEPOCHS, INITIALLEARNINGRATE, _som->getCurrenLearningRate());
			break;
		case 'i':
			if(_training)
				_training = !_training;
			if(_argc > 1){
			Utils::importMatrixFromFile(_fileName, _som);
			glutPostRedisplay();
			cout << "Termino de actualizar y ya debe estar repintado" << endl;
			}else{
				cout << "No es posible cargar un entranamiento porque ";
				cout << "no fue proporcionado un nombre de archivo." << endl;
			}
	}
}

void idle(void){
	if (_training && (_som->getEpochs() < MAXEPOCHS)){
		int randInput = rand() % _dataSetSize;
		if(_dataSetType == 1){
			_som->trainSegmentedFunctions(_trainingDataSet[randInput]);
		}else{
			_som->trainSegmentedFunctions(_rgbTrainingDataSet[randInput]->rgbToVector());
		}
		glutPostRedisplay();
 	}
}

void init(){
	// Initialize viewing system
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(_openGLFovy, 1.0, 1.0, 1000.0);
	glMatrixMode(GL_MODELVIEW);

	// Initialize background color to black
	glClearColor(0.0,0.0,0.0,0.0);

	// Enable depth buffering
	glEnable(GL_DEPTH_TEST);
}