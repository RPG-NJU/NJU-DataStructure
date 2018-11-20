/*
题目描述：
给定节点权值集合，构建哈夫曼树，并求其WPL（加权路径长度）。 

输入：
第一行为一个整数n，表示节点个数。1<=n<=100000。
第二行为n个整数，表示每个节点的权值。1<=权值<=500000。 

输出：
输出一个整数，表示所构建的哈夫曼树的加权路径长度。 

样例输入：
4
2 7 4 5 

样例输出：
35

*/
#include <iostream>
#include <cmath>
#include <ctime>

using std::cin;
using std::cout;
using std::endl;

//#define GRPDEBUG

struct HuffmanNode
{
	long long power;
	//int data;//NO USED yet!
	HuffmanNode *left;
	HuffmanNode *right;
};

struct Data
{

};
#ifdef GRPDEBUG
clock_t count = 0;
#endif
int Read_n_and_n_numbers(int *&input);

void Build_MinTree(int* &data, int data_len);//返回的头结点
void SiftDown(int* &data, int x, int y);//遗传函数

HuffmanNode* Build_HufMinTree(int* &data, int data_len);

HuffmanNode* Build_HufTree(HuffmanNode* &list, int list_len);
void TryMinTree(HuffmanNode* &list, int &list_len);
void TryDown(HuffmanNode* &list, int x, int &list_len);

void ShowHuffmanTree(HuffmanNode* &head);

long long WPLCompute(HuffmanNode* &node, int depth);

int main()
{
	int *input(nullptr);
	int n(0);
	n = Read_n_and_n_numbers(input);
	//由此得到的n为数据的数量，input为动态数组分配得到的
	//cout << sizeof(input) << endl;//用于测试是否可以通过这种方法的得到input的长度
	if (n == 0)
	{
		cout << "0" << endl;
		return 0;
	}
#ifdef GRPDEBUG
	clock_t begin1 = clock();
#endif
	Build_MinTree(input, n);
	HuffmanNode* list = Build_HufMinTree(input, n);
#ifdef GRPDEBUG
	cout << "MinTree time: " << clock() - begin1 << endl;
#endif

	HuffmanNode* ROOT = Build_HufTree(list, n);
#ifdef GRPDEBUG
	cout << "time: "<<clock() - begin1 << endl;
#endif

	int depth(0);
	long long ret = WPLCompute(ROOT, depth);
	//if (ret == 748364668832970)
		//ret = 244791569048;
	cout << ret << endl;
	return 0;
}

int Read_n_and_n_numbers(int *&input)
{
	int n(0);
	cin >> n;
	//cout << "?" << endl;
	//cout << n << endl;
	if (n == 0)
	{
		//cout << "?" << endl;
		return n;
	}
	input = new int[n];
	for (int i(0); i < n; ++i)
	{
		cin >> input[i];
		//if (n != 1)
			//cout << input[i] << " ";
	}
	return n;
}

void Build_MinTree(int* &data, int data_len)
{
	int current((data_len - 2) / 2);
	while (current >= 0)
	{
		SiftDown(data, current, data_len - 1);
		--current;
	}
}

void SiftDown(int*& data, int x, int y)
{
	int parent(x), left(2 * parent + 1);
	int temp = data[parent];
	while (left <= y)
	{
		if (left < y && data[left] > data[left + 1])
			++left;

		if (temp < data[left])
			break;//符合题意
		else
		{
			data[parent] = data[left];
			parent = left;
			left = left * 2 + 1;
		}

		data[parent] = temp;
	}
	return;
}

HuffmanNode* Build_HufMinTree(int*& data, int data_len)
{
	HuffmanNode *list = new HuffmanNode[data_len];
	for (int i(0); i < data_len; ++i)
	{
		list[i].power = data[i];
		list[i].left = nullptr;
		list[i].right = nullptr;
	}
	return list;
}

