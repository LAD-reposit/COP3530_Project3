#include <chrono>
#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace std::chrono;


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
	string whichOutput(string option, string bubb);

	//format/structure
	Head getHeader(string file);
	pixel findPix(ifstream& file);
	vector<pixel> inputPixels(ifstream& file);

	//write it into the output file
	void writeFile(ofstream& a, Head& b, vector<pixel> pixels);

	//testing
	void printPixels(vector<pixel> pix);
};

void merge(vector<pixel>& pixelVec, string pixelColor, int left, int mid, int right);
void mergeSort(vector<pixel>& pixelVec, string pixelColor, int left, int right);
void BubbleSort(vector<pixel>& pixels, string color);
float saturation(pixel p, string op);
void DisplayImage(string image, string sortMethod);

int main()
{
	vector<pixel> pixels_merge;
	vector<pixel> pixels_bubble;
	int choice;
	string imageName;
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
		{
			// READ IN COLOR EXPLOSION TO VECTOR OF PIXELS
			selection = "./image_input/color_explosion.tga";
			imageName = "Color Explosion";
		}
		else if (choice == 2)
		{
			// READ IN MICKEY MOUSE TO VECTOR OF PIXELS
			selection = "./image_input/MickeyMouse.tga";
			imageName = "Mickey Mouse";
		}
		else if (choice == 3)
		{
			// READ IN BUCHAREST TO VECTOR OF PIXELS
			selection = "./image_input/map.tga";
			imageName = "Bucharest";
		}
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
			pixels_merge = file.inputPixels(fil);
			pixels_bubble = pixels_merge;
			fil.close();
			cout << "FILE LOADED" << endl;
		}

		cout << "Which color would you like to sort by?" << endl;
		cout << "1. Red" << endl;
		cout << "2. Green" << endl;
		cout << "3. Blue" << endl;
		cout << "4. Quit" << endl;
		cin >> choice;

		std::chrono::microseconds bubbleTime, mergeTime;
		if (choice == 1)
		{
			// START TIMER
			auto startBubble = high_resolution_clock::now();
			cout << "BUBBLE SORT BEGINNING" << endl;
			BubbleSort(pixels_bubble, "Red");
			cout << "BUBBLE SORT FINISHED" << endl;
			auto stopBubble = high_resolution_clock::now();
			bubbleTime = duration_cast<microseconds>(stopBubble - startBubble);
			// STOP TIMER, START NEW TIMER
			int size = pixels_merge.size();
			auto startMerge = high_resolution_clock::now();
			cout << "MERGE SORT BEGINNING" << endl;
			mergeSort(pixels_merge, "Red", 0, size - 1);
			cout << "MERGE SORT FINISHED" << endl;
			auto stopMerge = high_resolution_clock::now();
			mergeTime = duration_cast<microseconds>(stopMerge - startMerge);
			// STOP TIMER
		}
		else if (choice == 2)
		{
			// START TIMER
			auto startBubble = high_resolution_clock::now();
			BubbleSort(pixels_bubble, "Green");
			auto stopBubble = high_resolution_clock::now();
			bubbleTime = duration_cast<microseconds>(stopBubble - startBubble);
			// STOP TIMER, START NEW TIMER
			int size = pixels_merge.size();
			auto startMerge = high_resolution_clock::now();
			mergeSort(pixels_merge, "Green", 0, size - 1);
			auto stopMerge = high_resolution_clock::now();
			mergeTime = duration_cast<microseconds>(stopMerge - startMerge);
			// STOP TIMER
		}
		else if (choice == 3)
		{
			// START TIMER
			auto startBubble = high_resolution_clock::now();
			BubbleSort(pixels_bubble, "Blue");
			auto stopBubble = high_resolution_clock::now();
			bubbleTime = duration_cast<microseconds>(stopBubble - startBubble);
			// STOP TIMER, START NEW TIMER
			int size = pixels_merge.size();
			auto startMerge = high_resolution_clock::now();
			mergeSort(pixels_merge, "Blue", 0, size - 1);
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
		//file.printPixels(pixels_merge);
		string merg = "merge_";
		string bubb = "bubble_";

		string outfile_merge = file.whichOutput(selection, merg);
		ofstream clos;
		clos.open(outfile_merge, ios_base::out | ios_base::binary);
		file.writeFile(clos, file.header, pixels_merge);
		clos.close();

		string outfile_bubble = file.whichOutput(selection, bubb);
		ofstream cl;
		cl.open(outfile_bubble, ios_base::out | ios_base::binary);
		file.writeFile(cl, file.header, pixels_bubble);
		cl.close();

		// DISPLAY GRADIENT
		bool displaying = true;
		string sortMethod;
		while (displaying)
		{
			cout << "Which sorted image would you like to view?" << endl;
			cout << "1. Merge Sort" << endl;
			cout << "2. Bubble Sort" << endl;
			cout << "3. Restart" << endl;
			cin >> choice;
			if (choice == 1)
				DisplayImage(imageName, "Merge");
			else if (choice == 2)
				DisplayImage(imageName, "Bubble");
			else if (choice == 3)
				displaying = false;
			else
				cout << "Invalid Response" << endl;

		}

		cout << "Running time for Bubble Sort: " << bubbleTime.count() << endl; // DISPLAY BUBBLE SORT TIME
		cout << "Running time for Merge Sort: " << mergeTime.count() << endl; // DISPLAY MERGE SORT TIME

		float mergeDuration = (float)mergeTime.count();
		float bubbleDuration = (float)bubbleTime.count();
		float ratio = 100 * (bubbleDuration / mergeDuration);

		if (mergeTime < bubbleTime)
		{
			cout << "Merge Sort was " << ratio << "% faster than Bubble Sort." << endl;
		}
		else
		{
			cout << "Bubble Sort was " << (float)((bubbleTime / mergeTime) * (long)100.000) << "% faster than Merge Sort." << endl;
		}

	}

	return 0;
}

