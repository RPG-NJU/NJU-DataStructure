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
