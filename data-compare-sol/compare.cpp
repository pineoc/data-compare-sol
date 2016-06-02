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
	standardMFCCFile = ifstream(string(standardDataFilename + "-mfcc.out"));

	//compare file open
	compPitchFile = ifstream(string(compareDataFilename + "-p.out"));
	compFormantFile = ifstream(string(compareDataFilename + "-f.out"));
	compIntensityFile = ifstream(string(compareDataFilename + "-i.out"));
	compMFCCFile = ifstream(string(compareDataFilename + "-mfcc.out"));
}


compare::~compare()
{
}

void compare::setPitchData()
{
	//read from file standard pitch data
	//start point check
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

	}

	//read from file compare pitch data
	//start point check value set false
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

	}
}

vector<double> compare::getStandPitchData()
{
	return standPitchVec;
}
vector<double> compare::getCompPitchData()
{
	return compPitchVec;
}

void compare::setFormantData()
{
	//read from file standard Formant data

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

	//read from file compare Formant data
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
	if (standardIntensityFile.is_open())
	{
		while (!standardIntensityFile.eof())
		{
			//file read
			string time, point;
			standardIntensityFile >> time >> point;

			//set 0 - --undefined-- intensity
			if (!point.compare("intensity"))
				continue;

			if (!point.compare("--undefined--"))
			{
				point = "0";
			}

			standIntensityVec.push_back(atof(point.c_str()));

		}

	}

	//read from file compare intensity data
	if (compIntensityFile.is_open())
	{
		while (!compIntensityFile.eof())
		{
			//file read
			string time, point;
			compIntensityFile >> time >> point;

			//set 0 - --undefined-- intensity
			if (!point.compare("intensity"))
				continue;

			if (!point.compare("--undefined--"))
			{
				point = "0";
			}
			//store after start
			compIntensityVec.push_back(atof(point.c_str()));
		}
	}
}

vector<double> compare::getStandIntensityData()
{
	return standIntensityVec;
}
vector<double> compare::getCompIntensityData()
{
	return compIntensityVec;
}
void compare::setMFCCData()
{
	//read from file standard mfcc data
	if (standardMFCCFile.is_open())
	{
		while (!standardMFCCFile.eof())
		{
			//file read
			string time, point;
			standardMFCCFile >> time >> point;

			//if pitch
			if (!point.compare("c0"))
				continue;

			if (!point.compare("--undefined--"))
			{
				point = "0";
			}

			//push to vector
			standMFCCVec.push_back(atof(point.c_str()));
		}
	}

	//read from file compare mfcc data
	if (compMFCCFile.is_open())
	{
		while (!compMFCCFile.eof())
		{
			//file read
			string time, point;
			compMFCCFile >> time >> point;

			//set 0 - --undefined-- pitch
			//if c0
			if (!point.compare("c0"))
				continue;

			if (!point.compare("--undefined--"))
			{
				point = "0";
			}

			//push to vector
			compMFCCVec.push_back(atof(point.c_str()));
		}
	}
}
vector<double> compare::getStandMFCCData()
{
	return standMFCCVec;
}
vector<double> compare::getCompMFCCData()
{
	return compMFCCVec;
}
void compare::setMFCCInterpolate()
{
	int standVecSize = standMFCCVec.size();
	int compVecSize = compMFCCVec.size();
	if (standVecSize > compVecSize)
	{
		compMFCCVec = interpolation(compMFCCVec, standVecSize);
	}
	else
	{
		standMFCCVec = interpolation(standMFCCVec, compVecSize);
	}

}
int compare::getDTWDistance(vector<double> v1, vector<double> v2)
{
	int cost = 0;
	int v1_size = v1.size();
	int v2_size = v2.size();
	vector<vector<int> > arr(v1_size, vector<int>(v2_size, 0));

	for (int i = 1; i < v1_size; i++)
	{
		arr[i][0] = 10000;//infinite value
	}
	for (int i = 1; i < v2_size; i++)
	{
		arr[0][i] = 10000;//infinite value
	}
	arr[0][0] = 0;

	for (int i = 0; i < v1_size; i++)
	{
		for (int j = 0; j < v2_size; j++)
		{

		}
	}

	return 0;
}
dataList compare::getStandDataList()
{
	return *standDL;
}

