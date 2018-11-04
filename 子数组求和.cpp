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