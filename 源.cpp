#include<stdio.h>  
#include<string.h>  
#include<stdlib.h>  
int n, m;
int map[105][105];
int result[105];
int state[105];
int find(int a)
{
	int i;
	for (i = 0; i < m; i++)
	{
		if (!state[i] && map[a][i])
		{
			state[i] = 1;
			if (result[i] == -1 || find(result[i]))
			{
				result[i] = a;
				return 1;
			}
		}
	}
	return 0;
}
int main()
{
	int i, t, a, b, c, ans;
	while (scanf_s("%d", &n), n)
	{
		scanf_s("%d%d", &m, &t);
		memset(map, 0, sizeof(map));
		memset(result, -1, sizeof(result));
		while (t--)
		{
			scanf_s("%d%d%d", &a, &b, &c);
			if (b != 0 && c != 0)
				map[b][c] = 1;
		}
		ans = 0;
		for (i = 0; i < n; i++)
		{
			memset(state, 0, sizeof(state));
			if (find(i))
				ans++;
		}
		printf("%d\n", ans);
	}
	return 0;
}

/*
 25 25
							      1 2
							      	2 3
							      	3 4
							      	4 5
							      	5 6
							      	6 7
							      	7 8
							      	8 9
							      	9 10
							      	10 11
							      	11 12
							      	12 13
							      	13 14
							      	14 15
							      	15 16
							      	16 17
							      	17 18
							      	18 19
							      	19 20
							      	20 21
							      	21 22
							      	22 23
							      	23 24
							      	24 25
							      	25 1
 */