dataList compare::getCompDataList()
{
	return *compDL;
}

dataList compare::getInterpolatedStandVec()
{
	return interp_stand;
}

dataList compare::getInterpolatedCompVec()
{
	return interp_comp;
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
	if (standIntensityVec.size() > compIntensityVec.size())
		min = compIntensityVec.size();
	else
		min = standIntensityVec.size();

	for (int i = 0; i < min; i++)
	{
		//male-10 < female < male + 10 ? check similar.
		if (abs(standIntensityVec[i] - compIntensityVec[i]) < RAW_INTENSITY_COMPARE_DIFF)
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
	int vecLength = min(standIntensityVec.size(), compIntensityVec.size());

	//top value sum
	for (int i = 0; i < vecLength; i++)
		topValue += standIntensityVec[i] * compIntensityVec[i];

	for (int i = 0; i < vecLength; i++)
	{
		bottomVal1 += pow(standIntensityVec[i], 2);
		bottomVal2 += pow(compIntensityVec[i], 2);
	}
	bottomValue = sqrt(bottomVal1) * sqrt(bottomVal2);
	similarityValue = topValue / bottomValue;
	return similarityValue * 100;
}

double compare::euclidean_compare(vector<double> v1, vector<double> v2)
{
	double value1 = 0.0;
	double result = 0.0;
	vector<double> tmpVec1, tmpVec2;
	tmpVec1 = v1;
	tmpVec2 = v2;
	if (v1.size() > v2.size())
		tmpVec2 = interpolation(tmpVec2, v1.size());
	else
		tmpVec1 = interpolation(tmpVec1, v2.size());

	int vecLength = tmpVec1.size();

	//sum of pow2, (p-q)^2
	for (int i = 0; i < vecLength; i++)
		value1 += pow((tmpVec1[i] - tmpVec2[i]), 2);

	result = sqrt(value1);
	result = 1.0 / (1.0 + result) * 100;
	return result;
}

double compare::block_cosine_compare_pitch()
{
	//get datalist size
	int comp_vec_size = interp_stand.getDataList().size();
	double result = 0.0;

	//compare start
	for (int i = 0; i < comp_vec_size; i++)
	{
		Data stand_d = interp_stand.getDataList()[i];
		Data comp_d = interp_comp.getDataList()[i];
		double comp_res = getCosineSimilarity(stand_d.getPitchVec(), comp_d.getPitchVec());
		result += comp_res;
	}
	result = result / (double)comp_vec_size;
	return result;
}

formantCompResultType compare::block_cosine_compare_formant()
{
	//get datalist size
	int comp_vec_size = interp_stand.getDataList().size();
	formantCompResultType result = { 0.0, 0.0 };

	//compare start
	for (int i = 0; i < comp_vec_size; i++)
	{
		Data stand_d = interp_stand.getDataList()[i];
		Data comp_d = interp_comp.getDataList()[i];
		double comp_res_f2 = getCosineSimilarity(stand_d.getFormant2Vec(), comp_d.getFormant2Vec());
		double comp_res_f3 = getCosineSimilarity(stand_d.getFormant3Vec(), comp_d.getFormant3Vec());
		result.func2Res += comp_res_f2;
		result.func3Res += comp_res_f3;
	}
	result.func2Res = result.func2Res / (double)comp_vec_size;
	result.func3Res = result.func3Res / (double)comp_vec_size;
	return result;
}

double compare::block_cosine_compare_intensity()
{
	//get datalist size
	int comp_vec_size = interp_stand.getDataList().size();
	double result = 0.0;

	//compare start
	for (int i = 0; i < comp_vec_size; i++)
	{
		Data stand_d = interp_stand.getDataList()[i];
		Data comp_d = interp_comp.getDataList()[i];
		double comp_res = getCosineSimilarity(stand_d.getIntVec(), comp_d.getIntVec());
		result += comp_res;
	}
	result = result / (double)comp_vec_size;
	return result;
}

double compare::getCosineSimilarity(vector<double> v1, vector<double> v2)
{
	double similarityValue = 0.0;
	double topValue = 0.0;
	double bottomValue = 0.0;
	double bottomVal1 = 0.0, bottomVal2 = 0.0;

	//vector length set
	int vecLength = v1.size();

	//top value sum
	for (int i = 0; i < vecLength; i++)
		topValue += v1[i] * v2[i];

	for (int i = 0; i < vecLength; i++)
	{
		bottomVal1 += pow(v1[i], 2);
		bottomVal2 += pow(v2[i], 2);
	}
	bottomValue = sqrt(bottomVal1) * sqrt(bottomVal2);
	similarityValue = topValue / bottomValue;
	return similarityValue * 100;
}

double compare::getCosineSimilarityEnhanced(vector<double> v1, vector<double> v2)
{
	unsigned int vectorLength = v2.size();
	double dot = 0.0, denom_a = 0.0, denom_b = 0.0;
	for (unsigned int i = 0u; i < vectorLength; ++i) {
		dot += v1[i] * v2[i];
		denom_a += v1[i] * v1[i];
		denom_b += v2[i] * v2[i];
	}
	return dot / (sqrt(denom_a) * sqrt(denom_b));
}

void compare::median_function()
{
	double filter[5];
	vector<double> tmpVec;
	tmpVec.assign(compPitchVec.size(), 0.0);

	//pitch vector median
	int pitchSize = compPitchVec.size();
	for (int i = 0; i < pitchSize - 4; i++)
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
	int intensitySize = compIntensityVec.size();
	for (int i = 0; i < intensitySize - 4; i++)
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
	int f2Size = compFormant2Vec.size();
	for (int i = 0; i < f2Size - 2; i++)
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
	int f3Size = compFormant3Vec.size();
	for (int i = 0; i < f3Size - 2; i++)
	{
		filter[0] = compFormant3Vec[i];
		filter[1] = compFormant3Vec[i + 1];
		filter[2] = compFormant3Vec[i + 2];

		sort(filter, filter + 3);
		tmpVec[i + 1] = filter[1];
	}
	compFormant3Vec = tmpVec;
}

bool compare::makeDataList()
{
	standDL = new dataList(standPitchVec, standFormant2Vec, standFormant3Vec, standIntensityVec);
	compDL = new dataList(compPitchVec, compFormant2Vec, compFormant3Vec, compIntensityVec);

	if (getInterpolatedVector(*standDL, *compDL))
		return true;
	else
		//error on get interpolation
		return false;
}

//cmompare pitch average
double compare::pitch_average_compare()
{
	//averages
	double std_pitch_average = 0;
	double cmp_pitch_average = 0;

	//get standard pitch averages
	int standPitchSize = standPitchVec.size();
	int count = 0;
	for (int i = 0; i < standPitchSize; i++)
	{
		if (standPitchVec[i] != 0.0)
		{
			std_pitch_average += standPitchVec[i];
			count++;
		}
	}

	std_pitch_average = (std_pitch_average / count);

	//get compared pitch averages
	int compPitchSize = compPitchVec.size();
	count = 0;
	for (int i = 0; i < compPitchSize; i++)
	{
		if (compPitchVec[i] != 0.0)
		{
			cmp_pitch_average += compPitchVec[i];
			count++;
		}
	}

	cmp_pitch_average = (cmp_pitch_average / count);

	//correctness
	if (cmp_pitch_average > std_pitch_average)
		return (std_pitch_average / cmp_pitch_average) * 100;
	else
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
	temp.assign(size, -1);

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
		if (temp[j] == -1)
		{
			k = j;
			//find p1
			while (temp[k] == -1)
			{
				k--;
			}
			p1 = temp[k];
			d1 = j - k;
			//find p2
			k = j;
			while (temp[k] == -1 && k < size - 1)
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
	temp = floor(temp + 0.5);
	temp *= pow(10, -1);
	return temp;
}

void compare::combineData(string outFileName)
{
	//outfile pitch stream
	ofstream outfile_p;
	string p_str = outFileName + "-p.out";
	outfile_p.open(p_str);

	//outfile intensity stream
	ofstream outfile_i;
	string i_str = outFileName + "-i.out";
	outfile_p.open(i_str);

	//outfile formant stream
	ofstream outfile_f;
	string f_str = outFileName + "-f.out";
	outfile_p.open(f_str);

	//two vector size
	int s_v1, s_v2;

	//new vector
	vector<double> tempVec;

	//pitch
	s_v1 = standPitchVec.size();
	s_v2 = compPitchVec.size();

	if (s_v1 > s_v2) {
		//pitch
		//get tempVec - interpolation
		tempVec = interpolation(compPitchVec, s_v1);
		//combine stand + temp
		for (int i = 0; i < s_v1; i++) {
			standPitchVec[i] = (standPitchVec[i] + tempVec[i]) / 2.0;
		}
		tempVec.clear();

		//intensity
		tempVec = interpolation(compIntensityVec, s_v1);
		//combine stand + temp
		for (int i = 0; i < s_v1; i++) {
			standIntensityVec[i] = (standIntensityVec[i] + tempVec[i]) / 2.0;
		}
		tempVec.clear();

		//formant2
		tempVec = interpolation(compFormant2Vec, s_v1);
		//combine stand + temp
		for (int i = 0; i < s_v1; i++) {
			standFormant2Vec[i] = (standFormant2Vec[i] + tempVec[i]) / 2.0;
		}
		tempVec.clear();

		//formant3
		tempVec = interpolation(compFormant3Vec, s_v1);
		//combine stand + temp
		for (int i = 0; i < s_v1; i++) {
			standFormant3Vec[i] = (standFormant3Vec[i] + tempVec[i]) / 2.0;
		}
		tempVec.clear();

	}
	else {
		//pitch
		//get tempVec - interpolation
		tempVec = interpolation(standPitchVec, s_v1);
		//combine comp + temp
		for (int i = 0; i < s_v1; i++) {
			standPitchVec[i] = (compPitchVec[i] + tempVec[i]) / 2.0;
		}
		tempVec.clear();

		//intensity
		tempVec = interpolation(standIntensityVec, s_v1);
		//combine comp + temp
		for (int i = 0; i < s_v1; i++) {
			standIntensityVec[i] = (compIntensityVec[i] + tempVec[i]) / 2.0;
		}
		tempVec.clear();

		//formant2
		tempVec = interpolation(standFormant2Vec, s_v1);
		//combine comp + temp
		for (int i = 0; i < s_v1; i++) {
			standFormant2Vec[i] = (compFormant2Vec[i] + tempVec[i]) / 2.0;
		}
		tempVec.clear();

		//formant3
		tempVec = interpolation(standFormant3Vec, s_v1);
		//combine comp + temp
		for (int i = 0; i < s_v1; i++) {
			standFormant3Vec[i] = (compFormant3Vec[i] + tempVec[i]) / 2.0;
		}
		tempVec.clear();
	}

	//file write to outfilename, pitch
	outfile_p << "time" << "	" << "pitch" << endl;
	int vecSize = standPitchVec.size();
	for (int i = 0; i < vecSize; i++)
	{
		outfile_p << 0.01 * i << "	" << standPitchVec[i] << endl;
	}

	//file write to outfilename, formant
	outfile_f << "time" << "	" << "f2" << "	" << "f3" << endl;
	for (int i = 0; i < vecSize; i++)
	{
		outfile_f << 0.01 * i << "	" << standFormant2Vec[i] << "	" << standFormant3Vec[i] << endl;
	}

	//file write to outfilename, intensity
	outfile_i << "time" << "	" << "intensity" << endl;
	for (int i = 0; i < vecSize; i++)
	{
		outfile_i << 0.01 * i << "	" << standIntensityVec[i] << endl;
	}

	//file descriptor close
	outfile_p.close();
	outfile_f.close();
	outfile_i.close();
}
