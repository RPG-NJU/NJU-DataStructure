//#pragma once
#ifndef GRP_VECTOR
#define GRP_VECTOR

#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;



#define GRP_VECTOR_DEFAULTSIZE 5

template <typename T>
class GRPVector
{
protected:
	T *data;
	size_t max_size;
	size_t real_size;
public:
	GRPVector();
	~GRPVector();

	void push_back(T input);
	void pop_back();
	size_t size() const;
	bool empty() const;
	void clear();

	T& front();
	T& back();
	T& operator[](int i);

	void insert(int i, const T &add);
	void erase(int i);

	int find(T which) const;//寻找某元素，返回它的索引

	GRPVector& operator=(const GRPVector& copy);
};

template <typename T>
GRPVector<T>::GRPVector() : data(new T[GRP_VECTOR_DEFAULTSIZE]), max_size(GRP_VECTOR_DEFAULTSIZE), real_size(0) {}

template <typename T>
GRPVector<T>::~GRPVector()
{
	delete data;//将动态数组归还
}


template <typename T>
size_t GRPVector<T>::size() const
{
	return real_size;
}

template <typename T>
bool GRPVector<T>::empty() const
{
	return real_size == 0;
}

template <typename T>
void GRPVector<T>::clear()
{
	real_size = 0;
	return;
}



template <typename T>
void GRPVector<T>::push_back(T input)
{
	if (real_size == max_size)
	{
		T *old = data;
		data = new T[2 * max_size];//开一个扩容一倍的数组
		for (size_t i(0); i < max_size; ++i)
		{
			data[i] = old[i];
		}
		max_size *= 2;//将扩容反馈
	}
	//无论需不需要扩容，后续的过程是一样的
	data[real_size] = input;
	++real_size;
	return;
}

template <typename T>
void GRPVector<T>::pop_back()
{
	//现如今没有打算完成可以自动减少长度的功能
	--real_size;//直接将最后的标识向前即可，这样子就可以避免访问
	return;
}

template <typename T>
T& GRPVector<T>::operator[](int i)
{
	//cout << -static_cast<int>(real_size) << endl;
	//cout << (i >= -static_cast<int>(real_size)) << endl;
	if ((i < static_cast<int>(real_size)) && (i >= -static_cast<int>(real_size)))
	{
		if (i >= 0)
			return data[i];
		else
			return data[this->size() + i];
	}

	else
	{
		cout << "This GRPVector's size is " << real_size << endl;
		cout << "You should not read the place [" << i << "]" << endl;
		exit(-1);
	}
}

template <typename T>
T& GRPVector<T>::front()
{
	return (*this)[0];
}

template <typename T>
T& GRPVector<T>::back()
{
	return (*this)[this->size() - 1];
}

template <typename T>
void GRPVector<T>::insert(int i, const T& add)
{
	if (i < real_size)
	{
		this->push_back(this->back());//将最后一位的数据在填充一次，供扩展
		for (int j(i); j < real_size - 1; ++j)
		{
			(*this)[j + 1] = (*this)[j];
		}
		(*this)[i] = add;
	}
	else
	{
		cout << "GRPVector的总长度为" << real_size << "，不能在[" << i << "]处插入元素" << endl;
	}
	return;
}

template <typename T>
void GRPVector<T>::erase(int i)
{
	if (i < real_size)
	{
		for (int j(i); j < real_size - 1; ++j)
		{
			(*this)[j] = (*this)[j + 1];
		}
		this->pop_back();
	}
	else
	{
		cout << "GRPVector的总长度为" << real_size << "，不能在删除[" << i << "]元素" << endl;
	}
	return;
}


template <typename T>
int GRPVector<T>::find(T which) const
{
	for (int i(0); i < real_size; ++i)
	{
		if (data[i] == which)
			return i;
	}
	return -1;//作为无此元素的标志
}



template <typename T>
GRPVector<T>& GRPVector<T>::operator=(const GRPVector& copy)
{
	this->clear();
	for (int i(0); i < copy.size(); ++i)
	{
		this->push_back(copy[i]);
	}
	return *this;
}

#endif

void BuildMinHeap(GRPVector<int> &data);

void SiftDown(GRPVector<int> &data, int x, int y);


int main()
{
	int input;
	GRPVector<int> all_data;
	while (cin >> input)
	{
		/*if (input == 0)
			break;*/
		all_data.push_back(input);
		//cout << input << endl;

	}
	//完成了所有的输入


	BuildMinHeap(all_data);
	//cout << "?" << endl;


	for (int i(0); i < all_data.size(); ++i)
		cout << all_data[i] << " ";
	cout << endl;

	return 0;
}


void BuildMinHeap(GRPVector<int> &data)
{
	int currentPos = (data.size() - 2) / 2;
	while (currentPos >= 0)
	{
		SiftDown(data, currentPos, data.size() - 1);
		--currentPos;
		
	}
	return;
}

void SiftDown(GRPVector<int> &data, int x, int y)
{
	int parent(x), left(2 * parent + 1);//left代表了parent的左节点的位置
	int mid = data[parent];
	while (left <= y)
	{
		
		if (left < y && data[left] > data[left + 1])
			left = left + 1;//指向了两个孩子节点中小的那一个

		if (mid < data[left])
			break;//非常的符合题意

		else
		{
			
			data[parent] = data[left];
			parent = left;
			left = left * 2 + 1;//否则长辈节点下滑，针对改变的子树进行进一步操作
		}
		//cout << "what" << endl;
		data[parent] = mid;
	}
	return;
}
