#pragma once
/*
class for speak data
datas: 
- [vector]pitch array
- [vector]formant 2, 3 array
- [vector]intensity array
- [int] data length
*/

#include <vector>
#include <string>
using namespace std;

class Data
{
private:
	int dataLength;
	vector<double> pitchVec;
	vector<double> formant2Vec;
	vector<double> formant3Vec;
	vector<double> intensityVec;
public:
	Data();
	Data(vector<double> pitchV, vector<double> f2V, vector<double> f3v, vector<double> intV);
	~Data();
	
	void setDataLength(int len);
	int getDataLength();

	void setPitchVec(vector<double> v);
	vector<double> getPitchVec();

	void setFormant2Vec(vector<double> v);
	vector<double> getFormant2Vec();

	void setFormant3Vec(vector<double> v);
	vector<double> getFormant3Vec();

	void setIntVec(vector<double> v);
	vector<double> getIntVec();
};

