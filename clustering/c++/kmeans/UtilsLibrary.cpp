#include "UtilsLibrary.h"

double UtilsLibrary::getRandomNumber(int maxValue){
	double divisor = RAND_MAX/(maxValue+1);
	double randomNumber;
	do{
		randomNumber = rand()/divisor;
	}while(randomNumber > maxValue);

	return randomNumber;
}