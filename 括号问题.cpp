#include <iostream>

using namespace std;


int main()
{
	int n(0);
	while (cin >> n)
	{
		char *input = new char[n + 1];
		cin >> input;
		//int head(0), tail(n - 1);//标记头尾
		//cout << Score(head, tail, input) << endl;
		//如果使用压栈的逆波兰式的思想呢？
		//假设input为一个栈
		char *stack = new char[n + 1];
		char *store = new char[n + 1];
		int point(0);
		int store_i(0);
		for (int i = 0; i < n; ++i)
		{
			if (input[i] == '(' && input[i + 1] == ')')
			{
				++i;
				stack[point] = 1;
				//cout << "?" << stack[point] << "!" << endl;
				++point;
			}
			else//此时不是成对出现的
			{
				stack[point] = input[i];
				++point;
			}
		}
		//for (int i = 0; i < point; ++i)
			//cout << "No." << i << ":" << (int)stack[i] << endl;
		//cout << endl;
		int score(0), mid(0);
		int final_point(0);
		int top(0);
		for (int i = 0; i < point; ++i)
		{
			if (stack[i] == '(')
			{
				store[final_point] = '(';
				++final_point;
			}
			else if (stack[i] == 1)
			{
				store[final_point] = 1;
				++final_point;
			}
			else//此时为括号结尾
			{
				--final_point;
				for (; final_point > 0; --final_point)
				{
					//for (int i = 0; i <= final_point; ++i)
						//cout << (int)store[i] << " ";
					//cout << endl;
					if (store[final_point - 1] != '(')
					{
						store[final_point - 1] += store[final_point];
					}
					else
					{
						store[final_point] *= 2;
						store[final_point - 1] = store[final_point];
						break;
					}
				}
			}
			//cout << store << endl;
		}
		--final_point;
		for (; final_point > 0; --final_point)
		{
			store[final_point - 1] += store[final_point];
		}
		cout << (int)store[0] << endl;
		//cout << (int)store[1] << endl;
	}
	return 0;
}