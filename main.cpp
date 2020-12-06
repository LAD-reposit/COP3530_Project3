#include <chrono>
#include <vector>
#include <iostream>
#include <string> 
#include "pixel.h"
#include "TGAdecon.h"
using namespace std;
using namespace std::chrono;
int main()
{
	vector<pixel> pixels;
	int choice;
	bool running = true;
	string selection = "";
	TGAdecon file;

	while (running)
	{
		cout << "Which image's pixels do you want to sort?" << endl;
		cout << "1. Color Explosion (100 x 100 pixels)" << endl;
		cout << "2. Mickey Mouse (1,000 x 1,000 pixels)" << endl;
		cout << "3. Bucharest (10,916 x 9,985 pixels)" << endl;
		cout << "4. Quit" << endl;
		cin >> choice;
		if (choice == 1)
			// READ IN COLOR EXPLOSION TO VECTOR OF PIXELS
			selection = "./image_input/color_explosion.tga";
		else if (choice == 2)
			// READ IN MICKEY MOUSE TO VECTOR OF PIXELS
			selection = "./image_input/MickeyMouse.tga"
		else if (choice == 3)
			// READ IN BUCHAREST TO VECTOR OF PIXELS
			selection = "./image_input/map.tga";
		else if (choice == 4)
		{
			running = false;
			return 0;
		}
		else
			cout << "Invalid Response." << endl;

		if (selection != "") 
		{
			//open file, store header
			file.header = file.getHeader(selection);
			//open file, jump to pixel data, and store into pixels
			ifstream fil;
			fil.open(selection, ios_base::in | ios_base::binary);
			fil.seekg(18);
			pixels = file.inputPixels(fil);
			fil.close();
		}

		cout << "Which color would you like to sort by?" << endl;
		cout << "1. Red" << endl;
		cout << "2. Green" << endl;
		cout << "3. Blue" << endl;
		cout << "4. Quit" << endl;
		cin >> choice;

		long bubbleTime, mergeTime;
		if (choice == 1)
		{
			// START TIMER
			auto startBubble = high_resolution_clock::now();
			BubbleSort(pixels, "Red");
			auto stopBubble = high_resolution_clock::now();
			bubbleTime = duration_cast<microseconds>(stopBubble - startBubble); 
			// STOP TIMER, START NEW TIMER
			int size = sizeof(pixels) / sizeof(pixels[0].getRed());
			auto startMerge = high_resolution_clock::now();
			MergeSort(pixels, "Red", 0, size - 1);
			auto stopMerge = high_resolution_clock::now();
			mergeTime = duration_cast<microseconds>(stopMerge - startMerge);
			// STOP TIMER
		}
		else if (choice == 2)
		{
			// START TIMER
			auto startBubble = high_resolution_clock::now();
			BubbleSort(pixels, "Green");
			auto stopBubble = high_resolution_clock::now();
			bubbleTime = duration_cast<microseconds>(stopBubble - startBubble); 
			// STOP TIMER, START NEW TIMER
			int size = sizeof(pixels) / sizeof(pixels[0].getGreen());
			auto startMerge = high_resolution_clock::now();
			MergeSort(pixels, "Green", 0, size - 1);
			auto stopMerge = high_resolution_clock::now();
			mergeTime = duration_cast<microseconds>(stopMerge - startMerge);
			// STOP TIMER
		}
		else if (choice == 3)
		{
			// START TIMER
			auto startBubble = high_resolution_clock::now();
			BubbleSort(pixels, "Blue");
			auto stopBubble = high_resolution_clock::now();
			bubbleTime = duration_cast<microseconds>(stopBubble - startBubble); 
			// STOP TIMER, START NEW TIMER
			int size = sizeof(pixels) / sizeof(pixels[0].getBlue());
			auto startMerge = high_resolution_clock::now();
			MergeSort(pixels, "Blue", 0, size - 1);
			auto stopMerge = high_resolution_clock::now();
			mergeTime = duration_cast<microseconds>(stopMerge - startMerge);
			// STOP TIMER
		}
		else if (choice == 4)
		{
			running = false;
			return 0;
		}
        else
			cout << "Invalid Response." << endl;

		// WRITE SORTED PIXELS TO FILE
		string outfile = file.whichOutput(selection);
		ofstream clos;
		clos.open(outfile, ios_base::out | ios_base::binary);
		file.writeFile(clos, file.header, pixels);
		clos.close();

		// DISPLAY GRADIENT
		cout << "Running time for Bubble Sort: " <<bubbleTime<< endl; // DISPLAY BUBBLE SORT TIME
		cout << "Running time for Merge Sort: " <<mergeTime<< endl; // DISPLAY MERGE SORT TIME

		if (mergeTime < bubbleTime)
		{
			cout << "Merge Sort was " << (mergeTime / bubbleTime) * 100 << "% faster than Bubble Sort." << endl;
		}
		else
		{
			cout << "Bubble Sort was " << (bubbleTime / mergeTime) * 100 << "% faster than Merge Sort." << endl;
		}
		
	}

	return 0;
}

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