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
		int input(0);//作为输入单元
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