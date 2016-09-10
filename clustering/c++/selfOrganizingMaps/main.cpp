#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <GL/glut.h>

#include "SelfOrganizingMaps.h"

#define NEURON_NUM 1
#define WIDTH 400
#define HEIGTH 400
#define TOTALWEIGHTS 3
#define MAXEPOCHS 1000
#define SIZE 100

using namespace std;

void display(void);
void reshape(int width, int height);
void keyboard(unsigned char key, int x, int y);
void idle(void);
void init();
vector<vector<double> > createDataSet();

SelfOrganizingMaps *som;
bool training;
int numInputs;
vector<vector<double> > dataSet;

int main(int argc, char **argv){
	dataSet = createDataSet();
	numInputs = dataSet.size();
	som = new SelfOrganizingMaps(SIZE, TOTALWEIGHTS, MAXEPOCHS, numInputs, 0.1);
	training = false;

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
	som->display();

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
	}
}

void idle(void){
	//if (training && som->getEpochs() < MAXEPOCHS){
	if (training && som->getEpochs() < MAXEPOCHS){
		int randInput = rand() % numInputs;
		som->train(dataSet[randInput]);
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

vector<vector<double> > createDataSet(){
	vector<vector<double> > dataSet;
	dataSet.resize(48);
	
	for(int i=0; i<48; i++){
		dataSet[i].resize(TOTALWEIGHTS);
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