#pragma once
#include <iostream>
#include <algorithm>

using std::end;
using std::cout;
using std::cin;

#define BinNodePosi(T) BinNode<T>* //返回节点的指针
#define stature(p) ((p) ? (p)->height : -1) //返回节点的高度（约定空节点为-1）
typedef enum { RB_RED, RB_BLACK } RBColor; //节点的颜色，用于红黑树

template <typename T>
struct BinNode
{
	T data;//数值
	BinNodePosi(T) parent;
	BinNodePosi(T) left_child;
	BinNodePosi(T) right_child;
	int height;//高度
	int npl;//Null Path Length（左式堆，也可以直接用height代替）
	RBColor color;//用于红黑树的颜色

	//构造函数
	BinNode() :parent(nullptr), left_child(nullptr), right_child(nullptr), height(0), npl(1), color(RB_RED) {}
	BinNode(T e, BinNodePosi(T) p = nullptr, BinNodePosi(T) lc = nullptr, BinNodePosi(T) rc = nullptr, int h = 0, int l = 1, RBColor c = RB_RED) :
		data(e), parent(p), left_child(lc), right_child(rc), height(h), npl(l), color(c) {}

	//操作接口
	int size(); //统计当前节点后代总数，即以其为根的子树的规模
	BinNodePosi(T) insertAsLc(T const&);//作为当前节点的左孩子插入节点
	BinNodePosi(T) insertAsRc(T const&);//作为当前节点的右孩子插入节点
	BinNodePosi(T) succ(); //取当前节点的直接后继
	template <typename VST> void travLevel(VST&);//子树层次遍历
	template <typename VST> void travPre(VST&);//子树先序遍历
	template <typename VST> void travIn(VST&);//子树中序遍历
	template <typename VST> void travPost(VST&);//子树后序遍历

	//比较器，判等器等
	bool operator<(BinNode const& bn) { return data < bn.data; }
	bool operator==(BinNode const& bn) { return data == bn.data; }
};

#define IsRoot(x) (!((x).parent))
#define IsLChild(x) (!IsRoot(x) && (&(x) == (x).parent->left_child))
#define IsRChild(x) (!IsRoot(x) && (&(x) == (x).parent->right_child))
#define HasParent(x) (!IsRoot(x))
#define HasLChild(x) ((x).left_child)
#define HasRChild(x) ((x).right_child)
#define HasChild(x) (HasLChild(x) || HasRChild(x)) //至少拥有一个孩子
#define HasBothChild(x) (HasLChild(x) && HasRChild(x)) //同时拥有两个孩子
#define IsLeaf(x) (!HasChild(x))

//关于BinNode具有特定关系的节点以及指针
#define sibling(p)/*兄弟*/\
	(IsLChild(*(p)) ? (p)->parent->right_child : (p)->parent->left_child)

#define uncle(x) /*叔叔*/\
	(IsLChild(*((x)->parent)) ? (x)->parent->parent->right_child : (x)->parent->parent->left_child)

#define FromParentTo(x)/*可以获得来自其父亲的引用*/\
	(IsRoot(x) ? BinTree<T>::_root : (IsLChild(x) ? (x).parent->left_child : (x).parent->right_child))

template <typename T>
BinNode<T>* BinNode<T>::insertAsLc(T const& e)
{
	return left_child = new BinNode(e, this);
}

template <typename T>
BinNode<T>* BinNode<T>::insertAsRc(T const& e)
{
	return right_child = new BinNode(e, this);
}

template <typename T>
BinNode<T>* BinNode<T>::succ()
{
	BinNodePosi(T) s = this;
	if (right_child)
	{
		s = right_child;
		while (HasLChild(*s))
			s = s->left_child;
	}
	else
	{
		while (IsRChild(*s))
			s = s->parent;
		s = s->parent;
	}
	return s;
}



template <typename T>
class BinTree
{
protected:
	int _size;
	BinNodePosi(T) _root;//作为根节点
	//virtual int updateHeight(BinNodePosi(T) x);//更新节点x的高度
	//void updateHeightAbove(BinNodePosi(T) x);//更新节点x以及其祖先的高度

public:
	BinTree() :_size(0), _root(nullptr) {}
	//virtual ~BinTree() { if (_size > 0) remove(_root); }//析构函数
	int size() const { return _size; }//规模
	BinNodePosi(T) root() const { return _root; }
	BinNodePosi(T) insertAsRoot(T const& e);//插入根节点
	BinNodePosi(T) insertAsLC(BinNodePosi(T) x, T const& e);
	BinNodePosi(T) insertAsRC(BinNodePosi(T) x, T const& e);
	BinNodePosi(T) attachAsLC(BinNodePosi(T) x, BinTree<T>* &t);//T作为x的左子树接入
	BinNodePosi(T) attachAsRC(BinNodePosi(T) x, BinTree<T>* &t);//T作为x的右子树接入
	//int remove(BinNodePosi(T) x);//删除以位置x为根节点的子树，返回该子树原先的规模
	BinTree<T>* secede(BinNodePosi(T) x);//将子树x从当前树中摘除，并将其转化为一棵独立子树

