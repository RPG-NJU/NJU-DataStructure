//#pragma once
//#pragma once
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