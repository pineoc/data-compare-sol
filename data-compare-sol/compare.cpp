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

//cmompare pitch average
double compare::pitch_average_compare()
{
	//averages
	double std_pitch_average = 0;
	double cmp_pitch_average = 0;

	//get standard pitch averages
	for (int i = 0; i < standPitchVec.size(); i++)
	{
		std_pitch_average += standPitchVec[i];
	}

	std_pitch_average = (std_pitch_average / standPitchVec.size());

	//get compared pitch averages
	for (int i = 0; i < compPitchVec.size(); i++)
	{
		cmp_pitch_average += standPitchVec[i];
	}

	cmp_pitch_average = (cmp_pitch_average / compPitchVec.size());

	//correctness
	return (cmp_pitch_average / std_pitch_average) * 100;
}

vector<double> compare::interpolation(vector<double> _vector, int size)
{
	//size of blocks
	double vector_s = _vector.size();

	int d1, d2, p1, p2;
	int k;

	//new block
	vector<double> temp;
	//initialize temp at 0, sizeof longer one
	temp.assign(size, 0);

	//get term
	double term = size / vector_s;

	//set temp data
	for (int i = 0; i < vector_s; i++)
	{
		int idx = round(i*term);
		temp[idx] = _vector[i];
	}

	//interpolation
	for (int j = 0; j < size; j++)
	{
		if (temp[j] == 0)
		{
			k = j;
			//find p1
			while (temp[k] == 0)
			{
				k--;
			}
			p1 = temp[k];
			d1 = j - k;
			//find p2
			k = j;
			while (temp[k] == 0)
			{
				k++;
			}
			p2 = temp[k];
			d2 = k - j;
				temp[j] = ((d1*p2) + (d2*p1)) / (d1 + d2);
		}
		else
		{
			continue;
		}
	}
	return temp;
}

bool compare::getInterpolatedVector(dataList stand, dataList comp)
{
	//data list size
	int s_stand = stand.getDataList().size();
	int s_comp = comp.getDataList().size();

	//blocks
	int s_std_blk, s_comp_blk;
	int i;

	//temp vectors
	vector<double> tmpPitch;
	vector<double> tmpIntensity;
	vector<double> tmpF2;
	vector<double> tmpF3;

	//two list size must be same
	if (s_stand == s_comp) 
	{
		for (i = 0; i < s_stand; i++)
		{
			//get i_th block
			Data s_data = stand.getDataList()[i];
			Data c_data = comp.getDataList()[i];

			//make new block after interpolation
			Data s_newData;
			Data c_newData;
			
			////pitch
			s_std_blk = s_data.getPitchVec().size();
			s_comp_blk = c_data.getPitchVec().size();

			if (s_std_blk < s_comp_blk)
			{
				//interpolation standard pitch
				tmpPitch = interpolation(s_data.getPitchVec(), s_comp_blk);
				//set pitch vector
				s_newData.setPitchVec(tmpPitch);
				c_newData.setPitchVec(c_data.getPitchVec());
			}
			else 
			{
				//interpolation compared pitch
				tmpPitch = interpolation(c_data.getPitchVec(), s_std_blk);
				s_newData.setPitchVec(s_data.getPitchVec());
				c_newData.setPitchVec(tmpPitch);
			}

			////intensity
			s_std_blk = s_data.getIntVec().size();
			s_comp_blk = c_data.getIntVec().size();

			if (s_std_blk < s_comp_blk)
			{
				//interpolation standard pitch
				tmpIntensity = interpolation(s_data.getIntVec(), s_comp_blk);
				//set intensity vector
				s_newData.setIntVec(tmpIntensity);
				c_newData.setIntVec(c_data.getIntVec());
			}
			else
			{
				//interpolation compared pitch
				tmpIntensity = interpolation(c_data.getIntVec(), s_std_blk);
				//set intensity vector
				s_newData.setIntVec(s_data.getIntVec());
				c_newData.setIntVec(tmpIntensity);
			}

			////formant2
			s_std_blk = s_data.getFormant2Vec().size();
			s_comp_blk = c_data.getFormant2Vec().size();

			if (s_std_blk < s_comp_blk)
			{
				//interpolation standard pitch
				tmpF2 = interpolation(s_data.getFormant2Vec(), s_comp_blk);
				//set formant2 vector
				s_newData.setFormant2Vec(tmpF2);
				c_newData.setFormant2Vec(c_data.getFormant2Vec());
			}
			else
			{
				//interpolation compared pitch
				tmpF2 = interpolation(c_data.getFormant2Vec(), s_std_blk);
				//set formant2 vector
				s_newData.setFormant2Vec(s_data.getFormant2Vec());
				c_newData.setFormant2Vec(tmpF2);
			}

			////formant3
			s_std_blk = s_data.getFormant3Vec().size();
			s_comp_blk = c_data.getFormant3Vec().size();

			if (s_std_blk < s_comp_blk)
			{
				//interpolation standard pitch
				tmpF3 = interpolation(s_data.getFormant3Vec(), s_comp_blk);
				//set formant3 vector
				s_newData.setFormant3Vec(tmpF3);
				c_newData.setFormant3Vec(c_data.getFormant3Vec());
			}
			else
			{
				//interpolation compared pitch
				tmpF3 = interpolation(c_data.getFormant3Vec(), s_std_blk);
				//set formant3 vector
				s_newData.setFormant3Vec(s_data.getFormant3Vec());
				c_newData.setFormant3Vec(tmpF3);
			}

			//make new data list
			interp_stand.pushList(s_newData);
			interp_comp.pushList(c_newData);

		}

		//finish making new dataList
		return true;
	}
	else
	{
		return  false;
	}

}

//rounding func
double compare::round(double value)
{
	double temp;
	temp = value*pow(10, 1);
	temp = floor(temp+0.5);
	temp *= pow(10, -1);
	return temp;
}