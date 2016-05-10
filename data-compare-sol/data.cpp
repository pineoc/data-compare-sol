#include "data.h"

Data::Data()
{

}

Data::Data(vector<double> pitchV, vector<double> f2V, vector<double> f3V, vector<double> intV)
{
	//set initial datas
	setPitchVec(pitchV);
	setFormant2Vec(f2V);
	setFormant3Vec(f3V);
	setIntVec(intV);
}

Data::~Data()
{

}

void Data::setDataLength(int len)
{
	dataLength = len;
}

int Data::getDataLength()
{
	return dataLength;
}

void Data::setPitchVec(vector<double> v)
{
	//copy to pitchVec
	pitchVec.insert(pitchVec.begin(), v.begin(), v.end());
}

vector<double> Data::getPitchVec()
{
	return pitchVec;
}

void Data::setFormant2Vec(vector<double> v)
{
	//copy to formant2Vec
	formant2Vec.insert(formant2Vec.begin(), v.begin(), v.end());
}

vector<double> Data::getFormant2Vec()
{
	return formant2Vec;
}

void Data::setFormant3Vec(vector<double> v)
{
	//copy to formant3Vec
	formant3Vec.insert(formant3Vec.begin(), v.begin(), v.end());
}

vector<double> Data::getFormant3Vec()
{
	return formant3Vec;
}

void Data::setIntVec(vector<double> v)
{
	//copy to intensityVec
	intensityVec.insert(intensityVec.begin(), v.begin(), v.end());
}

vector<double> Data::getIntVec()
{
	return intensityVec;
}
