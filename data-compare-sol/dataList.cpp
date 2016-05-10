#include "dataList.h"


dataList::dataList(vector<double> pitchV, vector<double> f2V, vector<double> f3V, vector<double> intV)
{
	//make data list of data node
	//using vector stream
	
	for (int i = 0; i < pitchV.size(); i++)
	{
		//data block start
		if (pitchV[i] > 0.0)
		{
			Data d;
			vector<double> pitchBlock;
			vector<double> f2Block;
			vector<double> f3Block;
			vector<double> intBlock;
			while (pitchV[i] > 0)
			{
				pitchBlock.push_back(pitchV[i]);
				f2Block.push_back(f2V[i]);
				f3Block.push_back(f3V[i]);
				intBlock.push_back(intV[i]);
				i++;
				if (pitchV.size() == i)
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