	static int updateHeight(BinNodePosi(T) x);//更新节点x的高度
	static void updateHeightAbove(BinNodePosi(T) x);//更新节点x以及其祖先的高度

	template <typename VST>//操作器
	void travLevel(VST& visit) { if (_root) _root->travLevel(visit); }//层次遍历
	template <typename VST>
	void travPre(VST& visit) { if (_root) _root->travPre(visit); }
	template <typename VST>
	void travIn(VST& visit) { if (_root) _root->travIn(visit); }
	template <typename VST>
	void travPost(VST& visit) { if (_root) _root->travPost(visit); }//后续遍历

	bool operator<(BinTree<T> const& t)
	{
		return _root && t._root && /*need to add*/ 1;
	}
	bool operator==(BinTree<T> const& t)
	{
		return _root && t._root && (_root == t._root);
	}
};

template <typename T>
int BinTree<T>::updateHeight(BinNodePosi(T) x)
{
	return x->height = 1 + std::max(stature(x->left_child), stature(x->right_child));
}

template <typename T>
void BinTree<T>::updateHeightAbove(BinNodePosi(T) x)
{
	while (x)
	{
		updateHeight(x);
		x = x->parent;
	}
	return;
}



template <typename T>
BinNodePosi(T) BinTree<T>::insertAsRoot(T const& e)
{
	_size = 1;
	return _root = new BinNode<T>(e);
}

template <typename T>
BinNodePosi(T) BinTree<T>::insertAsLC(BinNodePosi(T) x, T const& e)
{
	++_size;
	x->insertAsLc(e);
	updateHeightAbove(x);
	return x->left_child;
}

template <typename T>
BinNodePosi(T) BinTree<T>::insertAsRC(BinNodePosi(T) x, T const& e)
{
	++_size;
	x->insertAsRc(e);
	updateHeightAbove(x);
	return x->right_child;
}

//Binary Search Tree == BST
//二叉搜索树

template <typename T>
class BST : public BinTree<T>
{
protected:
	BinNode<T>* _hot;//“命中”节点的父亲
	//BinNodePosi(T) connect34(BinNodePosi(T), BinNodePosi(T), BinNodePosi(T), BinNodePosi(T), BinNodePosi(T), BinNodePosi(T), BinNodePosi(T));//按照“3+4”的通式结构链接三个节点以及四棵子树
	BinNodePosi(T) rotateAt(BinNodePosi(T) v);//对x及其父亲、祖父做统一旋转调整
public:
	BinNodePosi(T) connect34(BinNodePosi(T), BinNodePosi(T), BinNodePosi(T), BinNodePosi(T), BinNodePosi(T), BinNodePosi(T), BinNodePosi(T));//按照“3+4”的通式结构链接三个节点以及四棵子树
	virtual BinNodePosi(T)& search(const T& e);//查找
	virtual BinNodePosi(T) insert(const T& e);//插入
	//virtual bool remove(const T& e);//删除
	//static BinNodePosi(T)& searchIn(BinNodePosi(T)& v, const T& e, BinNodePosi(T)& hot);
};

template <typename T>
static BinNodePosi(T)& searchIn(BinNodePosi(T)& v, const T& e, BinNodePosi(T)& hot)
{
	if (!v || (e == v->data))
		return v;
	hot = v;//记下当前的节点，用作之后的命中结果的父亲节点
	return searchIn(((e < v->data) ? v->left_child : v->right_child), e, hot);
}

template <typename T>
BinNodePosi(T)& BST<T>::search(const T& e)
{
	return searchIn(BinTree<T>::_root, e, _hot = nullptr);//对_hot进行赋值的更新，重新作为空进行下一步的操作
}

template <typename T>
BinNode<T>* BST<T>::insert(const T& e)
{
	BinNodePosi(T)& x = search(e);
	if (x)
		return x;//如果目标已经存在，则不需要进一步插入了
	x = new BinNode<T>(e, _hot);
	++BinTree<T>::_size;
	BinTree<T>::updateHeightAbove(x);
	
	return x;
}


template <typename T>
class ALV : public BST<T>
{
public:
	void show();
	BinNode<T>* insert(const T& e);
	//bool remove(const T& e);
};

#define Balanced(x) (stature((x).left_child) == stature((x).right_child))//理想平衡条件
#define BalFac(x) (stature((x).left_child) - stature((x).right_child))//平衡因子
#define AvlBalanced(x) ((-2 < BalFac(x)) && (BalFac(x) < 2))//AVL的平衡条件

