#include <iostream>
#include <string>
#include "compare.h"
using namespace std;

int main(int argc, char* argv[])
{
	string argv3 = "";
	if(argc > 1)
		argv3 = string(argv[3]);

	if (argv3 == "")
	{ // cpp test dev version sequence
		//you should register two data and update this strings
		string dir = "";
		string file1 = dir + "test1/test1_1.wav";
		string file2 = dir + "test3/test3.wav";

		compare* oCompare = new compare(file1, file2);

		//set data to array
		oCompare->setFormantData();
		oCompare->setIntensityData();
		oCompare->setPitchData();

		cout << "===========raw similarity check===============" << endl;
		cout << "raw compare pitch: " << oCompare->raw_compare_pitch() << endl;
		cout << "raw compare intensity: " << oCompare->raw_compare_intensity() << endl;
		cout << "raw compare formant" << endl;
		cout << "func2: " << oCompare->raw_compare_formant().func2Res << endl;
		cout << "func3: " << oCompare->raw_compare_formant().func3Res << endl;
		cout << endl;


		cout << "===========cosine similarity check===============" << endl;
		cout << "cosine compare pitch: " << oCompare->cosine_compare_pitch() << endl;
		cout << "cosine compare intensity: " << oCompare->cosine_compare_intensity() << endl;
		cout << "cosine compare formant" << endl;
		cout << "func2: " << oCompare->cosine_compare_formant().func2Res << endl;
		cout << "func3: " << oCompare->cosine_compare_formant().func3Res << endl;
		cout << endl;

		oCompare->median_function();

		//test make data list
		oCompare->makeDataList();

	}
	else
	{ //release version sequence

		compare* oCompare = new compare(argv[1], argv[2]);

		//set data to array
		oCompare->setFormantData();
		oCompare->setIntensityData();
		oCompare->setPitchData();

		//print to stdout
		double cosine_pitch_rate = oCompare->cosine_compare_pitch();
		double cosine_int_rate = oCompare->cosine_compare_intensity();
		if (isnan(cosine_pitch_rate))
			cosine_pitch_rate = 0.0;
		if (isnan(cosine_int_rate))
			cosine_int_rate = 0.0;
		cout << "{ \"pitch_rate\": " << cosine_pitch_rate << ",";
		cout << "\"int_rate\": " << cosine_int_rate << "}";
	}



	return 0;
}
