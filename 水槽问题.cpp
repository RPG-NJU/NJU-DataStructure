#include <iostream>
#include <cmath>
#include <algorithm>

using std::cin;
using std::endl;
using std::cout;


int main()
{
	int n(0);
	cin >> n;
	long long *data = new long long[n];
	for (int i(0); i < n; ++i)
		cin >> data[i];
	int left(0), right(n - 1);//作为左右的索引
	long long ret(0);
	while (left < right)
	{
		ret = std::max(ret, std::min(data[left], data[right]) * (right - left));

		if (data[left] < data[right])
			++left;
		else
			--right;
	}

	cout << ret << endl;
	return 0;
}