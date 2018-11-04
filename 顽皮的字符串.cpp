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
		if (abs(y->data - z->data) == 1)//此时是情侣
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