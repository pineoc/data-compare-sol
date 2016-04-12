#include <iostream>
#include "compare.h"
using namespace std;

int main(int argc, char* argv[])
{
	compare* oCompare = new compare("datas/song1m", "datas/song1f");
	cout << "===========raw similarity check===============" << endl;
	cout << "raw compare pitch: " << oCompare->raw_compare_pitch() << endl;
	cout << "raw compare intensity: " << oCompare->raw_compare_intensity() << endl;
	cout << "raw compare formant: " << oCompare->raw_compare_formant() << endl << endl;
	
	cout << "===========cosine similarity check===============" << endl;
	cout << "cosine compare pitch: " << oCompare->cosine_compare_pitch() << endl;
	cout << "cosine compare intensity: " << oCompare->cosine_compare_intensity() << endl;

	
	return 0;
}
