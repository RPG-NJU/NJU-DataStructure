/*
题目描述：
给定两个链表，分别表示两个非负十进制整数。每个整数在链表中按反序存储，例如2018在链表中为8->1->0->2。链表每一个节点包含一个数字（0-9）。计算这两个数字的乘积，按照逆序存储在链表中，并输出正序结果。

输入：
输入有若干行，每两行为一组，分别表示两个链表。

输出：
输出每组两个链表的乘积，每个乘积占一行。

样例输入：
0 2 1
4 3 2
7 3 2 5 2 3 8 5
5 7 5 7 4 7 7 6
3 7 7 0 9 8 2 6 8 9 1 9 2 2 2 4
8 8 4 8 6 9 5 1 7 5 7 8 4 3 9 8

样例输出：
28080
3951393368050275
37731264133423744587449053961224
*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

#define FIRST 10000

struct Num
{
	int num;
	Num *before;
	Num *next;
};

void Build(Num *a_head, Num *b_head, char get);
void Print(Num *head);
void Print(vector<int> x);//也是逆序的
Num* Mul(Num *a, Num *b);
vector<int> OneMul(Num *a, int b);
void Add(vector<int> &a, vector<int> b, int sign);

int main()
{
	char x;
	while (cin>>x)
	{
		Num *a_head = new Num{ FIRST,NULL,NULL };
		Num *b_head = new Num{ FIRST,NULL,NULL };
		//Num *head = new Num{FIRST,NULL,NULL};
		Build(a_head, b_head, x);
		//Print(a_head); Print(b_head);//已经验证了输入的正确性
		//下面就需要进行乘法的计算
		Num *answer = Mul(a_head->next, b_head->next);
		Print(answer);
	}
	return 0;
}

void Build(Num *a_head, Num *b_head, char get)
{
	//char get('\0');
	do
	{
		if (get >= '0' && get <= '9')
		{
			Num *p = new Num{ get - '0',a_head,NULL };
			a_head->next = p;
			a_head = a_head->next;
		}
	} while ((get = getchar()) != '\n');
	while ((get = getchar()) != '\n')
	{
		if (get >= '0' && get <= '9')
		{
			Num *p = new Num{ get - '0',b_head,NULL };
			b_head->next = p;
			b_head = b_head->next;
		}
	}
	return;
}

void Print(Num *head)
{
	for (; head->next != NULL; head = head->next);//向后寻找
	for (; head->num != FIRST; head = head->before)
	{
		cout << head->num;
	}
	cout << endl;
	return;
}

Num* Mul(Num *a, Num *b)
{
	//如果将中间的步骤全部简化为，vector的相关会不会更加简便？
	vector<int> answer = OneMul(a, b->num);//第一个乘法不需要考虑进位
	b = b->next;
	int sign = 1;
	for (; b != NULL; ++sign)
	{
		vector<int> mid = OneMul(a, b->num);
		Add(answer, mid, sign);
		b = b->next;
	}
	//Print(answer);
	for (int i = answer.size() - 1; i > 0; --i)
	{
		if (answer[i] == 0)
			answer.pop_back();
		else
			break;
	}
	Num *head = new Num{ FIRST,NULL,NULL };
	Num *point = head;
	for (int i = 0; i < answer.size(); ++i)
	{
		Num *p = new Num{ answer[i],point,NULL };
		point->next = p;
		point = point->next;
	}
	return head;
}

vector<int> OneMul(Num *a, int b)
{
	int carry(0);//进位的标志
	vector<int> ret;
	for (; a != NULL; a = a->next)
	{
		//应该是一直乘到最高位
		ret.push_back(a->num * b + carry);//乘出的数据压入
		if (ret[ret.size() - 1] >= 10)//此时该位已经溢出
		{
			carry = ret[ret.size() - 1] / 10;
			ret[ret.size() - 1] %= 10;
		}
		else
			carry = 0;
	}
	if (carry != 0)
		ret.push_back(carry);
	return ret;
}

void Add(vector<int> &a, vector<int> b, int sign)
{
	int carry(0);
	for (int i = 0; i < b.size(); ++i)
	{
		if (i + sign >= a.size())
			a.push_back(0);//这时候被加数不够长，进行零扩展
		a[i + sign] += b[i] + carry;
		if (a[i + sign] >= 10)
		{
			carry = a[i + sign] / 10;//这是进位
			a[i + sign] %= 10;
		}
		else
			carry = 0;
	}
	if (carry != 0)
		a.push_back(carry);//如果第一位其实超限了的话，进行补充扩展
	return;
}

void Print(vector<int> x)
{
	for (int i = x.size() - 1; i >= 0; --i)
	{
		cout << x[i];
	}
	cout << endl;
	return;
}
