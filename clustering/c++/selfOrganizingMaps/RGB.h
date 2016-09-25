#ifndef RGB_H
#define RGB_H

#include <cstdio>
#include <cstdlib>
#include <vector>

using namespace std;

class RGB{
	public:
		RGB();
		RGB(double red, double green, double blue);
		~RGB();
		void setRed(double red){_red =  red;}
		void setGreen(double green){_green = green;}
		void setBlue(double blue){_blue = blue;}
		void setRGB(double red, double green, double blue);
		double getRed(){return _red;}
		double getGreen(){return _green;}
		double getBlue(){return _blue;}
		vector <double> rgbToVector();
	private:
		double _red, _green, _blue;
};
#endif