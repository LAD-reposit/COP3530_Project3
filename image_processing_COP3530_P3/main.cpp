#include "pixel.h"
#include "TGAdecon.h"

int main() 
{
	TGAdecon file;
	string selection = file.whichFile(1);
	file.header = file.getHeader(selection);
	
	ifstream fil;
	fil.open(selection, ios_base::in | ios_base::binary);
	fil.seekg(18);
	vector<pixel> pixels = file.inputPixels(fil);
	fil.close();
	//file.printPixels(pixels);

	string outfile = file.whichOutput(selection);
	cout << outfile << endl;
	ofstream clos;
	clos.open(outfile, ios_base::out | ios_base::binary);
	file.writeFile(clos, file.header, pixels);
	clos.close();

};