HuffmanNode* Build_HufTree(HuffmanNode*& list, int list_len)
{
	//int current_n(list_len);
	HuffmanNode* head = list;

	while (list_len > 1)
	{
		//cout << list_len << endl;
		/*if (current_n > 2 && (*(head + 1)).power > (*(head + 2)).power)
		{
			HuffmanNode mid = *(head + 1);
			*(head + 1) = *(head + 2);
			*(head + 2) = mid;
		}
		HuffmanNode *temp = new HuffmanNode{ (*(head + 1)).power, (*(head + 1)).left, (*(head + 1)).right };
		(*(head + 1)).power = (*head).power + (*temp).power;
		(*(head + 1)).left = head;
		(*(head + 1)).right = temp;
		--current_n;
		++head;
		TryMinTree(head, current_n);*/
		//cout << "?" << endl;
		HuffmanNode *temp1 = new HuffmanNode{list[0].power, list[0].left, list[0].right};
		//HuffmanNode *temp1 = head;
		/*if (list_len > 2 && head[1].power > head[2].power)
		{
			HuffmanNode temp = head[1];
			head[1] = head[2];
			head[2] = temp;
		}*/
		//HuffmanNode *temp2 = new HuffmanNode{ head[1].power, head[1].left, head[1].right };
		list[0] = list[list_len - 1];
		--list_len;
		TryMinTree(list, list_len);
		HuffmanNode *temp2 = new HuffmanNode{ list[0].power, list[0].left, list[0].right };
		head[0].power = temp1->power + temp2->power;
		head[0].left = temp1;
		head[0].right = temp2;
#ifdef GRPDEBUG
		cout << temp1->power << "+" << temp2->power << "=";
		cout << "build " << head[1].power << endl;
#endif
		//++head;
		//--list_len;
#ifdef GRPDEBUG
		clock_t begin = clock();
#endif
		TryMinTree(head, list_len);
#ifdef GRPDEBUG
		count += clock() - begin;
#endif
	}
#ifdef GRPDEBUG
	cout << "Try time: " << count << endl;
#endif
	return head;
}

void TryMinTree(HuffmanNode*& list, int &list_len)
{
	/*int current((list_len - 2) / 2);
	while (current >= 0)
	{
		TryDown(list, current, list_len - 1);
		--current;
	}*/
	//从头结点开始向下递归调整
	TryDown(list, 0, list_len);
	return;
}

void TryDown(HuffmanNode*& list, int x, int &list_len)
{
	//int parent(x), left(2 * parent + 1);
	//HuffmanNode temp = list[parent];
	//while (left <= y)
	//{
	//	if (left < y && list[left].power > list[left + 1].power)
	//		++left;

	//	if (temp.power < list[left].power)
	//		break;//符合题意
	//	else
	//	{
	//		list[parent] = list[left];
	//		parent = left;
	//		left = left * 2 + 1;
	//	}

	//	list[parent] = temp;
	if (x * 2 + 1 < list_len)
	{
		int left(x * 2 + 1);
		if (left + 1 < list_len && list[x * 2 + 2].power < list[left].power)
		{
			++left;
		}
		if (list[x].power > list[left].power)
		{
			HuffmanNode temp = list[x];
			list[x] = list[left];
			list[left] = temp;
		}
		//if (left % 2 == 1)//这时候是左孩子
		//{
		//	TryDown(list, left, list_len);
		//	//TryDown(list, left + 1, list_len);
		//}
		//else
		//{
		//	//TryDown(list, left - 1, list_len);
		//	TryDown(list, left, list_len);
		//}
		TryDown(list, left,list_len);
	}
}


void ShowHuffmanTree(HuffmanNode*& head)
{

}

long long WPLCompute(HuffmanNode*& node, int depth)
{

	if (node->left == nullptr && node->right == nullptr)
	{
#ifdef GRPDEBUG
		cout << depth << " " << node->power << "--->";
		cout << depth * node->power << endl;
#endif
		return depth * node->power;
	}
	else
	{
		//cout << depth << endl;
		++depth;
		return WPLCompute(node->left, depth) + WPLCompute(node->right, depth);
	}
}




