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
string OneMul(Num *a, int b);
void Add(string &a, string b, int sign);

int main()
{
	char x;
	while (cin >> x)
	{
		Num *a_head = new Num{ FIRST,nullptr,nullptr };
		Num *b_head = new Num{ FIRST,nullptr,nullptr };
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
			Num *p = new Num{ get - '0',a_head,nullptr };
			a_head->next = p;
			a_head = a_head->next;
		}
	} while ((get = getchar()) != '\n');
	while ((get = getchar()) != '\n')
	{
		if (get >= '0' && get <= '9')
		{
			Num *p = new Num{ get - '0',b_head,nullptr };
			b_head->next = p;
			b_head = b_head->next;
		}
	}
	return;
}

void Print(Num *head)
{
	for (; head->next != nullptr; head = head->next);//向后寻找
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
	string answer = OneMul(a, b->num);//第一个乘法不需要考虑进位
	b = b->next;
	int sign = 1;
	for (; b != nullptr; ++sign)
	{
		string mid = OneMul(a, b->num);
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
	Num *head = new Num{ FIRST,nullptr,nullptr };
	Num *point = head;
	for (int i = 0; i < answer.size(); ++i)
	{
		Num *p = new Num{ answer[i],point,nullptr };
		point->next = p;
		point = point->next;
	}
	return head;
}

string OneMul(Num *a, int b)
{
	int carry(0);//进位的标志
	string ret;
	for (; a != nullptr; a = a->next)
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

void Add(string &a, string b, int sign)
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