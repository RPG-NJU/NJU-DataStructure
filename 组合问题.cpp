/*
题目描述：
给定n，输出从1，2，3，... ，n中任取k(0<k<=n)个数的所有组合（数字按从小到大排列）。 

输入：
一行，两个数，n和k。 

输出：
所有k个数字的组合，一行一个，组合内数字按从小到大排列，两个数字之间有一个空格，不同组合按字典序排列。 

样例输入：
3 1

4 2

样例输出：
1
2
3

1 2
1 3
1 4
2 3
2 4
3 4

*/
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
