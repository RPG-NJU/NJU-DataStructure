#include <iostream>

using namespace std;

void C(int n, int k, int output[], int length)
{
	int i(0);
	if (length == k)//此时已经是长度达到要求的情况了
	{
		for (i = 0; i < k; ++i)
		{
			cout << output[i] << " ";
		}
		cout << endl;
		return;//这一次的输出已经结束了
	}
	else
	{
		//这个时候是没有输出而做运算的时候
		//此时一定要从输出语句的最后一个元素的下一个位置开始，并且循环的次数，且末尾一定要留出足够的元素进行分配。
		for (i = (length > 0 ? output[length - 1] + 1 : length + 1); i < n + length - k + 2; ++i)
		{
			output[length] = i;
			C(n, k, output, length + 1);
		}
	}
}

int main()
{
	int n, k;
	cin >> n >> k;
	int *output = new int[k];//选取这么多的元素进行输出
	C(n, k, output, 0);
	return 0;
}