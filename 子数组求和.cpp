/*
题目描述：
给定一个元素为正整数的数组A，B表示A的相邻元素组成的子数组，求所有子数组B对应的最小值的和。 
注意时间复杂度。 

输入：
输入有两行： 
第一行为数组A的长度len，0<=len<=10000。 
第二行是len个整数表示数组A，所有数字为小于1000的正整数。 

输出：
输出所有子数组中最小值的和，因为和可能很大，结果对10^9-7取模。

样例输入：
4
3 1 2 4

样例输出：
17

提示：
上述样例中，A数组为[3,1,2,4]，其子数组有[3],[1],[2],[4],[3,1][1,2][2,4],[3,1,2],[1,2,4],[3,1,2,4]，它们的最小值分别为3，1，2，4，1，1，2，1，1，1，加起来和为17。 


*/


#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <algorithm>


using namespace std;



int Func(vector<int> &input)
{
	int ret(0);
	for (int i(0); i < input.size(); ++i)
	{
		int this_min(input[i]);
		for (int j(i); j < input.size(); ++j)
		{
			this_min = min(this_min, input[j]);
			ret += this_min;
		}
	}
	return ret;
}


int main()
{
	int len(0);
	cin >> len;
	vector<int> input;
	int input_data(0);
	for (int i(0); i < len; ++i)
	{
		cin >> input_data;
		input.push_back(input_data);
	}
	//ÊäÈëÍê³É

	cout << Func(input) << endl;

	return 0;
}
