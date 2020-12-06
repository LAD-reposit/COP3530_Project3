#include "pixel.h"
#include <vector>
#include <iostream>
#include <fstream>

struct Head
{
	char  idLength;
	char  colorMapType;
	char  dataTypeCode;
	short colorMapOrigin;
	short colorMapLength;
	char  colorMapDepth;
	short xOrigin;
	short yOrigin;
	short width;
	short height;
	char  bitsPerPixel;
	char  imageDescriptor;

	Head();
};

class TGAdecon
{
public:
	Head header;
	string fil;
	int option;

	//default
	TGAdecon();

	//get a file name
	string whichFile(int selection);
	string whichOutput(string option);

	//format/structure
	Head getHeader(string file);
	pixel findPix(ifstream& file);
	vector<pixel> inputPixels(ifstream& file);

	//write it into the output file
	void writeFile(ofstream& a, Head& b, vector<pixel> pixels);

	//testing
	void printPixels(vector<pixel> pix);
};

