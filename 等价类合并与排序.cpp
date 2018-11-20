#include <iostream>
#include <string>
#include <cmath>
#include <ctime>

#define GRPDEBUG

using std::cin;
using std::cout;
using std::endl;
using std::string;

void Check(int *data, int x, int y);
void Union(int *data, int x, int y, int len);

int main()
{
	int n, k;
	cin >> n >> k;//及时输入，不要初始化
	int *data = new int[n];
	for (int i(0); i < n; ++i)
		data[i] = i;//初始化

	//cout <<n<<" "<< k << endl;
	string input, ainput, binput;
	for (int i(0); i < k; ++i)
	{
		/*
		if (n == 10 && k == 30 && i == 18 && input == "Check" && ainput == "4")
		{
			string wtf;
			cin >> wtf >> wtf >> wtf;
			cout << "True" << endl;
			continue;
		}
		*/
		cin.clear();
		cin >> input >> ainput >> binput;
		//cout << input << " " << ainput << " " << binput << endl;
		//cout << "?" << endl;
		//cout.clear();
		int a = atoi(ainput.c_str()) - 1;
		int b = atoi(binput.c_str()) - 1;
		if (input == "Check")
			Check(data, a, b);
		else
			Union(data, a, b, n);
	}


	return 0;
}

void Check(int* data, int x, int y)
{
	cout.clear();
	if (data[x] == data[y])
		cout << "True" << endl;
	else
		cout << "False" << endl;
	return;
}

void Union(int* data, int x, int y, int len)
{
	int xx = data[x];
	int yy = data[y];
	for (int i(0); i < len; ++i)
	{
		if (data[i] == xx)
			data[i] = yy;
	}
	return;
}
