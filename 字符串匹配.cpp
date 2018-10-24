/*
题目描述：
给定两个字符串s1,s2，寻找其中一个字符串s1是否包含另一个字符串s2。如果包含，返回包含的起始位置，否则返回-1.(注
意时间复杂度)。注：s1,s2长度满足: 0=<len(s2)<=len(s1)

输入：
输入有三行 
第一行包含两个数字，以空格分隔，表示两个字符串的长度 
第二行为第一个字符串 
第三行为第二个字符串 

输出：
输出有一行，输出包含的起始位置，如果有多处包含，则输出每一个包含的位置，以空格作为分隔；如果不包含则输出-1

样例输入：
37 7
bacbababadadabacambabacaddababacasdsd
ababaca

43 10
ababababcadababababcadababababcadababababca
ababababca

样例输出：
26

0 11 22 33


*/



#include <iostream>
#include <string>
#include <cstring>

//#define DEBUG

using namespace std;

int main()
{
	int input_len(0), substr_len(0);
	string input, substr;

	cin >> input_len >> substr_len;
	//input the int data;
	cin >> input >> substr;
	//input the str and the substr

	int *match = new int[substr_len];
	for (int i(0); i < substr_len; ++i)
		match[i] = 0;

	for (int i(1); i < substr_len; ++i)
	{
		for (int j(1); j <= i; ++j)
		{
			if (strncmp(substr.c_str() + i + 1 - j, substr.c_str() , j) == 0)
				match[i] = j;
			//cout << substr.c_str() + i + 1 - j << endl;
		}
	}
	//finish the match array;

	/*for (int i(substr_len - 1); i > 0; --i)
	{
		match[i] = match[i - 1];
	}
	match[0] = -1;
	*/
#ifdef DEBUG
	for (int i(0); i < substr_len; ++i)
		cout << match[i] << " ";
	cout << endl;
#endif
	bool flag = false;
	for (int i(0), j(0); i + substr_len - 2 - j <= input_len;)
	{
		//cout << i << endl;
		if (j == substr_len)
		{
			j -= j - 1 - match[j - 1];
			cout << i - substr_len<< " ";
			flag = true;
		}
		else if (input[i] == substr[j])
		{
			//cout <<j << endl;
			++j;
			++i;
		}
		else
		{
			if (i + substr_len - 2 - j == input_len)
				break;
			else
			{
				if (j == 0)
				{
					j = 0;
					++i;
				}
				else
				{
					j -= j - match[j - 1];
					//cout << "?";
					//--i;
				}
			}
		}
	}
	if (!flag)
		cout << "-1";
	return 0;
}
