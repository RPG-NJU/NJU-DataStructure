#include <iostream>
#include <algorithm>

using std::cin;
using std::cout;
using std::endl;
using std::max;
using std::min;

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
	cout << "==========" << endl << "<FRONT>" << endl;
	for (; p != nullptr; p = p->next)
		cout << p->data << endl;
	cout << "<BACK>" << endl << "==========" << endl;
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


struct SearchBinNode
{
	int data;
	SearchBinNode* left;
	SearchBinNode* right;
};

class SearchBinTree
{
private:
	SearchBinNode* parent;
	SearchBinNode* ROOT;
	SearchBinNode*& searchIn(SearchBinNode*& r, const int &x, SearchBinNode*& p);
	void show_midorder(SearchBinNode*& root);
public:
	SearchBinTree() { ROOT = nullptr; parent = nullptr; }
	~SearchBinTree() {}
	SearchBinNode*& search(const int &x) { return searchIn(ROOT, x, parent = nullptr); }
	SearchBinNode*& insert(const int &x);
	void show_midorder() { show_midorder(ROOT); }
	void show_side();
};

int main()
{
	int n;
	cin >> n;
	SearchBinTree tree;
	for (int i(0); i < n; ++i)
	{
		int input;
		cin >> input;
		tree.insert(input);
	}
	tree.show_side();
	cout << endl;
	tree.show_midorder();
	cout << endl;
	return 0;
}

SearchBinNode*& SearchBinTree::searchIn(SearchBinNode*& r, const int& x, SearchBinNode*& p)
{
	if (!r || (x == r->data))
		return r;
	p = r;//±£´æ¸¸½Úµã
	return searchIn(((x < r->data) ? r->left : r->right), x, p);
}

SearchBinNode*& SearchBinTree::insert(const int& x)
{
	SearchBinNode*& find = search(x);
	if (find)
		return find;
	find = new SearchBinNode{ x, nullptr, nullptr };
	if (parent)
	{
		if (parent->data > x)
			parent->left = find;
		else
			parent->right = find;
	}
	return find;
}

void SearchBinTree::show_midorder(SearchBinNode*& root)
{
	if (root == nullptr)
		return;

	show_midorder(root->left);
	cout << root->data << " ";
	show_midorder(root->right);
	return;
}

void SearchBinTree::show_side()
{
	GRPQueue<SearchBinNode*> list;
	if (ROOT == nullptr)
		return;
	SearchBinNode* x = new SearchBinNode{ ROOT->data, ROOT->left, ROOT->right };
	list.push(x);
	while (!list.empty())
	{
		SearchBinNode* get = list.pop();
		if (get->left != nullptr)
		{
			SearchBinNode* i = new SearchBinNode{ get->left->data, get->left->left, get->left->right };
			list.push(i);
		}

		if (get->right != nullptr)
		{
			SearchBinNode* i = new SearchBinNode{ get->right->data, get->right->left, get->right->right };
			list.push(i);
		}

		cout << get->data << " ";
	}
	return;
}
