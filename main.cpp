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
	vector<Pixel> pixels;
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
			file.header = file.getHeader(selection);
			ifstream fil;
			fil.open(selection, ios_base::in | ios_base::binary);
			fil.seekg(18);
			vector<pixel> pixels = file.inputPixels(fil);
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