//sources: Sorting 2 powerpoint by Professor Kapoor
void merge(vector<pixel>& pixelVec, string pixelColor, int left, int mid, int right) {

	if (pixelColor == "Red") { //if the user wants to merge sort by red
		int n1 = mid - left + 1;
		int n2 = right - mid;

		vector<unsigned char> X; //left
		vector<unsigned char> Y; //right

		for (int i = 0; i < n1; i++) { //sorting
			X.push_back(pixelVec[left + i].getRed());
		}
		for (int j = 0; j < n2; j++) {
			Y.push_back(pixelVec[mid + 1 + j].getRed());
		}

		int i = 0;
		int j = 0;
		int k = left;

		while (i < n1 && j < n2) { //sorting part
			if (X[i] <= Y[j]) {
				pixelVec[k].setRed(X[i]);
				i++;
			}
			else {
				pixelVec[k].setRed(Y[j]);
				j++;
			}
			k++;
		}

		while (i < n1) { //sorting parts
			pixelVec[k].setRed(X[i]);
			i++;
			k++;
		}

		while (j < n2) { //sorting parts
			pixelVec[k].setRed(Y[j]);
			j++;
			k++;
		}
	}

	else if (pixelColor == "Green") { //if the user wants to merge sort by green
		int n1 = mid - left + 1;
		int n2 = right - mid;

		vector<unsigned char> X; //left
		vector<unsigned char> Y; //right

		for (int i = 0; i < n1; i++) { //sorting
			X.push_back(pixelVec[left + i].getGreen());
		}
		for (int j = 0; j < n2; j++) {
			Y.push_back(pixelVec[mid + 1 + j].getGreen());
		}

		int i = 0;
		int j = 0;
		int k = left;

		while (i < n1 && j < n2) { //sorting part
			if (X[i] <= Y[j]) {
				pixelVec[k].setGreen(X[i]);
				i++;
			}
			else {
				pixelVec[k].setGreen(Y[j]);
				j++;
			}
			k++;
		}

		while (i < n1) { //sorting parts
			pixelVec[k].setGreen(X[i]);
			i++;
			k++;
		}

		while (j < n2) { //sorting parts
			pixelVec[k].setGreen(Y[j]);
			j++;
			k++;
		}
	}

	else if (pixelColor == "Blue") { //if the user wants to merge sort by green
		int n1 = mid - left + 1;
		int n2 = right - mid;

		vector<unsigned char> X; //left
		vector<unsigned char> Y; //right

		for (int i = 0; i < n1; i++) { //sorting
			X.push_back(pixelVec[left + i].getBlue());
		}
		for (int j = 0; j < n2; j++) {
			Y.push_back(pixelVec[mid + 1 + j].getBlue());
		}

		int i = 0;
		int j = 0;
		int k = left;

		while (i < n1 && j < n2) { //sorting part
			if (X[i] <= Y[j]) {
				pixelVec[k].setBlue(X[i]);
				i++;
			}
			else {
				pixelVec[k].setBlue(Y[j]);
				j++;
			}
			k++;
		}

		while (i < n1) { //sorting parts
			pixelVec[k].setBlue(X[i]);
			i++;
			k++;
		}

		while (j < n2) { //sorting parts
			pixelVec[k].setBlue(Y[j]);
			j++;
			k++;
		}
	}
}
void mergeSort(vector<pixel>& pixelVec, string pixelColor, int left, int right) { //sorting function that calls the helper sort
	if (left < right) {
		int mid = left + (right - left) / 2; //splits vector and then sorts each part
		mergeSort(pixelVec, pixelColor, left, mid);
		mergeSort(pixelVec, pixelColor, mid + 1, right);
		merge(pixelVec, pixelColor, left, mid, right); //merges it all together
	}
}
void BubbleSort(vector<pixel>& pixels, string color)
{
	bool swapped = true;

	while (swapped)
	{
		swapped = false;

		for (unsigned int i = 0; i < pixels.size() - 1; i++)
		{
			if (color == "Red")
			{
				if (pixels[i].getRed() > pixels[i + 1].getRed()) // Swaps adjacent pixels
				{
					swapped = true;
					pixel tempPix = pixels[i];
					pixels[i] = pixels[i + 1];
					pixels[i + 1] = tempPix;
				}
			}
			else if (color == "Green")
			{
				if (pixels[i].getGreen() > pixels[i + 1].getGreen()) // Swaps adjacent pixels
				{
					swapped = true;
					pixel tempPix = pixels[i];
					pixels[i] = pixels[i + 1];
					pixels[i + 1] = tempPix;
				}
			}
			else if (color == "Blue")
			{
				if (pixels[i].getBlue() > pixels[i + 1].getBlue()) // Swaps adjacent pixels
				{
					swapped = true;
					pixel tempPix = pixels[i];
					pixels[i] = pixels[i + 1];
					pixels[i + 1] = tempPix;
				}
			}
		}
	}
}

