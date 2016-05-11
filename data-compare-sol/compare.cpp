#include "compare.h"

/*
compare class init
file name
pitch file		: "name-p.out"
formant file	: "name-f.out"
intencity file	: "name-i.out"
*/
compare::compare(string standardDataFilename, string compareDataFilename)
{
	//set file to vector
	//standard file open
	standardPitchFile = ifstream(string(standardDataFilename + "-p.out"));
	standardFormantFile = ifstream(string(standardDataFilename + "-f.out"));
	standardIntensityFile = ifstream(string(standardDataFilename + "-i.out"));

	//compare file open
	compPitchFile = ifstream(string(compareDataFilename + "-p.out"));
	compFormantFile = ifstream(string(compareDataFilename + "-f.out"));
	compIntensityFile = ifstream(string(compareDataFilename + "-i.out"));
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

			//if pitch
			if (!point.compare("pitch"))
				continue;

			if (!point.compare("--undefined--"))
			{
				point = "0";
			}

			//push to vector
			standPitchVec.push_back(atof(point.c_str()));
			
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

			//set 0 - --undefined-- pitch
			//if pitch
			if (!point.compare("pitch"))
				continue;

			if (!point.compare("--undefined--"))
			{
				point = "0";
			}

			//push to vector
			compPitchVec.push_back(atof(point.c_str()));
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
	//read from file standard intensity data

	if (standardFormantFile.is_open())
	{
		while (!standardFormantFile.eof())
		{
			//file read
			string time, func2, func3;
			standardFormantFile >> time >> func2 >> func3;

			//set 0 - --undefined-- f2
			if (!func2.compare("f2"))
				continue;
			!func2.compare("--undefined--") ? func2 = "0.0" : func2 = func2;
			!func3.compare("--undefined--") ? func3 = "0.0" : func3 = func3;

			standFormant2Vec.push_back(atof(func2.c_str()));
			standFormant3Vec.push_back(atof(func3.c_str()));
		}
	}

	//read from file compare pitch data
	if (compFormantFile.is_open())
	{
		while (!compFormantFile.eof())
		{
			//file read
			string time, func2, func3;
			compFormantFile >> time >> func2 >> func3;

			//set 0 - --undefined-- f2
			if (!func2.compare("f2"))
				continue;
			!func2.compare("--undefined--") ? func2 = "0.0" : func2 = func2;
			!func3.compare("--undefined--") ? func3 = "0.0" : func3 = func3;

			compFormant2Vec.push_back(atof(func2.c_str()));
			compFormant3Vec.push_back(atof(func3.c_str()));
		}
	}
}

vector<double> compare::getFormantData()
{
	return standFormant2Vec;
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

			//set 0 - --undefined-- intensity
			if (!point.compare("--undefined--") || !point.compare("intensity"))
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

			//set 0 - --undefined-- intensity
			if (!point.compare("--undefined--") || !point.compare("intensity"))
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
				compIntensityVec.push_back(atof(point.c_str()));
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
	/*compare two voice*/
	//exist both data - compare
	int pos = 0;
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
				correctCnt++;

			pos++;
		}
		min--;
	}
	//return corrected count, percent
	return (double)correctCnt / (double)pos * 100;
}

formantCompResultType compare::raw_compare_formant()
{

	//result data init
	formantCompResultType result;
	result.func2Res = 0.0;
	result.func3Res = 0.0;

	//compare start
	/*compare two voice*/
	//exist both data - compare
	int correctCnt2 = 0, correctCnt3 = 0;
	int vecLength = 0;

	vecLength = min(compFormant2Vec.size(), standFormant2Vec.size());

	//formant functions compare
	for (int i = 0; i < vecLength; i++)
	{
		
		//function2 compare
		if (abs(standFormant2Vec[i] - compFormant2Vec[i]) < RAW_FORMANT_COMPARE_DIFF)
			correctCnt2++;
		//function3 compare
		if (abs(standFormant3Vec[i] - compFormant3Vec[i]) < RAW_FORMANT_COMPARE_DIFF)
			correctCnt3++;
		
	}

	result.func2Res = (double)correctCnt2 / (double)vecLength * 100;
	result.func3Res = (double)correctCnt3 / (double)vecLength * 100;

	return result;
}

