#include "compare.h"

/*
compare class init
file name
pitch file		: "name-p"
formant file	: "name-f"
intencity file	: "name-i"
*/
compare::compare(string standardDataFilename, string compareDataFilename)
{
	//standard file open
	standardPitchFile = ifstream(string(standardDataFilename + "-p"));
	standardFormantFile = ifstream(string(standardDataFilename + "-f"));
	standardIntensityFile = ifstream(string(standardDataFilename + "-i"));

	//compare file open
	compPitchFile = ifstream(string(compareDataFilename + "-p"));
	compFormantFile = ifstream(string(compareDataFilename + "-f"));
	compIntensityFile = ifstream(string(compareDataFilename + "-i"));
}


compare::~compare()
{
}

void compare::setPitchData()
{
	//read from file standard pitch data
	//start point check
	bool start = false;
	if (standardPitchFile.is_open()) 
	{
		while (!standardPitchFile.eof()) 
		{
			//file read
			string time, point;
			standardPitchFile >> time >> point;

			//set 0 - --undefined-- F0_Hz
			if (!point.compare("--undefined--") || !point.compare("F0_Hz"))
			{
				point = "0";
			}

			if (point != "0")
			{
				start = true;
			}
			//store after start
			if (start)
			{
				standPitchVec.push_back(atof(point.c_str()));
			}
		}

		//remove --undefined-- in the back
		while (1) 
		{
			if (standPitchVec.back() == 0)
				standPitchVec.pop_back();
			else
				break;
		}
	}

	//read from file compare pitch data
	//start point check value set false
	start = false;
	if (compPitchFile.is_open())
	{
		while (!compPitchFile.eof())
		{
			//file read
			string time, point;
			compPitchFile >> time >> point;

			//set 0 - --undefined-- F0_Hz
			if (!point.compare("--undefined--") || !point.compare("F0_Hz"))
			{
				point = "0";
			}

			if (point != "0")
			{
				start = true;
			}
			//store after start
			if (start)
			{
				compPitchVec.push_back(atof(point.c_str()));
			}
		}

		//remove --undefined-- in the back
		while (1)
		{
			if (compPitchVec.back() == 0)
				compPitchVec.pop_back();
			else
				break;
		}
	}
}

vector<double> compare::getPitchData()
{
	return standPitchVec;
}

void compare::setFormantData()
{

}

vector<double> compare::getFormantData()
{
	return standFormantVec;
}

void compare::setIntensityData()
{
	//read from file standard intensity data
	//start point check
	bool start = false;
	if (standardIntensityFile.is_open())
	{
		while (!standardIntensityFile.eof())
		{
			//file read
			string time, point;
			standardIntensityFile >> time >> point;

			//set 0 - --undefined-- F0_Hz
			if (!point.compare("--undefined--") || !point.compare("Intensity_dB"))
			{
				point = "0";
			}

			if (point != "0")
			{
				start = true;
			}
			//store after start
			if (start)
			{
				standIntencityVec.push_back(atof(point.c_str()));
			}
		}

	}

	//read from file compare pitch data
	//start point check value set false
	start = false;
	if (compIntensityFile.is_open())
	{
		while (!compIntensityFile.eof())
		{
			//file read
			string time, point;
			compIntensityFile >> time >> point;

			//set 0 - --undefined-- F0_Hz
			if (!point.compare("--undefined--") || !point.compare("Intensity_dB"))
			{
				point = "0";
			}

			if (point != "0")
			{
				start = true;
			}
			//store after start
			if (start)
			{
				compIntencityVec.push_back(atof(point.c_str()));
			}
		}

	}
}

vector<double> compare::getIntensityData()
{
	return standIntencityVec;
}

double compare::raw_compare_pitch()
{
	setPitchData();
	/*compare two voice*/
	//exist both data - compare
	int pos = 0;
	vector<bool> correct;
	int correctCnt = 0;
	int min = 0;
	if (standPitchVec.size() > compPitchVec.size())
	{
		min = compPitchVec.size();
	}
	else
	{
		min = standPitchVec.size();
	}

	while (min > 0) {
		while (standPitchVec[pos] != 0 && compPitchVec[pos] != 0)
		{
			//male-10 < female < male+10 ? check similar.
			if (abs(standPitchVec[pos] - compPitchVec[pos]) < RAW_PITCH_COMPARE_DIFF)
			{
				correct.push_back(true);
				correctCnt++;
			}
			else
			{
				correct.push_back(false);
			}
			pos++;
		}
		min--;
	}
	//print corrected count, percent
	//cout << "corrected count: " << correctCnt << endl;
	//cout << "corrected percent: " << (double)correctCnt / (double)fSound * 100 << "%" << endl;
	return (double)correctCnt / (double)pos * 100;
}

double compare::raw_compare_formant()
{
	return 0.0;
}

double compare::raw_compare_intensity()
{
	setIntensityData();
	/*compare two voice*/
	//exist both data - compare
	int pos = 0;
	vector<bool> correct;
	int correctCnt = 0;
	int min = 0;
	if (standIntencityVec.size() > compIntencityVec.size())
	{
		min = compIntencityVec.size();
	}
	else
	{
		min = standIntencityVec.size();
	}

	while (min > 0) {
		while (standIntencityVec[pos] != 0 && compIntencityVec[pos] != 0)
		{
			//male-10 < female < male+10 ? check similar.
			if (abs(standIntencityVec[pos] - compIntencityVec[pos]) < RAW_INTENSITY_COMPARE_DIFF)
			{
				correct.push_back(true);
				correctCnt++;
			}
			else
			{
				correct.push_back(false);
			}
			pos++;
		}
		min--;
	}
	//print corrected count, percent
	//cout << "corrected count: " << correctCnt << endl;
	//cout << "corrected percent: " << (double)correctCnt / (double)fSound * 100 << "%" << endl;
	return (double)correctCnt / (double)pos * 100;
}

double compare::cosine_compare_pitch()
{
	return 0.0;
}

double compare::cosine_compare_formant()
{
	return 0.0;
}

double compare::cosine_compare_intensity()
{
	return 0.0;
}
