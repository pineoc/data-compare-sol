#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

#define RAW_PITCH_COMPARE_DIFF 5.0f
#define RAW_FORMANT_COMPARE_DIFF 5.0f
#define RAW_INTENSITY_COMPARE_DIFF 5.0f

class compare
{
private:
	//standard of comparison audio data file
	ifstream standardPitchFile;
	ifstream standardFormantFile;
	ifstream standardIntensityFile;

	vector<double> standPitchVec;
	vector<double> standFormantVec;
	vector<double> standIntencityVec;

	//compare audio data file
	ifstream compPitchFile;
	ifstream compFormantFile;
	ifstream compIntensityFile;

	vector<double> compPitchVec;
	vector<double> compFormantVec;
	vector<double> compIntencityVec;

public:
	//init compare object
	compare(string standardDataFilename, string compareDataFilename);
	~compare();

	//read pitch file, insert to pitch vector(stand, comp)
	void setPitchData();
	vector<double> getPitchData();

	//read formant file, insert to formant vector(stand, comp)
	void setFormantData();
	vector<double> getFormantData();

	//read intencity file, insert to intencity vector(stand, comp)
	void setIntensityData();
	vector<double> getIntensityData();

	//raw compare functions
	double raw_compare_pitch();
	double raw_compare_formant();
	double raw_compare_intensity();

	//cosine compare functions
	//return value:
	//1		: same
	//0		: no relation
	//-1	: opposite
	double cosine_compare_pitch();
	double cosine_compare_formant();
	double cosine_compare_intensity();
};

