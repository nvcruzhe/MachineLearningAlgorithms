#include "RGB.h"

RGB::RGB(){
	_red = 0;
	_green = 0;
	_blue = 0;
}

RGB::RGB(double red, double green, double blue){
	_red = red;
	_green = green;
	_blue = blue;
}

RGB::~RGB(){}

void RGB::setRGB(double red, double green, double blue){
	_red = red;
	_green = green;
	_blue = blue;
}