#pragma once
/*
data list of data class
this class make list of speak data


*/

#include <vector>
#include <string>

#include "data.h"

using namespace std;

class dataList
{
private:
	vector<Data> objDataList;
public:
	dataList(vector<double> pitchV, vector<double> f2V, vector<double> f3V, vector<double> intV);
	~dataList();
	void pushList(Data d);
	vector<Data> getDataList();
};