double compare::raw_compare_intensity()
{
	//compare start
	/*compare two voice*/
	//exist both data - compare
	int correctCnt = 0;
	int min = 0;
	if (standIntencityVec.size() > compIntensityVec.size())
		min = compIntensityVec.size();
	else
		min = standIntencityVec.size();

	for (int i = 0; i < min; i++)
	{
		//male-10 < female < male+10 ? check similar.
		if (abs(standIntencityVec[i] - compIntensityVec[i]) < RAW_INTENSITY_COMPARE_DIFF)
			correctCnt++;
	}
	//return corrected count, percent
	return (double)correctCnt / (double)min * 100;
}

double compare::cosine_compare_pitch()
{
	double similarityValue = 0.0;
	double topValue = 0.0;
	double bottomValue = 0.0;
	double bottomVal1 = 0.0, bottomVal2 = 0.0;

	//vector length set
	int vecLength = min(standPitchVec.size(), compPitchVec.size());

	//top value sum
	for (int i = 0; i < vecLength; i++)
		topValue += standPitchVec[i] * compPitchVec[i];

	for (int i = 0; i < vecLength; i++)
	{
		bottomVal1 += pow(standPitchVec[i], 2);
		bottomVal2 += pow(compPitchVec[i], 2);
	}
	bottomValue = sqrt(bottomVal1) * sqrt(bottomVal2);
	similarityValue = topValue / bottomValue;
	return similarityValue * 100;
}

formantCompResultType compare::cosine_compare_formant()
{
	double similarityValue = 0.0;
	double topValue = 0.0;
	double bottomValue = 0.0;
	double bottomVal1 = 0.0, bottomVal2 = 0.0;

	//result data init
	formantCompResultType result;
	result.func2Res = 0.0;
	result.func3Res = 0.0;

	//vector length set
	int vecLength = min(standFormant2Vec.size(), compFormant2Vec.size());


	//values set to 0.0
	topValue = 0.0;
	bottomVal1 = 0.0;
	bottomVal2 = 0.0;
	bottomValue = 0.0;
	similarityValue = 0.0;

	//formant function2 cosine similarity
	//top value sum
	for (int i = 0; i < vecLength; i++)
		topValue += standFormant2Vec[i] * compFormant2Vec[i];

	for (int i = 0; i < vecLength; i++)
	{
		bottomVal1 += pow(standFormant2Vec[i], 2);
		bottomVal2 += pow(compFormant2Vec[i], 2);
	}
	bottomValue = sqrt(bottomVal1) * sqrt(bottomVal2);
	similarityValue = topValue / bottomValue;

	result.func2Res = similarityValue * 100;

	//values set to 0.0
	topValue = 0.0;
	bottomVal1 = 0.0;
	bottomVal2 = 0.0;
	bottomValue = 0.0;
	similarityValue = 0.0;

	//formant function3 cosine similarity
	//top value sum
	for (int i = 0; i < vecLength; i++)
		topValue += standFormant3Vec[i] * compFormant3Vec[i];

	for (int i = 0; i < vecLength; i++)
	{
		bottomVal1 += pow(standFormant3Vec[i], 2);
		bottomVal2 += pow(compFormant3Vec[i], 2);
	}
	bottomValue = sqrt(bottomVal1) * sqrt(bottomVal2);
	similarityValue = topValue / bottomValue;

	result.func3Res = similarityValue * 100;

	return result;
}

