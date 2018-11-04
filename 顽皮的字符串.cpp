/*
题目描述：
26个英文字母可以组成任意一个字符串，但是由于这些字母日久生情，在字母表中两个紧挨着的字母互有好感(比如ab，ed，yx , gh等)，在字符串中挨在一起会一起跑开（从字符串中消失），跑开之后空位由后面的字母补上。我们的问题是，输入一个长度为n（n<10^5）的字符串，问最后剩下的字符串是什么。

输入：
输入是由a-z构成的一行字符串，我们保证输入的都是小写字母。

输出：
输出是最后剩下的字符串，如果最后所有的字母都跑开了输出sad。

样例输入：
abgcdhfzya

adebc

cabeddbaec

eabdcfgd

ecddfcehdgfgbhaceeeg

样例输出：
fa

c

ec

sad

fcehdgbhaceeeg

*/



#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

struct Node
{
	char data;
	Node *next;
};

Node* Create(string input)
{
	Node* HEAD = new Node{'\0', nullptr};
	Node* p = HEAD;
	for (auto x : input)
	{
		p->next = new Node{ x, nullptr };
		p = p->next;
	}
	return HEAD;
}

bool FindAndKill(Node *p)
{
	Node *x, *y, *z;
	x = p;
	if (x == nullptr)
		return false;
	else
		y = x->next;
	if (y == nullptr)
		return false;
	else
		z = y->next;
	while (y!=nullptr && z!=nullptr)
	{
		if (abs(y->data - z->data) == 1)//´ËÊ±ÊÇÇéÂÂ
		{
			x->next = z->next;
			delete y;
			delete z;
			return true;
		}
		x = y;
		y = z;
		z = z->next;
	}
	return false;
}

int main()
{
	string input;
	cin >> input;

	
	Node *HEAD = Create(input);


	for (; FindAndKill(HEAD););

	if (HEAD->next == nullptr)
		cout << "sad";

	for (HEAD = HEAD->next; HEAD != nullptr; HEAD = HEAD->next)
		cout << HEAD->data;

	
	cout << endl;



	return 0;
}
