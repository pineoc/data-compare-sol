#include <iostream>
#include "compare.h"
using namespace std;

int main(int argc, char* argv[])
{
	compare* oCompare = new compare("datas/song1m", "datas/song2m");
	cout << "raw compare pitch: " << oCompare->raw_compare_pitch() << endl;
	cout << "raw compare intensity: " << oCompare->raw_compare_intensity() << endl;
	
	return 0;
}
