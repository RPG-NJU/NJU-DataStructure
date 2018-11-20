/*
题目描述：
假设初始时1，2，3，……，n，n个元素是n个不同的类，现在执行一些合并操作，Union(i, j)表示将i和j所在的类合并，同时有一些查询操作，Check(i, j)表示查询当前i和j是否是同一类。设计算法实现这个过程。 


输入：
第一行为两个整数，n和k，n表示初始类的个数，编号为1到n，k表示操作的个数。 1<=n<=10000，1<=k<=50000。 
接下来k行，每行开头一个字符串，”Union”表示合并操作，”Check”表示查询操作，后面是两个整数，表示要合并或查询的两个元素。 


输出：
对于每一个查询操作Check(i, j)，若i和j是同一类，输出True，否则输出False，每个查询结果一行。 


样例输入：
5 5
Check 1 2
Union 1 2
Check 1 2
Union 2 3
Check 1 3

样例输出：
False
True
True
*/

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
