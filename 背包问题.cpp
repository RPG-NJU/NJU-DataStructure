/*
题目描述：
设有一个背包可以放入的重量为S，现有n件物品，重量分别为w[1],w[2],...,w[n]。问能否从这n件物品中选择若干件放入背包中，使得放入的重量之和正好为S。如果存在一种符合上述要求的选择，则称此背包问题有解；否则此背包问题无解。请用递归的方法设计求解此背包问题的算法，输出解的个数（无解输出0）。 

输入：
输入有两行，第一行为两个整数S，n。
第二行有n个整数，表示n件物品的重量。 

输出：
输出解的个数，无解输出0。

样例输入：
4 5
1 1 3 5 2

7 3
5 4 6

样例输出：
3

0

*/
#include <iostream>
#include <algorithm>
using namespace std;
int InPack(int w[], int n, int s, int &num)//最后一个是背包目前为止的大小
{
	if (s == 0)//此时已经装满，刚刚好
		return 1;//此时是分配成功的
	else if (s < 0 || (s > 0 && n <= 0))//此时可能是背包溢出或者，已经没有了物品
		return 0;
	else if (InPack(w, n - 1, s - w[n - 1], num) == 1)
		++num;
	return InPack(w, n - 1, s, num);
}
int main()
{
	int n(0), s(0);
	while (cin >> s >> n)
	{
		int num(0);
		int *weight = new int[n];//动态创建
		for (int i = 0; i < n; ++i)
			cin >> weight[i];
		sort(weight, weight + n);
		InPack(weight, n, s, num);
		cout << num << endl;
	}
	return 0;
}