float saturation(pixel p, string op)
{
	return 0.0;
}

void DisplayImage(string image, string sortMethod)
{
	if (image == "Color Explosion")
	{
		sf::RenderWindow window(sf::VideoMode(1000, 1000), "Color Explosion Gradient");
		sf::Texture gradientTexture;
		string filePath;

		if (sortMethod == "Bubble")
			filePath = "./image_output/bubble_color_explosion.tga";
		else
			filePath = "./image_output/merge_color_explosion.tga";

		gradientTexture.loadFromFile(filePath);
		sf::Sprite gradient(gradientTexture);

		while (window.isOpen())
		{
			window.clear();

			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}
			gradient.setOrigin(gradient.getTextureRect().width / 2, gradient.getTextureRect().height / 2);
			gradient.setPosition(500, 500);
			window.draw(gradient);
			window.display();
		}
	}
	else if (image == "Mickey Mouse")
	{
		sf::RenderWindow window(sf::VideoMode(1600, 1200), "Mickey Mouse Gradient");
		sf::Texture gradientTexture;
		string filePath;

		if (sortMethod == "Bubble")
			filePath = "./image_output/bubble_mickey_mouse.tga";
		else
			filePath = "./image_output/merge_mickey_mouse.tga";

		gradientTexture.loadFromFile(filePath);
		sf::Sprite gradient(gradientTexture);

		while (window.isOpen())
		{
			window.clear();

			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}

			gradient.setOrigin(gradient.getTextureRect().width / 2, gradient.getTextureRect().height / 2);
			gradient.setPosition(800, 600);
			window.draw(gradient);
			window.display();
		}
	}
	else if (image == "Bucharest")
	{
		sf::RenderWindow window(sf::VideoMode(10916, 9985), "Bucharest Gradient");
		sf::Texture gradientTexture;
		string filePath;

		if (sortMethod == "Bubble")
			filePath = "./image_output/bubble_bucharest.tga";
		else
			filePath = "./image_output/merge_bucharest.tga";

		gradientTexture.loadFromFile(filePath);
		sf::Sprite gradient(gradientTexture);

		while (window.isOpen())
		{
			window.clear();

			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}

			gradient.setPosition(0, 0);
			window.draw(gradient);
			window.display();
		}
	}
}

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
string TGAdecon::whichOutput(string o, string bubb)
{
	o = o.substr(14, string::npos);
	string result = "./image_output/" + bubb + o;
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
		file.read((char*)&head.idLength, sizeof(head.idLength));
		file.read((char*)&head.colorMapType, sizeof(head.colorMapType));
		file.read((char*)&head.dataTypeCode, sizeof(head.dataTypeCode));
		file.read((char*)&head.colorMapOrigin, sizeof(head.colorMapOrigin));
		file.read((char*)&head.colorMapLength, sizeof(head.colorMapLength));
		file.read((char*)&head.colorMapDepth, sizeof(head.colorMapDepth));
		file.read((char*)&head.xOrigin, sizeof(head.xOrigin));
		file.read((char*)&head.yOrigin, sizeof(head.yOrigin));
		file.read((char*)&head.width, sizeof(head.width));
		file.read((char*)&head.height, sizeof(head.height));
		file.read((char*)&head.bitsPerPixel, sizeof(head.bitsPerPixel));
		file.read((char*)&head.imageDescriptor, sizeof(head.imageDescriptor));
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
	file.read((char*)&blue, sizeof(blue));
	file.read((char*)&green, sizeof(green));
	file.read((char*)&red, sizeof(red));

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
	file.write((char*)&head.idLength, sizeof(head.idLength));
	file.write((char*)&head.colorMapType, sizeof(head.colorMapType));
	file.write((char*)&head.dataTypeCode, sizeof(head.dataTypeCode));
	file.write((char*)&head.colorMapOrigin, sizeof(head.colorMapOrigin));
	file.write((char*)&head.colorMapLength, sizeof(head.colorMapLength));
	file.write((char*)&head.colorMapDepth, sizeof(head.colorMapDepth));
	file.write((char*)&head.xOrigin, sizeof(head.xOrigin));
	file.write((char*)&head.yOrigin, sizeof(head.yOrigin));
	file.write((char*)&head.width, sizeof(head.width));
	file.write((char*)&head.height, sizeof(head.height));
	file.write((char*)&head.bitsPerPixel, sizeof(head.bitsPerPixel));
	file.write((char*)&head.imageDescriptor, sizeof(head.imageDescriptor));

	for (int i = 0; i < pixels.size(); i++)
	{
		unsigned char r = pixels.at(i).getRed();
		unsigned char g = pixels.at(i).getGreen();
		unsigned char b = pixels.at(i).getBlue();
		file.write((char*)&b, sizeof(unsigned char));
		file.write((char*)&g, sizeof(unsigned char));
		file.write((char*)&r, sizeof(unsigned char));
	}
}

//testing
void TGAdecon::printPixels(vector<pixel> pix)
{
	for (int i = 0; i < pix.size(); i++)
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
