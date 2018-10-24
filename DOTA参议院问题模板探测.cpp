//#pragma once
/*
题目描述：
在Dota2游戏中，有两个门派：Radiant和Dire。 Dota2参议院由上述两个门派构成。现参议院想通过投票的方式
来选举获胜方来对游戏进行改进。投票机制是循环制。规则如下：
1, 议员均有投票权
2, 议员可以让另一方的一个议员失去本轮和接下来所有几轮的投票权利。
3, 如果该议员发现剩下的具有投票权的人员均来自本方门派，则宣告胜利。
设定字符串string，字符串（仅包含R和D）中的字符‘R’和‘D’分别代表Radiant门派和Dire门派。 循环投票机制按既
定的顺序进行投票，即每轮从第一个参议员开始，最后一个参议员结束。在该过程中，失去投票权利的参议员将被
略过。现在你需要预测两方参议员中哪一方能够最终取得胜利。输出应为Radiant或者Dire。
注：字符串长度len满足：1=<len<=10000

输入：
输入有一行，包含‘R’和‘D’的字符串

输出：
输出有一行，Radiant或者Dire

样例输入：
DDRRD

样例输出：
Dire
*/
#ifndef GRP_QUEUE
#define GRP_QUEUE

#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::istream;
using std::ostream;

template <typename T>
class GRPQueue;

template <typename T>
class GRPSinNode
{
	friend class GRPQueue<T>;
protected:
	T data;
	GRPSinNode *next;
	GRPSinNode() :data(*(new T)), next(nullptr) {}
	GRPSinNode(T data) :data(data), next(nullptr) {}
	~GRPSinNode() {}
};

template <typename T>
class GRPQueue
{
private:
	GRPSinNode<T> *FIRST, *current;
	size_t queue_size;
public:
	GRPQueue();
	~GRPQueue();
	void push(T input);
	T pop();
	T front();
	T back();
	size_t size() const;
	void show() const;
	bool empty() const;
	void clear();
};

template <typename T>
GRPQueue<T>::GRPQueue()
{
	FIRST = current = new GRPSinNode<T>;
	queue_size = 0;
}

template <typename T>
GRPQueue<T>::~GRPQueue()
{
	GRPSinNode<T> *kill(FIRST);
	for (; FIRST != nullptr;)
	{
		kill = FIRST;
		FIRST = FIRST->next;
		delete kill;
	}
}

template <typename T>
void GRPQueue<T>::push(T input)
{
	GRPSinNode<T> *add = new GRPSinNode<T>(input);
	current->next = add;
	current = add;
	++queue_size;
	return;
}

template <typename T>
size_t GRPQueue<T>::size() const
{
	return queue_size;
}

template <typename T>
void GRPQueue<T>::show() const
{
	GRPSinNode<T> *p(FIRST->next);
	for (; p != nullptr; p = p->next)
		cout << p->data << " ";
	cout << endl;
	return;
}

template <typename T>
bool GRPQueue<T>::empty() const
{
	return current == FIRST;
}

template <typename T>
void GRPQueue<T>::clear()
{
	while (!this->empty())
		this->pop();
	queue_size = 0;
	return;
}

template <typename T>
T GRPQueue<T>::pop()
{
	GRPSinNode<T> *ret = FIRST->next;
	if (ret->next == nullptr)
		current = FIRST;
	FIRST->next = ret->next;
	T ret_data(ret->data);
	delete ret;
	return ret_data;
}

template <typename T>
T GRPQueue<T>::front()
{
	return FIRST->next->data;
}

template <typename T>
T GRPQueue<T>::back()
{
	return current->data;
}

#endif





int main()
{
	string input;
	cin >> input;

	GRPQueue<int> Dire, Radiant;

	for (int i = 0; i < input.size(); ++i)
	{
		if (input[i] == 'D')
			Dire.push(i);
		else
			Radiant.push(i);
	}

	while (!Dire.empty() && !Radiant.empty())
	{
		//cout << "ONE TURN" << endl;
		int DireMan = Dire.pop();
		int RadiantMan = Radiant.pop();

		if (DireMan < RadiantMan)
			Dire.push(DireMan + input.size());
		else
			Radiant.push(RadiantMan + input.size());
	}

	if (Dire.empty())
		cout << "Radiant" << endl;
	else
		cout << "Dire" << endl;
	return 0;
}
