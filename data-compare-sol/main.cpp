#include <iostream>
#include <string>
#include "compare.h"
using namespace std;

int main(int argc, char* argv[])
{
	string argv3 = "";
	if (argc > 1)
		argv3 = string(argv[3]);

	if (argv3 == "")
	{ // cpp test dev version sequence
		//you should register two data and update this strings
		string dir = "";
		string file1 = dir + "test4/test4.wav";
		string file2 = dir + "test3/test3.wav";

		compare* oCompare = new compare(file1, file2);

		//set data to array
		oCompare->setFormantData();
		oCompare->setIntensityData();
		oCompare->setPitchData();

		cout << "===========[all stream] raw similarity check===============" << endl;
		cout << "raw compare pitch: " << oCompare->raw_compare_pitch() << endl;
		cout << "raw compare intensity: " << oCompare->raw_compare_intensity() << endl;
		cout << "raw compare formant" << endl;
		cout << "func1: " << oCompare->raw_compare_formant().func2Res << endl;
		cout << "func2: " << oCompare->raw_compare_formant().func3Res << endl;
		cout << endl;


		cout << "===========[all stream] cosine similarity check===============" << endl;
		cout << "cosine compare pitch: " << oCompare->cosine_compare_pitch() << endl;
		cout << "cosine compare intensity: " << oCompare->cosine_compare_intensity() << endl;
		cout << "cosine compare formant" << endl;
		cout << "func2: " << oCompare->cosine_compare_formant().func2Res << endl;
		cout << "func3: " << oCompare->cosine_compare_formant().func3Res << endl;
		cout << endl;

		//median filtering before make datalist
		oCompare->median_function();

		//make data list
		cout << "===========[block] cosine similarity check===============" << endl;
		if (oCompare->makeDataList())
		{//make dataList success
			//block compare start
			auto block_cosine_compare_f_data = oCompare->block_cosine_compare_formant();
			cout << "cosine compare pitch: " << oCompare->block_cosine_compare_pitch() << endl;
			cout << "cosine copmare intensity: " << oCompare->block_cosine_compare_intensity() << endl;
			cout << "cosine compare formant f2: " << block_cosine_compare_f_data.func2Res << endl;
			cout << "cosine compare formant f3: " << block_cosine_compare_f_data.func3Res << endl;
		}
		else
		{//make dataList fail
			cout << "make datalist fail" << endl;
		}
		cout << endl;
	}
	else if (argv3 == "raw")
	{ //release version sequence

		compare* oCompare = new compare(argv[1], argv[2]);

		//set data to array
		oCompare->setFormantData();
		oCompare->setIntensityData();
		oCompare->setPitchData();

		//print to stdout
		double raw_pitch_rate = oCompare->raw_compare_pitch();
		double raw_int_rate = oCompare->raw_compare_intensity();
		auto raw_f_rate = oCompare->raw_compare_formant();
		double raw_formant2_rate = raw_f_rate.func2Res;
		double raw_formant3_rate = raw_f_rate.func3Res;
		if (isnan(raw_pitch_rate))
			raw_pitch_rate = 0.0;
		if (isnan(raw_int_rate))
			raw_int_rate = 0.0;
		if (isnan(raw_formant2_rate))
			raw_formant2_rate = 0.0;
		if (isnan(raw_formant3_rate))
			raw_formant3_rate = 0.0;
		cout << "{ \"pitch_rate\": " << raw_pitch_rate << ",";
		cout << "\"int_rate\": " << raw_int_rate << ",";
		cout << "\"f2_rate\": " << raw_formant2_rate << ",";
		cout << "\"f3_rate\": " << raw_formant3_rate << " }";
	}
	else if (argv3 == "cosine")
	{
		compare* oCompare = new compare(argv[1], argv[2]);

		//set data to array
		oCompare->setFormantData();
		oCompare->setIntensityData();
		oCompare->setPitchData();

		//print to stdout
		double cosine_pitch_rate = oCompare->cosine_compare_pitch();
		double cosine_int_rate = oCompare->cosine_compare_intensity();
		auto cosine_f_rate = oCompare->cosine_compare_formant();
		double cosine_f2_rate = cosine_f_rate.func2Res;
		double cosine_f3_rate = cosine_f_rate.func3Res;
		if (isnan(cosine_pitch_rate))
			cosine_pitch_rate = 0.0;
		if (isnan(cosine_int_rate))
			cosine_int_rate = 0.0;
		if (isnan(cosine_f2_rate))
			cosine_f2_rate = 0.0;
		if (isnan(cosine_f3_rate))
			cosine_f3_rate = 0.0;
		cout << "{ \"pitch_rate\": " << cosine_pitch_rate << ",";
		cout << "\"int_rate\": " << cosine_int_rate << ",";
		cout << "\"f2_rate\": " << cosine_f2_rate << ",";
		cout << "\"f3_rate\": " << cosine_f3_rate << " }";
	}
	else if (argv3 == "median")
	{
		//median + cosine similarity
		compare* oCompare = new compare(argv[1], argv[2]);

		//set data to array
		oCompare->setFormantData();
		oCompare->setIntensityData();
		oCompare->setPitchData();

		//median filtering
		oCompare->median_function();

		//print to stdout
		double cosine_pitch_rate = oCompare->cosine_compare_pitch();
		double cosine_int_rate = oCompare->cosine_compare_intensity();
		auto cosine_f_rate = oCompare->cosine_compare_formant();
		double cosine_f2_rate = cosine_f_rate.func2Res;
		double cosine_f3_rate = cosine_f_rate.func3Res;
		if (isnan(cosine_pitch_rate))
			cosine_pitch_rate = 0.0;
		if (isnan(cosine_int_rate))
			cosine_int_rate = 0.0;
		if (isnan(cosine_f2_rate))
			cosine_f2_rate = 0.0;
		if (isnan(cosine_f3_rate))
			cosine_f3_rate = 0.0;
		cout << "{ \"pitch_rate\": " << cosine_pitch_rate << ",";
		cout << "\"int_rate\": " << cosine_int_rate << ",";
		cout << "\"f2_rate\": " << cosine_f2_rate << ",";
		cout << "\"f3_rate\": " << cosine_f3_rate << " }";

	}
	else if (argv3 == "block_cosine")
	{
		//median + cosine similarity
		compare* oCompare = new compare(argv[1], argv[2]);

		//set data to array
		oCompare->setFormantData();
		oCompare->setIntensityData();
		oCompare->setPitchData();

		//median filtering
		oCompare->median_function();

		//median filtering + data block parsing + cosine similarity
		if (oCompare->makeDataList())
		{//make dataList success
			//print to stdout
			double cosine_pitch_rate = oCompare->block_cosine_compare_pitch();
			double cosine_int_rate = oCompare->block_cosine_compare_intensity();
			auto cosine_f_rate = oCompare->block_cosine_compare_formant();
			double cosine_f2_rate = cosine_f_rate.func2Res;
			double cosine_f3_rate = cosine_f_rate.func3Res;
			if (isnan(cosine_pitch_rate))
				cosine_pitch_rate = 0.0;
			if (isnan(cosine_int_rate))
				cosine_int_rate = 0.0;
			if (isnan(cosine_f2_rate))
				cosine_f2_rate = 0.0;
			if (isnan(cosine_f3_rate))
				cosine_f3_rate = 0.0;
			cout << "{ \"pitch_rate\": " << cosine_pitch_rate << ",";
			cout << "\"int_rate\": " << cosine_int_rate << ",";
			cout << "\"f2_rate\": " << cosine_f2_rate << ",";
			cout << "\"f3_rate\": " << cosine_f3_rate << " }";

		}
		else
		{//make dataList fail
			cout << "{ \"pitch_rate\": " << 0.0 << ",";
			cout << "\"int_rate\": " << 0.0 << ",";
			cout << "\"f2_rate\": " << 0.0 << ",";
			cout << "\"f3_rate\": " << 0.0 << " }";
		}
	}
	else
	{
		compare* oCompare = new compare(argv[1], argv[2]);

		//set data to array
		oCompare->setFormantData();
		oCompare->setIntensityData();
		oCompare->setPitchData();

		//print to stdout
		double cosine_pitch_rate = oCompare->cosine_compare_pitch();
		double cosine_int_rate = oCompare->cosine_compare_intensity();
		auto cosine_f_rate = oCompare->cosine_compare_formant();
		double cosine_f2_rate = cosine_f_rate.func2Res;
		double cosine_f3_rate = cosine_f_rate.func3Res;
		if (isnan(cosine_pitch_rate))
			cosine_pitch_rate = 0.0;
		if (isnan(cosine_int_rate))
			cosine_int_rate = 0.0;
		if (isnan(cosine_f2_rate))
			cosine_f2_rate = 0.0;
		if (isnan(cosine_f3_rate))
			cosine_f3_rate = 0.0;
		cout << "{ \"pitch_rate\": " << cosine_pitch_rate << ",";
		cout << "\"int_rate\": " << cosine_int_rate << ",";
		cout << "\"f2_rate\": " << cosine_f2_rate << ",";
		cout << "\"f3_rate\": " << cosine_f3_rate << " }";
	}

	return 0;
}
