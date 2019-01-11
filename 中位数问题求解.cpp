#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;


int GetMidNum(int* data, int lenth);


int main()
{
	int n(0);
	cin >> n;//输入每个数组的长度
	//要求的时间复杂度是一个Log函数，Log函数的解法通常可能是一个递归或者拆分的问题
	int *a = new int[n];
	int *b = new int[n];

	int *bsign = b;
	int *asign = a;

	for (int i(0); i < n; i++)
		cin >> a[i];
	for (int i(0); i < n; i++)
		cin >> b[i];
	//END OF INPUT

	while (n > 1)
	{
		int x = GetMidNum(asign, n);
		int y = GetMidNum(bsign, n);
		if (x == y)
		{
			cout << x << endl;
			return 0;
		}
		else if (x > y)
		{
			bsign += n / 2;
			//此时是a的数组中位数大于b，这时候需要将a进行前调
			n = (n + 1) / 2;
		}
		else if (x < y)
		{
			asign += n / 2;
			n = (n + 1) / 2;
		}
	}
	(*asign < *bsign) ? cout << *asign << endl : cout << *bsign << endl;
	//cout << *asign << endl;
	return 0;
}

int GetMidNum(int* data, int lenth)
{
	return data[(lenth - 1) / 2];
}

/*
5
1 324 6365 24314 35515123
12 434 657567 9879807 586473562
434
 */