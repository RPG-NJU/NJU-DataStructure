/*
题目描述：
小张同学来到南大一年多，对南大各个建筑的位置已经了如指掌。现在他想知道，从他所在的位置去指定教室的最短路径有多长。设计算法帮助小张解决这个问题，要求使用队列。 


输入：
第一行为两个整数n和m，表示学校地图的长和宽。 
接下来n行，每行有m个字符，’o’表示可以到达的地方，’x’表示不能到达的地方，’z’表示小张所处位置，’d’表示小张要去的教室。 各字符之间有空格。 


输出：
一个整数，表示小张去指定教室的最短路径长度。如果没有路径可以到达则输出-1。 


样例输入：
5 5
o o o o o
o o o o o
o o x d o
o o z x o
o o o o o

4 6
x x x x o o
x o x x o x
d o o x z x
o x o o x x

样例输出：
6

-1
*/



#include <iostream>
#include <algorithm>

using namespace std;

struct FindTheWay
{
	int row;
	int col;
	int distance;
	FindTheWay *next;
};

struct Map
{
	char data;
	bool flag;
};

struct Distance
{
	int sum;
	Distance *next;
};

int FindWay(FindTheWay *FINDHEAD, Distance *DISHEAD, Map **map, int n, int m);
bool Empty(FindTheWay *HEAD);

int main()
{
	int n(0), m(0);
	cin >> n >> m;
	Map **map = new Map*[n];
	for (int i(0); i < n; ++i)
		map[i] = new Map[m];
	for (int i(0); i < n; ++i)
	{
		for (int j(0); j < m; ++j)
		{
			char input;
			cin >> input;
			map[i][j].data = input;
			map[i][j].flag = true;//true代表没有访问
		}
	}
	//输入所有的地图标识
	//如若是栈实现，可以使用深度优先算法，而队列的话，最好的方法是广度优先算法
	//广度优先算法，类似于树的向下查找
	FindTheWay *FINDHEAD = new FindTheWay{ -1,-1,-1,nullptr };
	Distance *DISHEAD = new Distance{ -1,nullptr };
	cout << FindWay(FINDHEAD, DISHEAD, map, n, m) << endl;
	return 0;
}

int FindWay(FindTheWay* FINDHEAD, Distance* DISHEAD, Map** map, int n, int m)
{
	FindTheWay *findtail = FINDHEAD;
	Distance *distail = DISHEAD;
	int begin_row(0), begin_col(0);
	int end_row(0), end_col(0);
	for (int i(0); i < n; ++i)
	{
		for (int j(0); j < m; ++j)
		{
			if (map[i][j].data == 'x')
				map[i][j].flag = false;
			else if (map[i][j].data == 'd')
			{
				end_row = i;
				end_col = j;
			}
			else if (map[i][j].data == 'z')
			{
				begin_row = i;
				begin_col = j;
			}
		}
	}

	map[begin_row][begin_col].flag = false;
	FindTheWay *begin = new FindTheWay{ begin_row, begin_col, 0, nullptr };
	FINDHEAD->next = begin;//提供了第一个节点，不便于放在通式里面进行计算
	findtail = begin;
	FINDHEAD = begin;//此时的头和尾都是同一个位置

	while (!Empty(FINDHEAD))
	{
		if (FINDHEAD->col == end_col && FINDHEAD->row == end_row)//此时是到达了终点
		{
			Distance *dis_p = new Distance{ FINDHEAD->distance, nullptr };
			//cout << "dis_p"<<dis_p << endl;
			distail->next = dis_p;
			distail = distail->next;
			FindTheWay *findkill = FINDHEAD;
			FINDHEAD = FINDHEAD->next;
			delete findkill;
		}
		//如果没有到达终点，就应该遍历周围的所有
		else
		{
			map[FINDHEAD->row][FINDHEAD->col].flag = false;//标记这一位已经遍历
			if (FINDHEAD->row - 1 >= 0 && map[FINDHEAD->row - 1][FINDHEAD->col].flag)
			{
				FindTheWay *find_p = new FindTheWay{ FINDHEAD->row - 1, FINDHEAD->col, FINDHEAD->distance + 1,nullptr };
				findtail->next = find_p;
				findtail = findtail->next;
			}
			if (FINDHEAD->row + 1 < n && map[FINDHEAD->row + 1][FINDHEAD->col].flag)
			{
				FindTheWay *find_p = new FindTheWay{ FINDHEAD->row + 1, FINDHEAD->col, FINDHEAD->distance + 1,nullptr };
				findtail->next = find_p;
				findtail = findtail->next;
			}
			if (FINDHEAD->col - 1 >= 0 && map[FINDHEAD->row][FINDHEAD->col - 1].flag)
			{
				FindTheWay *find_p = new FindTheWay{ FINDHEAD->row, FINDHEAD->col - 1, FINDHEAD->distance + 1,nullptr };
				findtail->next = find_p;
				findtail = findtail->next;
			}
			if (FINDHEAD->col + 1 >= 0 && map[FINDHEAD->row][FINDHEAD->col + 1].flag)
			{
				FindTheWay *find_p = new FindTheWay{ FINDHEAD->row, FINDHEAD->col + 1, FINDHEAD->distance + 1,nullptr };
				findtail->next = find_p;
				findtail = findtail->next;
			}
			FindTheWay *findkill = FINDHEAD;
			FINDHEAD = FINDHEAD->next;
			delete findkill;
		}	
	}
	//cout << "?";
	//cout << DISHEAD << endl;
	//cout << p << endl;
	Distance *p = DISHEAD->next;
	
	int mindis = 100000000;
	if (p == nullptr)
		mindis = -1;
	else
	{
		for (;p != nullptr; p = p->next)
		{
			//mindis > p->sum ? mindis = p->sum : mindis = mindis;

			if (mindis > p->sum)
				mindis = p->sum;
		}
	}
	return mindis;
}

bool Empty(FindTheWay* HEAD)
{
	bool flag(false);
	(HEAD == nullptr) ? (flag = true) : (flag = false);
	return flag;
}

