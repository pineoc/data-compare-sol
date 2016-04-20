#include <iostream>
#include "compare.h"
using namespace std;

int main(int argc, char* argv[])
{
	//file name will need ,argv[1], argv[2]
	string file1 = "./datas/person-data/leeyunseok1";
	string file2 = "./datas/person-data/leeyunseok-record";
	compare* oCompare = new compare(file1, file2);
	cout << "Compare program" << endl << "file1 name: " << file1 << endl;
	cout << "file2 name: " << file2 << endl;
	cout << "===========raw similarity check===============" << endl;
	cout << "raw compare pitch: " << oCompare->raw_compare_pitch() << endl;
	cout << "raw compare intensity: " << oCompare->raw_compare_intensity() << endl;
	cout << "raw compare formant" << endl;
	cout << "func1: " << oCompare->raw_compare_formant().func1Res << endl;
	cout << "func2: " << oCompare->raw_compare_formant().func2Res << endl;
	cout << "func3: " << oCompare->raw_compare_formant().func3Res << endl;
	cout << "func4: " << oCompare->raw_compare_formant().func4Res << endl;
	cout << endl;


	cout << "===========cosine similarity check===============" << endl;
	cout << "cosine compare pitch: " << oCompare->cosine_compare_pitch() << endl;
	cout << "cosine compare intensity: " << oCompare->cosine_compare_intensity() << endl;
	cout << "cosine compare formant" << endl;
	cout << "func1: " << oCompare->cosine_compare_formant().func1Res << endl;
	cout << "func2: " << oCompare->cosine_compare_formant().func2Res << endl;
	cout << "func3: " << oCompare->cosine_compare_formant().func3Res << endl;
	cout << "func4: " << oCompare->cosine_compare_formant().func4Res << endl;
	cout << endl;

	cout << "===========euclidean similarity check===============" << endl;
	cout << "euclidean compare pitch: " << oCompare->euclidean_compare_pitch() << endl;
	cout << "euclidean compare intensity: " << oCompare->euclidean_compare_intensity() << endl;
	cout << "euclidean compare formant" << endl;
	cout << "func1: " << oCompare->euclidean_compare_formant().func1Res << endl;
	cout << "func2: " << oCompare->euclidean_compare_formant().func2Res << endl;
	cout << "func3: " << oCompare->euclidean_compare_formant().func3Res << endl;
	cout << "func4: " << oCompare->euclidean_compare_formant().func4Res << endl;
	cout << endl;

	return 0;
}