#define tallerChild(x)(\
	stature((x)->left_child) > stature((x)->right_child) ? (x)->left_child : (\
	stature((x)->left_child) < stature((x)->right_child) ? (x)->right_child : (\
	IsLChild(*(x)) ? (x)->left_child : (x)->right_child\
	)\
	)\
)

template <typename T>
BinNode<T>* ALV<T>::insert(const T& e)
{
	BinNode<T>*& x = BST<T>::search(e);
	if (x)
		return x;
	BinNode<T>* xx = x = new BinNode<T>(e, BST<T>::_hot);
	for (BinNode<T>* g = BST<T>::_hot; g; g = g->parent)//从底向上进行调整
	{
		/*
		if (!AvlBalanced(*g))
		{
			FromParentTo(*g) = rotateAt(tallerChild(tallerChild(g)));
			break;//g恢复平衡之后，局部子树高度必然复原，其祖先亦如此，故调整就随即结束了
		}
		*/
		if (!AvlBalanced(*g))
		{
			//cout<<this->search(25)<<" can i find?"<<std::endl;
			//FromParentTo(*g) = rotateAt(tallerChild(tallerChild(g)));
			if (g->parent == nullptr)
				BinTree<T>::_root = rotateAt(tallerChild(tallerChild(g)));
			else if (IsLChild(*g))
				g->parent->left_child = rotateAt(tallerChild(tallerChild(g)));
			else
				g->parent->right_child = rotateAt(tallerChild(tallerChild(g)));
			//cout<<this->search(25)<<" can i find?"<<std::endl;
			break;//g恢复平衡之后，局部子树高度必然复原，其祖先亦如此，故调整就随即结束了
		}
		//此段函数是通过了Linux以及OJ测试的部分，不知道为什么
		else
		{
			BinTree<T>::updateHeight(g);//更新高度
		}
	}//调整至多只有一次
	//cout << "insert " << xx->data<< std::endl;
	return xx;
}

template <typename T>
BinNodePosi(T) connect34(BinNodePosi(T) a, BinNodePosi(T) b, BinNodePosi(T) c, BinNodePosi(T) T0, BinNodePosi(T) T1, BinNodePosi(T) T2, BinNodePosi(T) T3)
{
	a->left_child = T0;
	if (T0)
		T0->parent = a;
	a->right_child = T1;
	if (T1)
		T1->parent = a;
	BinTree<T>::updateHeight(a);

	c->left_child = T2;
	if (T2)
		T2->parent = c;
	c->right_child = T3;
	if (T3)
		T3->parent = c;
	BinTree<T>::updateHeight(c);

	b->left_child = a;
	a->parent = b;
	b->right_child = c;
	c->parent = b;
	BinTree<T>::updateHeight(b);
	return b;//该子树的节点
}

template <typename T>
BinNodePosi(T) rotateAt(BinNodePosi(T) v)
{
	BinNode<T>* p = v->parent;
	BinNode<T>* g = p->parent;//找到父亲，祖父节点，之后要分四种情况进行讨论

	if (IsLChild(*p))
	{
		if (IsLChild(*v))
		{
			p->parent = g->parent;//向上进行链接
			cout << "1" << std::endl;
			return connect34(v, p, g, v->left_child, v->right_child, p->right_child, g->right_child);
			//cout << "1" << std::endl;
		}
		else
		{
			v->parent = g->parent;
			cout << "2" << std::endl;
			return connect34(p, v, g, p->left_child, v->left_child, v->right_child, g->right_child);
		}
	}

	else
	{
		if (IsRChild(*v))
		{
			p->parent = g->parent;
			cout << "3" << std::endl;
			return connect34(g, p, v, g->left_child, p->left_child, v->left_child, v->right_child);
		}
		else
		{
			v->parent = g->parent;
			cout << "4" << std::endl;
			return connect34(g, v, p, g->left_child, v->left_child, v->right_child, p->right_child);
		}
	}
}
template <typename T>
void visit_root(BinNode<T>* x)
{
	//cout << "what";
	if (x)
	{
		cout << x->data << " ";
		visit_root(x->left_child);
		visit_root(x->right_child);
	}
	return;
}

template <typename T>
void ALV<T>::show()
{
	//cout << BinTree<T>::_root << std::endl;
	//cout << "what" << std::endl;
	visit_root(BinTree<T>::_root);
	return;
}




int main()
{
	ALV<int> tree;
	int n(0);
	cin >> n;
	int input;
	/*64 71 62 25 11 23 27 83 70*/
	for (int i(0); i < n; ++i)
	{
		cin >> input;
		tree.insert(input);
		//cout << input << " ";
	}
	tree.show();
	//cout << "--" << tree.search(25) << std::endl;
	return 0;
}