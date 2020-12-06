#pragma once
#include <string>
using namespace std;

class pixel
{
	unsigned char red;
	unsigned char green;
	unsigned char blue;
public:

	pixel();
	pixel(unsigned char red, unsigned char green, unsigned char blue);
	
	unsigned char getRed();
	unsigned char getGreen();
	unsigned char getBlue();
	void setRed(unsigned char red);
	void setGreen(unsigned char green);
	void setBlue(unsigned char blue);
};
