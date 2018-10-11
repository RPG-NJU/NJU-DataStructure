/*
题目描述：
一个具有 n(0<n<100000)个整型数的向量，要求得到该向量的任何连续子向量中的最大和。

输入：
输入分为两行 
第一行为此向量元素的个数n 
第二行为n个向量元素，数字之间以空格分隔开 

输出：
输出连续子向量的最大和是多少 

样例输入：
10
31 -41 59 26 -53 58 97 -93 -23 84

样例输出：
187

提示：
n的取值范围很大，暴力枚举会引起时间超限
*/

#include <iostream>
#include <algorithm>//need the function max(,);

using namespace std;

int SubStr(int *x, int size);

int main()
{
	int n(0);
	cin >> n;
	int *input = new int[n];
	for (int i(0); i < n; ++i)
		cin >> input[i];
	cout << SubStr(input, n) << endl;

	return 0;
}

int SubStr(int* x, int size)
{
	//但是在这个样例中存在负数的最小值影响这一算法的实现
	int max_get(0), real_max(0);

	for (int i(0); i < size; ++i)
	{
		//其实问题的本质在于能不能在后续的正数之中弥补负数的缺憾
		max_get = max(x[i] + max_get, 0);
		real_max = max(max_get, real_max);
	}
	if (real_max == 0)
	{
		real_max = -10000000;
		for (int i(0); i < size; ++i)
			real_max = max(x[i], real_max);
	}
	return real_max;
}