double compare::cosine_compare_intensity()
{
	double similarityValue = 0.0;
	double topValue = 0.0;
	double bottomValue = 0.0;
	double bottomVal1 = 0.0, bottomVal2 = 0.0;

	//vector length set
	int vecLength = min(standIntencityVec.size(), compIntensityVec.size());

	//top value sum
	for (int i = 0; i < vecLength; i++)
		topValue += standIntencityVec[i] * compIntensityVec[i];

	for (int i = 0; i < vecLength; i++)
	{
		bottomVal1 += pow(standIntencityVec[i], 2);
		bottomVal2 += pow(compIntensityVec[i], 2);
	}
	bottomValue = sqrt(bottomVal1) * sqrt(bottomVal2);
	similarityValue = topValue / bottomValue;
	return similarityValue * 100;
}
/*
double compare::euclidean_compare_pitch()
{
	double value1 = 0.0;
	double result = 0.0;

	int vecLength = min(standPitchVec.size(), compPitchVec.size());

	//sum of pow2, (p-q)^2
	for (int i = 0; i < vecLength; i++)
		value1 += pow((standPitchVec[i] - compPitchVec[i]), 2);

	result = sqrt(value1);
	result = 1.0 / (1.0 + result) * 100;
	return result;
}

formantCompResultType compare::euclidean_compare_formant()
{
	return formantCompResultType();
}

double compare::euclidean_compare_intensity()
{
	double value1 = 0.0;
	double result = 0.0;

	int vecLength = min(standIntencityVec.size(), compIntencityVec.size());

	//sum of pow2, (p-q)^2
	for (int i = 0; i < vecLength; i++)
		value1 += pow((standIntencityVec[i] - compIntencityVec[i]), 2);

	result = sqrt(value1);

	return 1.0 / (1.0 + result) * 100;
}
*/

void compare::median_function()
{
	double filter[5];
	vector<double> tmpVec;
	tmpVec.assign(compPitchVec.size(), 0.0);

	//pitch vector median
	for (int i = 0; i < compPitchVec.size() - 4; i++)
	{
		filter[0] = compPitchVec[i];
		filter[1] = compPitchVec[i + 1];
		filter[2] = compPitchVec[i + 2];
		filter[3] = compPitchVec[i + 3];
		filter[4] = compPitchVec[i + 4];

		sort(filter, filter + 5);
		tmpVec[i + 2] = filter[2];
	}
	compPitchVec = tmpVec;
	
	//intensity median
	tmpVec.clear();
	tmpVec.assign(compIntensityVec.size(), 0.0);
	for (int i = 0; i < compIntensityVec.size() - 4; i++)
	{
		filter[0] = compIntensityVec[i];
		filter[1] = compIntensityVec[i + 1];
		filter[2] = compIntensityVec[i + 2];
		filter[3] = compIntensityVec[i + 3];
		filter[4] = compIntensityVec[i + 4];

		sort(filter, filter + 5);
		tmpVec[i + 2] = filter[2];
	}
	compIntensityVec = tmpVec;


	//f2 median
	tmpVec.clear();
	tmpVec.assign(compFormant2Vec.size(), 0.0);
	for (int i = 0; i < compFormant2Vec.size() - 2; i++)
	{
		filter[0] = compFormant2Vec[i];
		filter[1] = compFormant2Vec[i + 1];
		filter[2] = compFormant2Vec[i + 2];

		sort(filter, filter + 3);
		tmpVec[i + 1] = filter[1];
	}
	compFormant2Vec = tmpVec;

	//f3 median
	tmpVec.clear();
	tmpVec.assign(compFormant3Vec.size(), 0.0);
	for (int i = 0; i < compFormant3Vec.size() - 2; i++)
	{
		filter[0] = compFormant3Vec[i];
		filter[1] = compFormant3Vec[i + 1];
		filter[2] = compFormant3Vec[i + 2];
		
		sort(filter, filter + 3);
		tmpVec[i + 1] = filter[1];
	}
	compFormant3Vec = tmpVec;
}

void compare::makeDataList()
{
	dataList* standDL = new dataList(standPitchVec, standFormant2Vec, standFormant3Vec, standIntencityVec);
	dataList* compDL = new dataList(compPitchVec, compFormant2Vec, compFormant3Vec, compIntensityVec);

	cout << "" << endl;
}
