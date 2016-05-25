#include <iostream>
#include <string>
#include "compare.h"
using namespace std;

#define DEBUG 0

int main(int argc, char* argv[])
{
	//get file number

#if(DEBUG == 0)
	int s_argv1, s_argv2;
	s_argv1 = sizeof(argv[1]) - 4;
	s_argv2 = sizeof(argv[2]) - 4;
	char f1_num = string(argv[1]).at(s_argv1);
	char f2_num = string(argv[2]).at(s_argv2);
#endif

	string argv3 = "";
	if (argc > 1)
		argv3 = string(argv[3]);

	if (argv3 == "")
	{ // cpp test dev version sequence
		//you should register two data and update this strings
		string dir = "";
		string file1 = dir + "test3/test3.wav";
		string file2 = dir + "test4/test4.wav";

		//compare regi1 regi2
		compare* oCompare = new compare(file1, file2);

		//set data to array
		oCompare->setFormantData();
		oCompare->setIntensityData();
		oCompare->setPitchData();

		//compare
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

		cout << "===========[all stream] euclidean similarity check===============" << endl;
		cout << "euclidean compare pitch: " << 
			oCompare->euclidean_compare(oCompare->getStandPitchData(), oCompare->getCompPitchData()) << endl;
		cout << "euclidean compare intensity: " << 
			oCompare->euclidean_compare(oCompare->getStandIntensityData(), oCompare->getCompIntensityData()) << endl;
		cout << endl;

		//result
		double pitch_avg;
		double pitch, intensity, formant2, formant3;
		//median filtering before make datalist
		oCompare->median_function();

		//make data list
		cout << "===========[block] cosine similarity check===============" << endl;
		if (oCompare->makeDataList())
		{//make dataList success
		 //block compare start
			auto block_cosine_compare_f_data = oCompare->block_cosine_compare_formant();
			pitch_avg = oCompare->pitch_average_compare();
			pitch = oCompare->block_cosine_compare_intensity();
			intensity = block_cosine_compare_f_data.func2Res;
			formant2 = block_cosine_compare_f_data.func3Res;
			formant3 = oCompare->pitch_average_compare();
			cout << "cosine compare pitch: " << pitch << endl;
			cout << "cosine copmare intensity: " << intensity << endl;
			cout << "cosine compare formant f2: " << formant2 << endl;
			cout << "cosine compare formant f3: " << formant3 << endl;
			cout << "pitch avg rate: " << pitch_avg << endl;
			//true or false?
			if (pitch_avg > 90.0
				&& pitch > 80.0
				&& intensity > 80.0
				&& formant2 > 90.0
				&& formant3 > 90.0) {
				//true
				//oCompare->combineData(argv[2]);
			}
			else {
				//false
			}
		}
		else
		{//make dataList fail
			cout << "make datalist fail" << endl;
		}
		cout << endl;
	}
#if(DEBUG == 0)
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
		double pitch_avg = oCompare->pitch_average_compare();
		if (isnan(raw_pitch_rate))
			raw_pitch_rate = 0.0;
		if (isnan(raw_int_rate))
			raw_int_rate = 0.0;
		if (isnan(raw_formant2_rate))
			raw_formant2_rate = 0.0;
		if (isnan(raw_formant3_rate))
			raw_formant3_rate = 0.0;
		if (isnan(pitch_avg))
			pitch_avg = 0.0;

		cout << "{ \"pitch_rate\": " << raw_pitch_rate << ",";
		cout << "\"pitch_avg\": " << pitch_avg << ",";
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
		double pitch_avg = oCompare->pitch_average_compare();
		if (isnan(cosine_pitch_rate))
			cosine_pitch_rate = 0.0;
		if (isnan(cosine_int_rate))
			cosine_int_rate = 0.0;
		if (isnan(cosine_f2_rate))
			cosine_f2_rate = 0.0;
		if (isnan(cosine_f3_rate))
			cosine_f3_rate = 0.0;
		if (isnan(pitch_avg))
			pitch_avg = 0.0;

		cout << "{ \"pitch_rate\": " << cosine_pitch_rate << ",";
		cout << "\"pitch_avg\": " << pitch_avg << ",";
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

		double pitch_avg = oCompare->pitch_average_compare();

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
			if (isnan(pitch_avg))
				pitch_avg = 0.0;

			cout << "{ \"pitch_rate\": " << cosine_pitch_rate << ",";
			cout << "\"pitch_avg\": " << pitch_avg << ",";
			cout << "\"int_rate\": " << cosine_int_rate << ",";
			cout << "\"f2_rate\": " << cosine_f2_rate << ",";
			cout << "\"f3_rate\": " << cosine_f3_rate << ",";
			cout << "\"stand_block_num_a\": " << oCompare->getStandDataList().getDataList().size() << ",";
			cout << "\"comp_block_num_a\": " << oCompare->getCompDataList().getDataList().size() << ",";
			cout << "\"stand_block_num\": " << oCompare->getInterpolatedStandVec().getDataList().size() << ",";
			cout << "\"comp_block_num\": " << oCompare->getInterpolatedCompVec().getDataList().size() << ",";
			if (f1_num == '3')
			{//check attendance
				cout << "\"data_valid\": " << 0 << " }";
			}
			else
			{//combine data
			 //corr data set
			 //true or false?
				if (pitch_avg > 80.0
					&& cosine_pitch_rate > 80.0
					&& cosine_int_rate > 80.0
					&& cosine_f2_rate > 90.0
					&& cosine_f3_rate > 90.0)
				{
					//true
					//oCompare->combineData(argv[2]);
					cout << "\"data_valid\": " << 1 << " }";
				}
				else
				{
					cout << "\"data_valid\": " << -1 << " }";
				}
			}
		}
		else
		{//make dataList fail
			cout << "{ \"pitch_rate\": " << 0.0 << ",";
			cout << "\"pitch_avg\": " << pitch_avg << ",";
			cout << "\"int_rate\": " << 0.0 << ",";
			cout << "\"f2_rate\": " << 0.0 << ",";
			cout << "\"f3_rate\": " << 0.0 << ",";
			cout << "\"stand_block_num_a\": " << oCompare->getStandDataList().getDataList().size() << ",";
			cout << "\"comp_block_num_a\": " << oCompare->getCompDataList().getDataList().size() << ",";
			cout << "\"stand_block_num\": " << oCompare->getInterpolatedStandVec().getDataList().size() << ",";
			cout << "\"comp_block_num\": " << oCompare->getInterpolatedCompVec().getDataList().size() << ",";
			cout << "\"data_valid\": " << -1 << " }";
		}
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
		//oCompare->median_function();

		double pitch_avg = oCompare->pitch_average_compare();

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
			cout << "\"pitch_avg\": " << pitch_avg << ",";
			cout << "\"int_rate\": " << cosine_int_rate << ",";
			cout << "\"f2_rate\": " << cosine_f2_rate << ",";
			cout << "\"f3_rate\": " << cosine_f3_rate << ",";
			cout << "\"stand_block_num_a\": " << oCompare->getStandDataList().getDataList().size() << ",";
			cout << "\"comp_block_num_a\": " << oCompare->getCompDataList().getDataList().size() << ",";
			cout << "\"stand_block_num\": "<< oCompare->getInterpolatedStandVec().getDataList().size() << ",";
			cout << "\"comp_block_num\": " << oCompare->getInterpolatedCompVec().getDataList().size() << ",";
			if (f1_num == '3')
			{//check attendance
				cout << "\"data_valid\": " << 0 << " }";
			}
			else
			{//combine data
			 //corr data set
			 //true or false?
				if (pitch_avg > 80.0
					&& cosine_pitch_rate > 80.0
					&& cosine_int_rate > 80.0
					&& cosine_f2_rate > 90.0
					&& cosine_f3_rate > 90.0)
				{
					//true
					//oCompare->combineData(argv[2]);
					cout << "\"data_valid\": " << 1 << " }";
				}
				else
				{
					cout << "\"data_valid\": " << -1 << " }";
				}
			}
		}
		else
		{//make dataList fail
			cout << "{ \"pitch_rate\": " << 0.0 << ",";
			cout << "\"pitch_avg\": " << pitch_avg << ",";
			cout << "\"int_rate\": " << 0.0 << ",";
			cout << "\"f2_rate\": " << 0.0 << ",";
			cout << "\"f3_rate\": " << 0.0 << ",";
			cout << "\"stand_block_num_a\": " << oCompare->getStandDataList().getDataList().size() << ",";
			cout << "\"comp_block_num_a\": " << oCompare->getCompDataList().getDataList().size() << ",";
			cout << "\"stand_block_num\": " << oCompare->getInterpolatedStandVec().getDataList().size() << ",";
			cout << "\"comp_block_num\": " << oCompare->getInterpolatedCompVec().getDataList().size() << ",";
			cout << "\"data_valid\": " << -1 << " }";
		}
	}
#endif

	return 0;
}
