#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "utils.h"

double getRandomNumber(int maxValue){
	double divisor = RAND_MAX/(maxValue+1);
	double randomNumber;
	do{
		randomNumber = rand()/divisor;
	}while(randomNumber > maxValue);

	return randomNumber;
}