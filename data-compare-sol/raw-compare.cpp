#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

int main()
{
	//file open
	ifstream mfile("song-m-pitch.txt");
	ifstream ffile("song-f-pitch.txt");

	//pitch vector
	vector<float> malePitch;
	vector<float> femalePitch;

	/*extract male pitch*/
	//start point check
	bool start = false;
	if (mfile.is_open()) {
		while (!mfile.eof()) {
			//file read
			string time, point;
			mfile >> time >> point;

			//set 0 - --undefined-- F0_Hz
			if (!point.compare("--undefined--") || !point.compare("F0_Hz"))
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
				malePitch.push_back(atof(point.c_str()));
			}
		}

		//remove --undefined-- in the back
		int i = malePitch.size();
		while (1) {
			if (malePitch.back() == 0)
			{
				malePitch.pop_back();
			}
			else
			{
				break;
			}
		}

		//      for(int i=0; i<malePitch.size(); i++){
		//         cout << malePitch[i] <<endl;
		//      }
	}

	/*extract male pitch*/
	//start point check
	start = false;
	if (ffile.is_open()) {
		while (!ffile.eof()) {
			//file read
			string time, point;
			ffile >> time >> point;

			//set 0 - --undefined-- F0_Hz
			if (!point.compare("--undefined--") || !point.compare("F0_Hz"))
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
				femalePitch.push_back(atof(point.c_str()));
			}
		}

		//remove --undefined-- in the back
		int i = femalePitch.size();
		while (1) {
			if (femalePitch.back() == 0)
			{
				femalePitch.pop_back();
			}
			else
			{
				break;
			}
		}

		//      for(int i=0; i<malePitch.size(); i++){
		//         cout << malePitch[i] <<endl;
		//      }
	}

	/*compare two voice*/
	//exist both data - compare
	int mSound = 0, fSound = 0;
	vector<bool> correct;
	int corretCnt = 0;
	int min = 0;
	if (femalePitch.size() > malePitch.size())
	{
		min = malePitch.size();
	}
	else
	{
		min = femalePitch.size();
	}

	while (min>0) {
		while (femalePitch[fSound] != 0 && malePitch[mSound] != 0) {
			//male-10 < female < male+10 ? check similar.
			if (malePitch[mSound] - 10 < femalePitch[fSound] && femalePitch[fSound] < malePitch[mSound] + 10) {
				correct.push_back(true);
				corretCnt++;
			}
			else {
				correct.push_back(false);
			}
			fSound++; mSound++;
		}
		min--;
	}

	mfile.close();
	ffile.close();
	return 0;
}