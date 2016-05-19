#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

#include "dataList.h"

#define RAW_PITCH_COMPARE_DIFF 5.0f
#define RAW_FORMANT_COMPARE_DIFF 20.0f
#define RAW_INTENSITY_COMPARE_DIFF 5.0f

struct formantCompResultType {
	double func2Res;
	double func3Res;
};

class compare
{
private:
	//standard of comparison audio data file
	ifstream standardPitchFile;
	ifstream standardFormantFile;
	ifstream standardIntensityFile;

	vector<double> standPitchVec;
	vector<double> standFormant2Vec;
	vector<double> standFormant3Vec;
	vector<double> standIntencityVec;

	//compare audio data file
	ifstream compPitchFile;
	ifstream compFormantFile;
	ifstream compIntensityFile;

	vector<double> compPitchVec;
	vector<double> compFormant2Vec;
	vector<double> compFormant3Vec;
	vector<double> compIntensityVec;

	//before interpolate dataList
	dataList* standDL;
	dataList* compDL;

	//after interpolated dataList
	dataList interp_stand;
	dataList interp_comp;

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
	formantCompResultType raw_compare_formant();
	double raw_compare_intensity();

	//cosine compare functions
	//return value:
	//1		: same
	//0		: no relation
	//-1	: opposite
	double cosine_compare_pitch();
	formantCompResultType cosine_compare_formant();
	double cosine_compare_intensity();

	//Euclidean distance
	//double euclidean_compare_pitch();
	//formantCompResultType euclidean_compare_formant();
	//double euclidean_compare_intensity();

	//based blockList compare, cosine similarity
	double block_cosine_compare_pitch();
	formantCompResultType block_cosine_comapre_formant();
	double block_cosine_compare_intensity();

	//get cosine similarity value of two vectors
	double getCosineSimilarity(vector<double> v1, vector<double> v2);

	//median filtering
	void median_function();

	//cmompare pitch average
	double pitch_average_compare();

	//DataList logic functions
	bool makeDataList();

	//interpolate functions
	vector<double> interpolation(vector<double> _vector, int size);
	bool getInterpolatedVector(dataList stand, dataList comp);
	double round(double value);
};
