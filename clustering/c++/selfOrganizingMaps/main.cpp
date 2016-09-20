#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <GL/glut.h>

#include "SelfOrganizingMaps.h"
#include "utils.h"

#define NEURON_NUM 1
#define WIDTH 400
#define HEIGTH 400
#define TOTALWEIGHTS 3
#define MAXEPOCHS 1000
#define SIZE 100
#define DATASETSIZE 48
#define INITIALLEARNINGRATE 0.1

using namespace std;

// OpenGlL methods
void display(void);
void reshape(int width, int height);
void keyboard(unsigned char key, int x, int y);
void idle(void);
void init();

// Global variables
SelfOrganizingMaps *som;
bool training;
vector<vector<double> > dataSet;
vector<vector<double> > testDataset; 

int main(int argc, char **argv){
	// Algorithm initialization
	dataSet = Utils::createColorDataSet(DATASETSIZE, TOTALWEIGHTS);
	testDataset = Utils::createColorTestDataSet(); 
	som = new SelfOrganizingMaps(SIZE, TOTALWEIGHTS, MAXEPOCHS, DATASETSIZE, INITIALLEARNINGRATE);
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
			Utils::exportMatrixToFile(som->getMatrix(), som->getEpochs());
			break;
	}
}

void idle(void){
	if (training && (som->getEpochs() < MAXEPOCHS)){
		int randInput = rand() % DATASETSIZE;
		som->trainSegmentedFunctions(dataSet[randInput]);
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