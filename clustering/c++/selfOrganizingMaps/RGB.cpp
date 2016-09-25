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

vector <double> RGB::rgbToVector(){
	vector<double> rgb;
	rgb.resize(3);
	rgb[0] = _red;
	rgb[1] = _green;
	rgb[2] = _blue;
	return rgb;
}