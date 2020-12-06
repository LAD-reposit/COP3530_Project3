int main()
{
	vector<Pixel> pixels;
	int choice;
	bool running = true;
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
		else if (choice == 2)
			// READ IN MICKEY MOUSE TO VECTOR OF PIXELS
		else if (choice == 3)
			// READ IN BUCHAREST TO VECTOR OF PIXELS
		else if (choice == 4)
		{
			running = false;
			return 0;
		}
		else
			cout << "Invalid Response." << endl;

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
			BubbleSort(pixels, "Red");
			// STOP TIMER, START NEW TIMER
			// MergeSort(pixels, "Red");
			// STOP TIMER
		}
		else if (choice == 2)
		{
			BubbleSort(pixels, "Green");
			// MergeSort(pixels, "Green");
		}
		else if (choice == 3)
		{
			BubbleSort(pixels, "Blue");
			// MergeSort(pixels, "Blue");
		}
		else if (choice == 4)
		{
			running = false;
			return 0;
		}
    else
			cout << "Invalid Response." << endl;

		// DISPLAY GRADIENT
		cout << "Running time for Bubble Sort: " << endl; // DISPLAY BUBBLE SORT TIME
		cout << "Running time for Merge Sort: " << endl; // DISPLAY MERGE SORT TIME

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
