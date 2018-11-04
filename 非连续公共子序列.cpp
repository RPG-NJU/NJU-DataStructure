#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <algorithm>



using namespace std;


int Func(const string &inputa, const string &inputb)
{
	int ret(0);
	vector<vector<int> > data;

	for (int i(0); i <= inputa.length(); ++i)
	{
		vector<int> mid;
		for (int j(0); j < inputb.length(); ++j)
		{
			mid.push_back(0);
		}
		mid.push_back(0);
		data.push_back(mid);
		mid.clear();
	}


	for (int i(0); i < inputa.length(); ++i)
	{
		for (int j(0); j < inputb.length(); ++j)
		{
			if (i == 0 || j == 0)
			{
				data[i][j] = 0;
			}
		}
	}

	//cout << "?";

	for (int i(1); i <= inputa.length(); ++i)
	{
		for (int j(1); j <= inputb.length(); ++j)
		{
			if (inputa[i - 1] == inputb[j - 1])
				data[i][j] = data[i - 1][j - 1] + 1;
			else
			{
				data[i][j] = max(data[i][j - 1], data[i - 1][j]);
				ret = max(data[i][j - 1], data[i - 1][j]);
			}


			ret = max(ret, data[i][j]);
		}
	}


	return ret;


}

int main()
{
	string inputa;
	string inputb;

	cin >> inputa >> inputb;


	//输入已经完成

	cout << Func(inputa, inputb) << endl;


	return 0;
}

