/*
题目描述：
P85，2.12设有两个整数型类型的顺序表A（有m个元素）和B（有n个元素），其元素均以从小到大的升序排列。试将这两个顺序表合并成一个顺序表C，要求C的元素也以从小到大的升序排列。（请尽量简化算法的复杂度）

输入：
输入多组数据，每组格式如下 
m n 
A 
B 
其中m，n分别表示顺序表A和B的元素个数，A、B为顺序表元素 

输出：
顺序表C的从小到大的输出。（请注意输出，行末无空格）

样例输入：
3 5
3 7 11
2 8 9 12 16
4 2
1 4 6 7
4 9

样例输出：
2 3 7 8 9 11 12 16
1 4 4 6 7 9
*/

#include <iostream>
#include <string>

using namespace std;

int main()
{
	string a, b, c;
	int a_len(0), b_len(0);
	while (cin >> a_len)
	{
		cin >> b_len;
		//cout << a_len << "&" << b_len << endl;
		int input(0);//×÷ÎªÊäÈëµ¥Ôª
		for (int i = 0; i < a_len; ++i)
		{
			cin >> input;
			a.push_back(input);
		}
		for (int i = 0; i < b_len; ++i)
		{
			cin >> input;
			b.push_back(input);
		}
		if (a.size() == 0 || b.size() == 0)
		{
			if (a.size() == 0)
				c = b;
			else
				c = a;
		}
		else
		{
			for (int i = 0, j = 0; i < a.size() || j < b.size();)
			{
				int push(0);
				if (j >= b.size())
				{
					push = a[i];
					++i;
				}
				else if (i >= a.size())
				{
					push = b[j];
					++j;
				}
				else if (a[i] < b[j])
				{
					push = a[i];
					++i;
				}
				else
				{
					push = b[j];
					++j;
				}
				c.push_back(push);
			}
		}
		if (c.size() == 0)
			cout << endl;
		else
		{
			for (int i = 0; i < c.size() - 1; ++i)
			{
				cout << (int)c[i] << " ";
			}
			cout << (int)c[c.size() - 1] << endl;
		}
		c.clear();
		a.clear();
		b.clear();
	}
	return 0;
}
