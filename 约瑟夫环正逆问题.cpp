/*
题目描述：
约瑟夫环(约瑟夫问题)是一个数学的应用问题：已知n个人(编号1，2，3…n)围坐在一张圆桌周围。从编号为k的人开始报数，数到m的那个人出列;他的下一个人又从1开始报数，数到m的那个人又出列；依此规律重复下去，直到圆桌周围的人全部出列。用双链表实现约瑟夫环问题，并输出顺时针与逆时针结果。

输入：
n m k

输出：
输出有两行，依次是约瑟夫环的顺时针和逆时针输出

样例输入：
5 2 1

10 3 7

样例输出：
2 4 1 5 3
5 3 1 2 4

9 2 5 8 3 7 4 1 6 10
5 2 9 6 1 7 10 3 8 4
*/

#include <iostream>
#include <string>

using namespace std;

struct Person
{
	int num;
	Person *before;
	Person *next;
};

Person* Build(int n);
void Right(Person *head, int m, int k);
void Left(Person *head, int m, int k);

int main()
{
	int n(0), m(0), k(0);
	while(cin>>n)
	{
		cin >> m >> k;//input
		Person *head1 = Build(n);
		Person *head2 = Build(n);
		Right(head1, m, k);
		Left(head2, m, k);
	}
	return 0;
}




Person* Build(int n)
{
	Person *head = new Person{ 1, nullptr, nullptr };
	Person *p = head;
	for (int i = 2; i <= n; ++i)
	{
		Person *add = new Person{ i,p,nullptr };
		p->next = add;
		p = p->next;
	}
	p->next = head;
	head->before = p;
	return head;
}

void Right(Person *head, int m, int k)
{
	for (int i = 1; i < k; ++i)
		head = head->next;
	while (head->next != head)
	{
		//cout << "in" << endl;
		for (int i = 1; i < m; ++i)
		{
			head = head->next;
		}
		//delete
		cout << head->num << " ";
		head->before->next = head->next;
		head->next->before = head -> before;
		Person *kill = head;
		head = head->next;
		delete kill;
	}
	cout << head->num << endl;
	return;
}

void Left(Person *head, int m, int k)
{
	for (int i = 1; i < k; ++i)
		head = head->next;
	while (head->before != head)
	{
		//cout << "in" << endl;
		for (int i = 1; i < m; ++i)
		{
			//cout << "for" << endl;
			//cout << head->before << endl;
			head = head->before;
		}
		//delete
		cout << head->num << " ";
		head->before->next = head->next;
		head->next->before = head->before;
		Person *kill = head;
		head = head->before;
		delete kill;
	}
	cout << head->num << endl;
	return;
}
