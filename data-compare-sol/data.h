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
	~Data();
};

