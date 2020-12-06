#include "pixel.h"
pixel::pixel() 
{
	this->red = 0;
	this->green = 0;
	this->blue = 0;
}
pixel::pixel(unsigned char red, unsigned char green, unsigned char blue) 
{
	this->red = red;
	this->green = green;
	this->blue = blue;
}
unsigned char pixel::getRed() 
{
	return this->red;
}
unsigned char pixel::getGreen() 
{
	return this->green;
}
unsigned char pixel::getBlue() 
{
	return this->blue;
}
void pixel::setRed(unsigned char red) 
{
	this->red = red;
}
void pixel::setGreen(unsigned char green) 
{
	this->green = green;
}
void pixel::setBlue(unsigned char blue) 
{
	this->blue = blue;
}