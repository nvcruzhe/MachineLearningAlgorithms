#include "utils.h"

double Utils::getRandomDoubleNumber(double min, double max){
	double random = (double)rand() / RAND_MAX;
	return min + random * (max - min);	
}