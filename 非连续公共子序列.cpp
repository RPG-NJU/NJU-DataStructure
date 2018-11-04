/*
题目描述：
在两个非空字符串（字符串长度不超过100）中找到一个最长的非连续公共子序列。 
例如：str1 = "abcdefgh"， str2 = "ghabdh"， 它们的最长非连续公共子序列即为"abdh"，长度为4。 
注意时间复杂度。 

输入：
输入两行，分别为两个非空字符串。

输出：
输出一个整数，表示最长公共子序列的长度。

样例输入：
abcdefgh
ghabdh

样例输出：
4
*/

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


	//输入数据完成

	cout << Func(inputa, inputb) << endl;


	return 0;
}

