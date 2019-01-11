#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::endl;

bool Judge(int *data, int len);


int main()
{
	int n(0);
	cin >> n;
	int* input = new int[n];
	for (int i(0); i < n; ++i)
		cin >> input[i];
	//input already
	if (Judge(input, n))
		cout << "true" << endl;
	else
		cout << "false" << endl;
	return 0;
}

bool Judge(int* data, int len)
{
	if (len <= 0)
		return true;//It must be right
	int left_head, root;
	root = data[len - 1];//find the root data

	for (left_head = 0; left_head < len - 1; ++left_head)
	{
		if (data[left_head] > root)
			break;
	}

	for (int all_left = left_head; all_left < len - 1; ++all_left)
	{
		if (data[all_left] < root)
			return false;
	}

	return Judge(data, left_head) && Judge(data + left_head, len - left_head - 1);//还需要减去头结点
}
