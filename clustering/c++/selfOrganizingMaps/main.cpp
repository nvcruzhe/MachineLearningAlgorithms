#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <GL/glut.h>

#include "Classes.h"

#define WIDTH 400
#define HEIGTH 400
#define TOTALWEIGHTS 3
#define MAXEPOCHS 1000
#define SIZE 100
#define DATASETSIZE 48
#define INITIALLEARNINGRATE 0.1

using namespace std;

// OpenGl methods
void display(void);
void reshape(int width, int height);
void keyboard(unsigned char key, int x, int y);
void idle(void);
void init();

// Global variables
SelfOrganizingMaps *som;
bool training;
vector<vector<double> > trainingDataSet;
vector<vector<double> > testDataset;
vector<RGB* > initializationDataSet;
int _argc;
int dataSetType;
char *_fileName;

int main(int argc, char **argv){
	// Setting global variable for more control
	_argc = argc;

	// Check if argv has more than one argument
	// 0 program name
	// 1 select matrix color formation, dataSet for training, dataSet for evaluation
	// 2 file to import matrix
	if(argc < 2){
		cout << "se requiere indicar un dataset para el correcto funcionamiento" << endl;
		return 0;
	}

	// Get dataSetType
	dataSetType = atoi(argv[1]);

	// Set file name for importing trained matrix
	if(argc == 3){
		_fileName = argv[2];
	}

	// Algorithm initialization
	switch(dataSetType){
		// Many colors dataset
		case 1:
			trainingDataSet = Utils::createColorDataSet(DATASETSIZE, TOTALWEIGHTS);
			testDataset = Utils::createColorTestDataSet();
			som = new SelfOrganizingMaps(SIZE, TOTALWEIGHTS, MAXEPOCHS, INITIALLEARNINGRATE);
			break;

		// Blue colors dataset
		case 2:
			initializationDataSet = Utils::createBlueColorDataSet();
			som = new SelfOrganizingMaps(SIZE, TOTALWEIGHTS, MAXEPOCHS, INITIALLEARNINGRATE, initializationDataSet);
			break;
		case 3:
			initializationDataSet = Utils::createRedColorDataSet();
			som = new SelfOrganizingMaps(SIZE, TOTALWEIGHTS, MAXEPOCHS, INITIALLEARNINGRATE, initializationDataSet);
			break;
		case 4:
			initializationDataSet = Utils::createGreenColorDataSet();
			som = new SelfOrganizingMaps(SIZE, TOTALWEIGHTS, MAXEPOCHS, INITIALLEARNINGRATE, initializationDataSet);
			break;
		case 5:
			initializationDataSet = Utils::createYellowColorDataSet();
			som = new SelfOrganizingMaps(SIZE, TOTALWEIGHTS, MAXEPOCHS, INITIALLEARNINGRATE, initializationDataSet);
			break;
	}
	
	training = false;

	// Open GL
	// Set up window
  	glutInitWindowSize(WIDTH, HEIGTH);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("Self-organizing Map");

	// Register callback functions
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutIdleFunc(idle);

	// Initalize opengl parameters
	init();

	// Loop until something happens
	glutMainLoop();

	// Release memory
	delete som;
	return 0;
}

void display(){
	// Clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Compute eye position
	glLoadIdentity();
	gluLookAt(50,50,200, 50,50,0, 0,1,0);

	// Draw the current map
	som->displayUsingNeuronColor();

	// Draw to screen
	glutSwapBuffers();
}

void reshape(int width, int height){
	glViewport(0, 0, (GLsizei) width, (GLsizei) height);
}

void keyboard(unsigned char key, int mouseX, int mouseY){ 
	switch (key){
		case 't':
			training = !training;
			if(training)
				cout << "Training..." << endl;
			else
				cout << "Stopped training" << endl;
			break;
		case 'r':
			training = false;
			som->reset();
			cout << "Map reset" << endl;
			glutPostRedisplay();
			break;
		case '0':
			cout << "0" << endl;
			//0 0 255 Azul
			som->evaluateIndependentVector(testDataset[0]);
			glutPostRedisplay();
			break;
		case '1':
			cout << "1" << endl;
			// 255 0 0 Rojo
			som->evaluateIndependentVector(testDataset[1]);
			glutPostRedisplay();
			break;
		case '2':
			// 204 0 204 Violeta
			cout << "2" << endl;
			som->evaluateIndependentVector(testDataset[2]);
			glutPostRedisplay();
			break;
		case '3':
			// 0 255 0 Verde 
			cout << "3" << endl;
			som->evaluateIndependentVector(testDataset[3]);
			glutPostRedisplay();
			break;
		case 's':
			if(training)
				training = !training;
			break;
		case 'e':
			Utils::exportMatrixToFile(som->getMatrix(), som->getEpochs(),
				MAXEPOCHS, INITIALLEARNINGRATE, som->getCurrenLearningRate());
			break;
		case 'i':
			if(training)
				training = !training;
			if(_argc > 1){
			Utils::importMatrixFromFile(_fileName, som);
			glutPostRedisplay();
			cout << "Termino de actualizar y ya debe estar repintado" << endl;
			}else{
				cout << "No es posible cargar un entranamiento porque ";
				cout << "no fue proporcionado un nombre de archivo." << endl;
			}
	}
}

void idle(void){
	if (training && (som->getEpochs() < MAXEPOCHS)){
		int randInput = rand() % DATASETSIZE;
		som->trainSegmentedFunctions(trainingDataSet[randInput]);
		glutPostRedisplay();
 	}
}

void init(){
	// Initialize viewing system
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, 1.0, 1.0, 1000.0);
	glMatrixMode(GL_MODELVIEW);

	// Initialize background color to black
	glClearColor(0.0,0.0,0.0,0.0);

	// Enable depth buffering
	glEnable(GL_DEPTH_TEST);
}