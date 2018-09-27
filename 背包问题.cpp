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