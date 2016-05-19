#include "dataList.h"


dataList::dataList()
{
}

dataList::dataList(vector<double> pitchV, vector<double> f2V, vector<double> f3V, vector<double> intV)
{
	//make data list of data node
	//using vector stream

	double int_avg = 0.0;
	//get intensity average value
	for (int i = 2; i < intV.size() - 2; i++)
		int_avg += intV[i];
	int_avg = int_avg / (double)(intV.size() - 4);
	
	for (int i = 0; i < intV.size(); i++)
	{
		//data block start
		if (intV[i] > int_avg)
		{
			Data d;
			vector<double> pitchBlock;
			vector<double> f2Block;
			vector<double> f3Block;
			vector<double> intBlock;
			while (intV[i] > int_avg)
			{
				pitchBlock.push_back(pitchV[i]);
				f2Block.push_back(f2V[i]);
				f3Block.push_back(f3V[i]);
				intBlock.push_back(intV[i]);
				i++;
				if (intV.size() == i)
					break;
			}
			d.setPitchVec(pitchBlock);
			d.setFormant2Vec(f2Block);
			d.setFormant3Vec(f3Block);
			d.setIntVec(intBlock);
			d.setDataLength(pitchBlock.size());
			pushList(d);
		}
	}
}


dataList::~dataList()
{
}

void dataList::pushList(Data d)
{
	objDataList.push_back(d);
}

vector<Data> dataList::getDataList()
{
	return objDataList;
}
