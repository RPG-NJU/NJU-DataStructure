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