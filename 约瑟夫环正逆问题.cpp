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