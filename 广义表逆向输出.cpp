/*
题目描述：
已知广义表的字符串表示如下： 
    ((a,(b,c)),(),(d)) 
请根据字符串生成广义表的链表存储表示，并逆向输出广义表的每个元素。如果广义表的元素是原子，直接输出原子的值，原子是一个字符；如果元素是子表，逆向输出子表的每个元素；如果遇到空表则输出特殊符号'@'。 

输入：
输入一行，为广义表的字符串表示。

输出：
输出一行，为逆向的广义表元素，元素之间不需加空格。

样例输入：
((a,(b,c)),(),(d))

样例输出：
d@cba
*/

#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::istream;
using std::ostream;

#define DEFAULTSIZE 5

template <typename T>
class GRPVector
{
protected:
	T *data;
	size_t max_size;
	size_t real_size;
public:
	GRPVector();

	void push_back(T input);
	void pop_back();
	T pop_head();
	size_t size() const;

	T& front();
	T& back();
	T& operator[](int i);
};

template <typename T>
GRPVector<T>::GRPVector() : data(new T[DEFAULTSIZE]), max_size(5), real_size(0) {}


template <typename T>
size_t GRPVector<T>::size() const
{
	return real_size;
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
T GRPVector<T>::pop_head()
{
	T ret = data[0];
	data = &data[1];
	max_size--;
	real_size--;
	return ret;
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
	return (*this)[this->size()];
}


template <typename T>
class GRPGenListItem;//作为返回值类型

template <typename T>
class GRPGenListNode;//作为广义表的节点类型

template <typename T>
class GRPGenList;//作为广义表的主体

template <typename T>
class GRPGenListItem
{
	friend class GRPGenList<T>;
private:
	int type;
	union
	{
		int ref;
		T data;
		GRPGenListNode<T> *link;
	}info;

public:
	GRPGenListItem() : type(0) { info.ref = 0; }
	GRPGenListItem(GRPGenListItem<T> &copy) { type = copy.type; info = copy.info; }
};

template <typename T>
class GRPGenListNode
{
	friend class GRPGenList<T>;
private:
	int type;//取值只可能是0/1/2，决定了当前节点的类型，0为头节点，1位数据，2为指针域
	GRPGenListNode<T> *next_link;//指向同一个层级的下一个节点
	union
	{
		int ref;//如果是头结点，则存储的是引用计数
		T data;//如果是数据
		GRPGenListNode<T> *link;
	}info;

public:
	GRPGenListNode() :type(0), next_link(nullptr) { info.ref = 0; }//作为头结点的时候的建立
	GRPGenListNode(GRPGenListNode<T> &copy) { type = copy.type; next_link = copy.next_link; info = copy.info; }//拷贝赋值
	~GRPGenListNode() {}
};

template <typename T>
class GRPGenList
{
private:
	GRPGenListNode<T> *HEAD;
	GRPGenListNode<T> *copy(GRPGenListNode<T> *x);//复制一个x指示的无共享非递归表
	int length(GRPGenListNode<T> *x);
	int depth(GRPGenListNode<T> *x);

public:
	GRPGenList();
	//~GRPGenList();
	bool head(GRPGenListItem<T> &x);//返回头元素
	bool tail(GRPGenList<T> &it);
	void copy(const GRPGenList<T> &x);//广义表的复制
	GRPGenListNode<T>* first();//返回广义表的第一个元素，如果为空，则返回一个空指针nullptr
	GRPGenListNode<T>* next(GRPGenListNode<T> *x);//返回所给元素的直接后续元素
	int length();
	int depth();
	//另外需要一个建立广义表的算法
	void createlist(GRPVector<T> &input, GRPGenListNode<T> *&x);//这里是仿照书上所做的构建函数，可能会不符合自己的预期
	void Creat(GRPVector<T> &input);
	void remove(GRPGenListNode<T> *it);
	void save_to(GRPVector<T> &output, GRPGenListNode<T> *x);
	void Save(GRPVector<T> &output);
};

template <typename T>
GRPGenList<T>::GRPGenList()
{
	HEAD = new GRPGenListNode<T>;
	if (HEAD == nullptr)
	{
		cout << "The HEAD is nullptr!" << endl;
		exit(-1);
	}
}

template <typename T>
bool GRPGenList<T>::head(GRPGenListItem<T>& x)
{
	if (HEAD->next_link == nullptr)
		return false;//此时是没有头的
	else
	{
		x.type = HEAD->next_link->type;
		x.info = HEAD->next_link->info;
		return true;//需要返回的通过引用进行返回
	}
}

template <typename T>
bool GRPGenList<T>::tail(GRPGenList<T>& it)
{
	if (HEAD->next_link == nullptr)
		return false;//空表，没有tail可以返回
	else
	{
		it.HEAD->type = 0;//作为一个头结点
		it.HEAD->info.ref = 0;
		it.HEAD->next_link = copy(HEAD->next_link->next_link);//将tail的头放入头结点之后
		return true;
	}
}

template <typename T>
void GRPGenList<T>::copy(const GRPGenList<T> &x)
{
	HEAD = copy(x.HEAD);//调用了私有函数，定义如下
}

template <typename T>
GRPGenListNode<T>* GRPGenList<T>::copy(GRPGenListNode<T>* x)
{
	GRPGenListNode<T> *p = nullptr;
	if (x != nullptr)
	{
		p = new GRPGenListNode<T>;
		p->type = x->type;//将这个节点的类型设置成为拷贝进来的类型
		switch (x->type)
		{
		case 0:p->info.ref = x->info.ref; break;
		case 1:p->info.data = x->info.data; break;
		case 2:p->info.link = x->info.link; break;
		default:cout << x->type << " is not expected as a type!" << endl; exit(-1); break;
		}
		p->next_link = copy(x->next_link);//处理同一层的下一个节点
	}
	return p;
}

template <typename T>
GRPGenListNode<T>* GRPGenList<T>::first()
{
	if (HEAD->next_link == nullptr)
		return nullptr;
	else
		return HEAD->next_link;
}

template <typename T>
GRPGenListNode<T>* GRPGenList<T>::next(GRPGenListNode<T>* x)
{
	if (x->next_link == nullptr)
		return nullptr;
	else
		return x->next_link;
}

template <typename T>
int GRPGenList<T>::length()
{
	return length(HEAD);
}

template <typename T>
int GRPGenList<T>::length(GRPGenListNode<T>* x)
{
	//相当于一个递归调用，不断寻找该链条
	if (x != nullptr)
		return 1 + length(x->next_link);
	else
		return 0;
}

template <typename T>
int GRPGenList<T>::depth()
{
	return depth(HEAD);
}

template <typename T>
int GRPGenList<T>::depth(GRPGenListNode<T>* x)
{
	//一样的是一个递归调用
	/*
	 * depth有三种可能的情形
	 * 如果x为空表：1
	 * 如果x为原子：0
	 * default：1+max{depth} 其中，depth为表中所有对应的子表的深度
	 */
	if (x->next_link == nullptr)
		return 1;
	GRPGenListNode<T> *p = x->next_link;
	int m(0), n(0);//两个临时变量
	while (p != nullptr)//空则不考虑
	{
		if (p->type == 2)//如果是广义表的节点，而非元素（不可能是表头）
		{
			n = depth(p->info.link);//计算以该节点为头的广义表的深度
			if (m < n)//此时m已然不是最大深度
				m = n;
		}
		p = p->next_link;
	}
	return m + 1;//因为还要算上自己的深度
}


template <typename T>
void GRPGenList<T>::createlist(GRPVector<T> &input, GRPGenListNode<T> *&x)
{
	//cout << "!" << endl;
	T input_data;//作为读取出来的数据
	//在这里，希望能够直接达到DSOJ的输入要求，而非书上的
	//DSOJ输入样例：((a,(b,c)),(),(d))
	//如上
	//此时的建立均没有考虑共享表
	//input >> input_data;//读入一个单位的数据
	if (input.size() == 0)
		return;
	else
		input_data = input.pop_head();
	//cout << input_data << endl;
	//cout << input.size() << endl;
	if (input_data == '(')//如果是左括号，则为表
	{
		x = new GRPGenListNode<T>;
		x->type = 2;//建立了一个子表节点

		x->info.link = new GRPGenListNode<T>;//新加节点
		x->info.link->type = 0;//是个表头
		x->info.link->info.ref = 1;//被引用了一次

		//cout << "here" << endl;
		createlist(input, x->info.link->next_link);//递归建立子表，同层向后
		//cout << "here" << endl;
		createlist(input, x);
		//input_data = input.pop_head();
	}

	else if (input_data == ',')
	{
		//此时应该是建立后续节点
		
		createlist(input, x->next_link);
	}

	else if (input_data == '#')
	{
		//此时代表为空表
		//cout << "?" << endl;
		x = nullptr;
		input.pop_head();
		//createlist(input, x);
	}

	else if (input_data == ')')
	{
		//说明该层已经结束了
		//input_data = input.pop_head();
		x->next_link = nullptr;
	}

	else
	{
		//此时是元素的节点
		x = new GRPGenListNode<T>;
		x->type = 1;//data节点
		x->info.data = input_data;
		createlist(input, x);
	}
	return;
}

template <typename T>
void GRPGenList<T>::Creat(GRPVector<T>& input)
{
	createlist(input, HEAD->next_link);
}


template <typename T>
void GRPGenList<T>::remove(GRPGenListNode<T>* it)
{
	--(it->info.ref);//将引用减1，因为只有当引用为0的时候，才可以放心的删除这个头结点
	if (it->info.ref == 0)//此时就可以删除了
	{
		GRPGenListNode<T> *p(nullptr);
		while (it->next_link != nullptr)//当同层的下一个节点存在
		{
			p = it->next_link;
			if (p->type == 2)//如果是link域
			{
				remove(p->info.link);//递归求，向下进行删除
				if (p->info.link->info.ref <= 0)//所指向的头结点的引用已经安全
					delete p->info.link;//所以删除
			}
			it->next_link = p->next_link;
			delete p;
		}
	}
}

template <typename T>
void GRPGenList<T>::save_to(GRPVector<T>& output, GRPGenListNode<T>* x)
{
	if (x == nullptr)
		return;
	else if (x->type == 0)//此时是头结点
	{
		if (x->next_link == nullptr)//此时是空
		{
			output.push_back('@');
			return;
		}
		else
		{
			save_to(output, x->next_link);
		}
	}

	else if (x->type == 1)
	{
		//此时是数据域
		output.push_back(x->info.data);
		save_to(output, x->next_link);
	}

	else
	{
		//此时是link域
		save_to(output, x->info.link);
		save_to(output, x->next_link);
	}
	return;
}

template <typename T>
void GRPGenList<T>::Save(GRPVector<T>& output)
{
	save_to(output, HEAD);
}


int main()
{
	GRPGenList<char> x;
	string input;
	cin >> input;
	GRPVector<char> input_resave;
	for (int i(0); i < input.length(); ++i)
	{
		input_resave.push_back(input[i]);
		if (input[i] == '(' && input[i + 1] == ')')
		{
			//cout << "?" << endl;
			input_resave.push_back('#');
		}
	}
	/*if (input_resave[0] == '(' && input_resave[-1] == ')')
	{
		input_resave.pop_head();
		input_resave.pop_back();
	}*/
	x.Creat(input_resave);
	GRPVector<char> output;
	x.Save(output);
	
	for (int i(1); i <= output.size(); ++i)
		cout << output[-i];

	//cout << x.depth() << endl;
	return 0;
}
