#include "TGAdecon.h"
Head::Head() 
{
	this->idLength = 0;
	this->colorMapType = 0;
	this->dataTypeCode = 0;
	this->colorMapOrigin = 0;
	this->colorMapLength = 0;
	this->colorMapDepth = 0;
	this->xOrigin = 0;
	this->yOrigin = 0;
	this->width = 0;
	this->height = 0;
	this->bitsPerPixel = 0;
	this->imageDescriptor = 0;
}

//default
TGAdecon::TGAdecon() 
{
	this->header = Head();
	this->fil = "";
	this->option = 0;
}

//select which file to deconstruct
string TGAdecon::whichFile(int option)
{
	string inp = "";
	if (option == 1)
	{
		//map
		inp = "./image_input/map.tga";
	}
	if (option == 2)
	{
		//color explosion
		inp = "./image_input/color_explosion.tga";
	}
	if (option == 3)
	{
		//mickey
		inp = "./image_input/MickeyMouse.tga";
	}
	return inp;
}

//select the output files
string TGAdecon::whichOutput(string o)
{
	o = o.substr(14, string::npos);
	string result = "./image_output/" + o;
	return result;
}

//function to load and store the header
Head TGAdecon::getHeader(string fileLocation)
{
	string current = fileLocation;
	Head head;

	ifstream file;
	file.open(current, ios_base::in | ios_base::binary);
	if (!file.is_open()) { cout << "Error! File " << current << " is not open." << endl; }
	if (file.is_open())
	{
		file.read((char*)& head.idLength, sizeof(head.idLength));
		file.read((char*)& head.colorMapType, sizeof(head.colorMapType));
		file.read((char*)& head.dataTypeCode, sizeof(head.dataTypeCode));
		file.read((char*)& head.colorMapOrigin, sizeof(head.colorMapOrigin));
		file.read((char*)& head.colorMapLength, sizeof(head.colorMapLength));
		file.read((char*)& head.colorMapDepth, sizeof(head.colorMapDepth));
		file.read((char*)& head.xOrigin, sizeof(head.xOrigin));
		file.read((char*)& head.yOrigin, sizeof(head.yOrigin));
		file.read((char*)& head.width, sizeof(head.width));
		file.read((char*)& head.height, sizeof(head.height));
		file.read((char*)& head.bitsPerPixel, sizeof(head.bitsPerPixel));
		file.read((char*)& head.imageDescriptor, sizeof(head.imageDescriptor));
	}
	file.close();
	return head;
}
//function to open a file and return a pixel at a specific location
pixel TGAdecon::findPix(ifstream& file)
{
	unsigned char red;
	unsigned char green;
	unsigned char blue;
	file.read((char*)& blue, sizeof(blue));
	file.read((char*)& green, sizeof(green));
	file.read((char*)& red, sizeof(red));

	pixel pix(red, green, blue);

	return pix;
}
//function to store all of the pixels in the file
vector<pixel> TGAdecon::inputPixels(ifstream& file) 
{
	vector<pixel> pixels;
	int pixnum = header.height * header.width;
	for (int i = 0; i < pixnum; i++) 
	{
		pixels.push_back(findPix(file));
	}
	return pixels;
}

//write to the new file
//add a header to the output file
void TGAdecon::writeFile(ofstream& file, Head& head, vector<pixel> pixels)
{
	file.write((char*)& head.idLength, sizeof(head.idLength));
	file.write((char*)& head.colorMapType, sizeof(head.colorMapType));
	file.write((char*)& head.dataTypeCode, sizeof(head.dataTypeCode));
	file.write((char*)& head.colorMapOrigin, sizeof(head.colorMapOrigin));
	file.write((char*)& head.colorMapLength, sizeof(head.colorMapLength));
	file.write((char*)& head.colorMapDepth, sizeof(head.colorMapDepth));
	file.write((char*)& head.xOrigin, sizeof(head.xOrigin));
	file.write((char*)& head.yOrigin, sizeof(head.yOrigin));
	file.write((char*)& head.width, sizeof(head.width));
	file.write((char*)& head.height, sizeof(head.height));
	file.write((char*)& head.bitsPerPixel, sizeof(head.bitsPerPixel));
	file.write((char*)& head.imageDescriptor, sizeof(head.imageDescriptor));

	for (int i = 0; i < pixels.size(); i++) 
	{
		unsigned char r = pixels.at(i).getRed();
		unsigned char g = pixels.at(i).getGreen();
		unsigned char b = pixels.at(i).getBlue();
		file.write((char*)& b, sizeof(unsigned char));
		file.write((char*)& g, sizeof(unsigned char));
		file.write((char*)& r, sizeof(unsigned char));
	}
}

//testing
void TGAdecon::printPixels(vector<pixel> pix) 
{
	for (int i = 0; i < pix.size(); i++ ) 
	{
		cout << "Red: " << static_cast<unsigned>(pix.at(i).getRed()) << " ";
		cout << "Green: " << static_cast<unsigned>(pix.at(i).getGreen()) << " ";
		cout << "Blue: " << static_cast<unsigned>(pix.at(i).getBlue()) << endl;
	}
}