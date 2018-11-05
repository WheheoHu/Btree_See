#ifndef BINARY_TREE
#define BINARY_TREE


#include <iostream>
#include <string>
#include <stdexcept>
#include <stack>

using namespace std;

enum ChildID { LEFTCHILD = 0, RIGHTCHILD };//子节点类型，左节点or右节点;

template<class T> class BinaryTree;

template<class T> class BTreeNode
{
	friend class BinaryTree<T>;
public:
	BTreeNode() : pParent(0), pLChild(0), pRChild(0) {}
	BTreeNode(T elem, BTreeNode<T>* parent = 0, BTreeNode* lchild = 0, BTreeNode* rchild = 0) :
		pParent(parent), pLChild(lchild), pRChild(rchild), data(elem) {}

	T GetData() const; //获取节点数据;
	T& GetDataRef();         //不应当提供这样的接口，这里仅仅让iterator能够自由访问存储的数据;
	BTreeNode* GetParent() const;//获取节点的父节点
	BTreeNode* GetLChild() const;//获取节点的左孩子节点
	BTreeNode* GetRChild() const;//获取节点的右孩子节点
	void SetData(const T& elem);//修改节点的数据;

	/*下面是更改节点的指针域结构的function，是否真的需要，还得仔细考量
	做为树的节点，一般不允许直接访问节点中的指针数据，如果这些数据在树
	被建立完成以后修改，会破坏树的结构;*/
	void SetParent(BTreeNode<T>* parent, ChildID CHID); //设置当前节点的父节点，并指定当前节点作为子节点的类型;
	void SetLeft(BTreeNode<T>* left);                 //设置当前节点的左子节点;
	void SetRight(BTreeNode<T>* right);               //设置当前节点的右子节点;


private:
	BTreeNode<T>* pParent;
	BTreeNode<T>* pLChild;
	BTreeNode<T>* pRChild;
	T data;
};
//declare BTreeNode end

//*********************************************************
// BTreeNode Implementation
//*********************************************************

template<class T> T BTreeNode<T>::GetData() const
{
	return data;
}

template<class T>T& BTreeNode<T>::GetDataRef()
{
	return data;
}

template<class T>
inline BTreeNode * BTreeNode<T>::GetParent() const
{
	return pParent;
}


template<class T>T BTreeNode<T>::GetRChild() const
{
	return pRChild;
}

template<class T>T BTreeNode<T>::GetLChild() const
{
	return pLChild;
}

template<class T>T BTreeNode<T>::SetData(const T& elem)
{
	data = elem;
}

template<class T>void BTreeNode<T>::SetParent(BTreeNode<T>* parent, ChildID CHID)
{
	if (!parent) return;

	if (CHID == LEFTCHILD) //当前节点作为parent的左子节点;
	{
		pParent = parent;
		parent->pLChild = this;
	}
	else if (CHID == RIGHTCHILD)
	{
		pParent = parent;
		parent->rLChild = this;
	}
}

template<class T>void BTreeNode<T>::SetLeft(BTreeNode<T>* left)
{
	pLChild = left;
}
template<class T>void BTreeNode<T>::SetRight(BTreeNode<T>* right)
{
	pRChild = right;
}

// BTreeNode Implementation over
//*********************************************************
//*********************************************************

template<class T> class BinaryTree
{
public:
	BinaryTree() : root(NULL) {}
	BinaryTree(T value) : RefValue(value), root(NULL) {}
	BinaryTree(const BinaryTree<T>& tree);                 //copy ConstruBcture privated
	BinaryTree<T>& operator=(const BinaryTree<T>& tree); //operator= privated

	virtual ~BinaryTree();
	virtual int IsEmpty() { return root == NULL; }

	/*
	* 下面三个函数的可用性，返回值类型的正确性值得考量
	* 这样做不仅会破坏树的结构，而且很容易引起内存泄漏
	* 在一般的树中最好不要提供这三个接口 ;
	*/
	virtual BTreeNode<T>* Parent(BTreeNode<T>* current); //返回所给结点父结点;
	virtual BTreeNode<T>* LeftChild(BTreeNode<T>* current);      //返回节点的左孩子;
	virtual BTreeNode<Ty>* RightChild(BTreeNode<T>* current);     //返回节点的右孩子;

	virtual bool Insert(const T& item);        //插入元素;
	virtual bool Find(const T& item) const;    //搜索元素;
	const BTreeNode<T>* GetRoot() const;      //取树根;

	//遍历操作
	void PreOrder() const;   //前序;
	void InOrder() const; //中序;
	void PostOrder() const;  //后序;

	//二叉树特性操作函数
	int Size() const;
	int Size(const BTreeNode<T>* troot) const;
	int Height() const;
	int Height(const BTreeNode<T>* troot) const;
	bool operator==(const BinaryTree<T>& tree) const;

	//下面的接口是以不同的方式来构建二叉树
	BinaryTree<T>& AutoCreateTree(const std::string& expstr);            //自动判断格式并建立
	BinaryTree<T>& PreOrderCreateTree(const std::string& expstr);        //先序建立
	BinaryTree<T>& PostOrderCreateTree(const std::string& expstr);       //后续建立

protected:
	BTreeNode< T>* Parent(BTreeNode<T>* start, BTreeNode<T>* current);
	int Insert(BTreeNode<T>* current, const T& item);
	void Travers(BTreeNode<T>* current, std::ostream& out) const;
	void Find(BTreeNode<T>* current, const T& item) const;
	void destroy(BTreeNode<T>* current);

	//遍历递归
	void InOrder(BTreeNode<T>* current) const;
	void PreOrder(BTreeNode<T>* current) const;
	void PostOrder(BTreeNode<T>* current) const;

	//二叉树特性递归操作函数
	BTreeNode<T>* Copy(BTreeNode<T>* troot, BTreeNode<T>* parent);
	bool equal(BTreeNode<T>* troot1, BTreeNode<T>* troot2) const;


	//建树用的递归函数
	BTreeNode<T>* PreOrderCreateNode(const char* &expstr, BTreeNode<T>* parent);    //先序递归建立二叉树
	BTreeNode<T>* PostOrderCreateNode(const char* &expstr, BTreeNode<T>* parent);    //后续递归建立二叉树

	//声明一组用于二叉树的迭代器iterator
private:
	class iterator;       //迭代器基类
	friend class iterator;
public:


	class PreOrder_iterator; //前序迭代器
	class InOrder_iterator;     //中序迭代器
	class PostOrder_iterator;   //后序迭代器
	class LevelOrder_iterator;  //层序迭代器

	friend class PreOrder_iterator;
	friend class InOrder_iterator;
	friend class PostOrder_iterator;
	friend class LevelOrder_iterator;

private:
	BTreeNode< T >* root;     //树的根指针  
	T RefValue;              //数据输入终结标志

};
//END BinaryTree
/**********************************
 * implament of template BinaryTree
 *
 **********************************/
template <class T>
BinaryTree<T>::BinaryTree(const BinaryTree<T>& tree)   //copy Constructor
{
	root = Copy(tree.root, NULL);
}

template <class T> BinaryTree<T>& BinaryTree<T>::operator=(const BinaryTree<T>& tree)     //operator= constructor
{
	destroy(root);
	root = Copy(tree.root, NULL);
	return *this;
}
template <class T> BinaryTree<T>::~BinaryTree()
{
	destroy(root);              //遍历删除二叉树
}

template <class T> bool BinaryTree<T>::Insert(const T& item)
{
	return true;
}

template <class T>bool BinaryTree<T>::Find(const T& item) const
{
	return true;
}

template <class T>BTreeNode<T>* BinaryTree<T>::Parent(BTreeNode<T>* current)
{
	if (root == NULL || root == current)
	{
		return NULL;
	}
	else
	{
		return current->pParent;
	}
	/*
	* 由于节点保留了parent的地址，所以可以直接取得父节点的地址
	* 但是节点中如果没有parent的数据，就必须调用递归查询来寻找父节点的地址
	* 代码片断如下，它调用了Parent( BTreeNode<T> *start, BTreeNode<T>* current)

	 return (root == NULL || root == current) ? NULL : Parent( root, current);

	 */
}

template <class T>BTreeNode<T>* BinaryTree<T>::LeftChild(BTreeNode<T>* current)
{
	return current != NULL ? current->pLChild : NULL;
}

template <class T>BTreeNode<T>* BinaryTree<T>::RightChild(BTreeNode<T>* current)
{
	return current != NULL ? current->pRChild : NULL;
}

template <class T>BTreeNode<T>* BinaryTree<T>::Parent(BTreeNode<T> *start, BTreeNode<T>* current)
{
	//从结点start开始，搜索节点current的父结点，
	//如果找到其父节点，则函数将其返回，否则返回 NULL
	if (!start) return NULL;
	if (start->pLChild == current || start->pRChild == current)
		return start;

	BTreeNode<T> *pNode;
	if ((pNode = Parent(start->pLChild, current)) != NULL)
	{
		return pNode;
	}
	else
	{
		return Parent(start->pRChild, current);
	}
}

template <class T> const BTreeNode<T>* BinaryTree<T>::GetRoot() const
{
	return root;
}

template <class T>
void BinaryTree<T>::Travers(BTreeNode<T>* current, std::ostream& out) const
{
	//前序输出根为current的二叉数
	if (current) {
		out << current->data;
		Travers(current->pLChild, out);
		Travers(current->pRChild, out);
	}
	else
	{
		out << "#";
	}
}
//中序遍历操作
template <class T>
void BinaryTree<T>::InOrder() const
{
	std::cout << "InOrder Traval Tree:/n";
	InOrder(root);
	std::cout << std::endl;
}

template <class T>
void BinaryTree<T>::InOrder(BTreeNode<T>* current) const
{
	//递归私有函数，中序遍历二叉树
	if (current != NULL) {
		InOrder(current->pLChild);
		std::cout << current->data;
		InOrder(current->pRChild);
	}
	else
	{
		std::cout << "#";
	}
}

//前序遍历操作
template <class T>
void BinaryTree<T>::PreOrder() const
{
	std::cout << "PreOrder Travel Tree:/n";
	PreOrder(root);
	std::cout << std::endl;
}

template <class T>
void BinaryTree<T>::PreOrder(BTreeNode<T>* current) const
{
	if (current != NULL) {
		std::cout << current->data;
		PreOrder(current->pLChild);
		PreOrder(current->pRChild);
	}
	else
	{
		std::cout << "#";
	}
}

//后序遍历操作
template <class T>
void BinaryTree<T>::PostOrder() const
{
	//后序遍历
	std::cout << "PostOrder Travel Tree:/n";
	PostOrder(root);
	std::cout << std::endl;
}

template <class T>
void BinaryTree<T>::PostOrder(BTreeNode<T>* current) const {
	//后序递归操作

	if (current != NULL) {
		PostOrder(current->pLChild);
		PostOrder(current->pRChild);
		std::cout << current->data;
	}
	else
	{
		std::cout << "#";
	}
}
//计算二叉树的结点数
template <class T>
int BinaryTree<T>::Size() const
{
	return Size(root);
}

template <class T>
int BinaryTree<T>::Size(const BTreeNode<T>* troot) const
{
	if (troot == NULL)  return 0;   //空树,返回0
	else return 1 + Size(troot->pLChild) + Size(troot->pRChild);

}

//计算二叉树的高度
template <class T>
int BinaryTree<T>::Height() const
{
	return Height(root);
}

template <class T>
int BinaryTree<T>::Height(const BTreeNode<T>* troot) const
{
	if (troot == NULL) return -1;
	else return 1 + MAX(Height(troot->pLChild), Height(troot->pRChild));
}

//递归拷贝的私有函数；
template <class T>
BTreeNode<T>* BinaryTree<T>::Copy(BTreeNode<T>* troot, BTreeNode<T>* parent)
{
	if (NULL == troot) return NULL;
	BTreeNode<T>* pNode = new BTreeNode<T>;
	pNode->data = troot->data;                          //拷贝数据
	pNode->pParent = parent;
	pNode->pLChild = Copy(troot->pLChild, pNode);        //新建左子树
	pNode->pRChild = Copy(troot->pRChild, pNode);        //新建右子树
	return pNode;                                     //返回树根结点
}

//判断二叉树内容是否相等
template <class T>
bool BinaryTree<T>::operator==(const BinaryTree<T>& tree) const
{
	return equal(root, tree.root);
}

//判断二叉树相等的递归操作
template <class T>
bool BinaryTree<T>::equal(BTreeNode<T>* troot1, BTreeNode<T>* troot2) const
{
	if (NULL == troot1 && NULL == troot2) return true;
	if ((NULL == troot1 && NULL != troot2)
		|| (NULL != troot1 && NULL == troot2)
		|| (troot1->data != troot2->data)) {
		return false;
	}
	else {
		return equal(troot1->pLChild, troot2->pLChild) && equal(troot1->pRChild, troot2->pRChild);
	}
	return true;
}

template <class T>
void BinaryTree<T>::destroy(BTreeNode<T>* current) {
	if (current) {
		destroy(current->pLChild);    //递归删除左结点
		destroy(current->pRChild);     //除右节点
		delete current;
		current = NULL;                //空置指针
	}
}

//define of Max function
template <class _T>
_T MAX(const _T& a, const _T& b)
{
	return (a >= b) ? a : b;
}

//*********************************************************
//1:先序方式建立二叉树

template <class T>
BinaryTree<T>&
BinaryTree<T>::PreOrderCreateTree(const std::string& expstr)
{
	using namespace std;

	const char* exp = expstr.c_str();
	if (*exp != '#')    //以#开头表示字符串不是先序表达式
	{
		destroy(root);
		root = PreOrderCreateNode(exp, NULL);
	}
	else
	{
		cout << "Your string expression error, I can't Create B-Tree :)/n";
	}

	return *this;
}

template <class T>
BTreeNode<T>*
BinaryTree<T>::PreOrderCreateNode(const char* &expstr, BTreeNode<T>* parent)
{
	if (*expstr == '#' || *expstr == '/0') return NULL;
	BTreeNode<T>* pnewNode = new BTreeNode<T>(*expstr, parent);

	assert(pnewNode);

	pnewNode->pLChild = PreOrderCreateNode(++expstr, pnewNode);
	pnewNode->pRChild = PreOrderCreateNode(++expstr, pnewNode);
	return pnewNode;
}

//*********************************************************

//*********************************************************

//3：后续方式建立二叉树
template <class T>
BinaryTree<T>&
BinaryTree<T>::PostOrderCreateTree(const std::string& expstr)
{
	using namespace std;
	const char* exp = expstr.c_str();
	if (expstr.size() < 3)
	{
		destroy(root);
		return *this;
	}


	if (*exp == '#' && *(exp + 1) == '#' && *(exp + 2) == '#')     //以 ##'X' 开头表示字符串是后续序表达式 'X'表示元素
	{
		destroy(root);
		exp += expstr.size() - 1;
		root = PostOrderCreateNode(exp, NULL);      //反向遍历生成
	}
	else
	{
		cout << "Your string expression error, I can't Create B-Tree :)/n";
	}

	return *this;

}

template <class T>
BTreeNode<T>*
BinaryTree<T>::PostOrderCreateNode(const char* &expstr, BTreeNode<T>* parent)
{
	if (*expstr == '#') return NULL;
	BTreeNode<T>* pnewNode = new BTreeNode<T>(*expstr, parent);

	assert(pnewNode);
	pnewNode->pRChild = PostOrderCreateNode(--expstr, pnewNode);

	pnewNode->pLChild = PostOrderCreateNode(--expstr, pnewNode);

	return pnewNode;
}

//********************************************************
//********************************************************
//三种迭代器的实现

//iterator 是私有的基类迭代器,这里没有实现常量树的迭代器 const_iterator
//这样做确保了用户不可能访问到这个迭代器
template <class T>
class BinaryTree<T>::iterator {
public:
	iterator() :m_btree(NULL), pCurrent(NULL) {}
	virtual ~iterator() {}

	virtual iterator& operator= (const iterator& iter)
	{
		pCurrent = iter.pCurrent;
		return *this;
	}

	virtual iterator& GotoFirst() = 0;      //游标索引到第一个节点
	virtual bool IsEnd() = 0;               //游标是否已经索引到末尾

	virtual iterator& operator++() = 0;         // 游标自增
	//virtual iterator operator++(int) = 0;

	virtual const T& current() const;
	virtual T& operator*();
	virtual T* operator->();
protected:
	BinaryTree<T>* m_btree;
	BTreeNode<T>* pCurrent;
};

template <class T>
const T&
BinaryTree<T>::iterator::current() const
{
	if (pCurrent != NULL)
	{
		return pCurrent->GetDataRef();
	}
	else
	{
		throw std::out_of_range("iterator error/n");
	}
}

template <class T>
T&
BinaryTree<T>::iterator::operator*()
{
	if (pCurrent != NULL)
	{
		return pCurrent->GetDataRef();
	}
	else
	{
		throw std::out_of_range("iterator error/n");
	}
}

template <class T>
T*
BinaryTree<T>::iterator::operator->()
{
	if (pCurrent != NULL)
	{
		return &(pCurrent->GetDataRef());
	}
	else
	{
		throw std::out_of_range("iterator error/n");
	}

}

//*********************************************************
//这里采用两种方式来遍历树
//1:采用简单计数栈的非递归遍历（要求结点中有父节点数据域）
//2：采用栈的非递归遍历（在最后注释部分）
//*********************************************************


//前序遍历迭代器(无栈)

template <class T>
class BinaryTree<T>::PreOrder_iterator : public iterator {
	using iterator::pCurrent;
	using iterator::m_btree;
public:
	PreOrder_iterator() {}
	PreOrder_iterator(const BinaryTree<T>& tree)
	{
		m_btree = const_cast<BinaryTree<T>*>(&tree);
		GotoFirst();	//索引至第一个结点;  
	}

	PreOrder_iterator(const PreOrder_iterator& iter) {
		m_btree = iter.m_btree;
		pCurrent = iter.pCurrent;
	}

	PreOrder_iterator& GotoFirst()
	{
		stk.MakeEmpty();
		if (m_btree == NULL)
		{
			stk.MakeEmpty();
			pCurrent = NULL;
		}
		else
		{
			pCurrent = const_cast<BTreeNode<T>*>(m_btree->GetRoot());  //强制转换为非常量指针
			stk.Push(1);    //记录当前树的根节点访问次数
		}
		return *this;
	}

	bool IsEnd()
	{
		return pCurrent == NULL;
	}

	PreOrder_iterator& operator++();           // 游标自增;
	//PreOrder_iterator operator++(int);

private:
	stack<int> stk;        //保存访问节点的遍历次数的栈;
};

template <class T>
BinaryTree<T>::PreOrder_iterator&
BinaryTree<T>::PreOrder_iterator::operator++() //前序后继节点;
{
	if (stk.IsEmpty())      //确保迭代器是有效的;
	{
		return *this;
	}

	//访问左子节点

	if (pCurrent->GetLeft() == NULL) //左节点无效;
	{
		stk.Pop();
		stk.Push(2); //pCurrent 第二次访问;

		//查询右节点;
		if (pCurrent->GetRight() == NULL)  //右节点也无效;
		{
			//回溯搜索有效的节点
			while (!stk.IsEmpty() && stk.Pop() == 2)
			{
				pCurrent = pCurrent->GetParent();
			}

			stk.Push(1);
			//节点的右子节点不可访问,继续回溯,搜索到跟节点,停止搜索;
			while (pCurrent != NULL && pCurrent->GetRight() == NULL)
			{
				pCurrent = pCurrent->GetParent();
				stk.Pop();
			}

			//如果已经搜索出根节点,抛出异常;
			if (pCurrent == NULL)
			{
				//throw std::out_of_range("BinaryTree iterator over/n");
			}
			else
			{
				stk.Pop();
				stk.Push(2); //pCurrent访问计数2;

				pCurrent = pCurrent->GetRight();
				stk.Push(1);
			}
		}
		else //右节点有效
		{
			pCurrent = pCurrent->GetRight();
			stk.Push(1);
		}
	}
	else  //左节点有效
	{
		pCurrent = pCurrent->GetLeft();
		stk.Push(1);
	}
	return *this;
}


//中序遍历迭代器
//InOrder_iterator


template <class T>
class BinaryTree<T>::InOrder_iterator : public iterator {
	using iterator::pCurrent;
	using iterator::m_btree;
public:
	InOrder_iterator() {}
	InOrder_iterator(const BinaryTree<T>& tree)
	{
		m_btree = const_cast<BinaryTree<T>*>(&tree);
		GotoFirst(); //索引至第一个结点   
	}

	InOrder_iterator(const PreOrder_iterator& iter) {
		m_btree = iter.m_btree;
		pCurrent = iter.pCurrent;
	}

	InOrder_iterator& GotoFirst()
	{
		stk.MakeEmpty();
		if (m_btree == NULL)
		{
			stk.MakeEmpty();
			pCurrent = NULL;
		}
		else
		{
			pCurrent = const_cast<BTreeNode<T>*>(m_btree->GetRoot());
			if (pCurrent != NULL)
			{
				stk.Push(1); //节点计数进1
				while (pCurrent->GetLeft() != NULL)
				{
					pCurrent = pCurrent->GetLeft();
					stk.Push(1);
				}
			}
		}
		return *this;
	}


	bool IsEnd()
	{
		return pCurrent == NULL;
	}

	InOrder_iterator& operator++()           // 游标自增1
	{
		if (IsEnd())
		{
			return *this;
		}

		if (pCurrent->GetRight() == NULL)
		{
			stk.Pop();
			stk.Push(2);
			while (!stk.IsEmpty() && stk.Pop() == 2)
			{
				pCurrent = pCurrent->GetParent();
			}
			stk.Push(2);
			return *this;
		}
		else
		{
			//右节点有效
			stk.Pop();
			stk.Push(2);
			pCurrent = pCurrent->GetRight();
			stk.Push(1);

			while (pCurrent->GetLeft() != NULL)
			{
				pCurrent = pCurrent->GetLeft();
				stk.Push(1);
			}
		}
		return *this;
	}
	//InOrder_iterator operator++(int);

private:
	ChainStack<int> stk;        //保存访问节点的遍历次数的栈

};


//**********************************************************
//后序遍历迭代器
//PostOrder_iterator
template <class T>
class BinaryTree<T>::PostOrder_iterator : public iterator {
	using iterator::pCurrent;
	using iterator::m_btree;
public:
	PostOrder_iterator() {}
	PostOrder_iterator(const BinaryTree<T>& tree)
	{
		m_btree = const_cast<BinaryTree<T>*>(&tree);
		GotoFirst(); //索引至第一个结点   
	}

	PostOrder_iterator(const PreOrder_iterator& iter) {
		m_btree = iter.m_btree;
		pCurrent = iter.pCurrent;
	}

	PostOrder_iterator& GotoFirst()
	{
		stk.MakeEmpty();
		if (m_btree == NULL)
		{
			stk.MakeEmpty();
			pCurrent = NULL;
		}
		else
		{
			pCurrent = const_cast<BTreeNode<T>*>(m_btree->GetRoot());
			if (pCurrent != NULL)
			{
				stk.Push(1); //节点计数进1
				while (pCurrent->GetLeft() != NULL || pCurrent->GetRight() != NULL)
				{
					if (pCurrent->GetLeft() != NULL)
					{
						pCurrent = pCurrent->GetLeft();
						stk.Push(1);
					}
					else if (pCurrent->GetRight() != NULL)
					{
						stk.Pop();
						stk.Push(2);
						pCurrent = pCurrent->GetRight();
						stk.Push(1);
					}
				}
			}
		}
		return *this;
	}

	bool IsEnd()
	{
		return pCurrent == NULL;
	}

	PostOrder_iterator& operator++()            // 游标自增1
	{
		if (IsEnd())
		{
			return *this;
		}

		if (pCurrent->GetRight() == NULL || stk.GetTop() == 2)
		{
			pCurrent = pCurrent->GetParent();
			stk.Pop();
		}
		if (pCurrent != NULL && pCurrent->GetRight() != NULL && stk.GetTop() == 1)
		{
			//父节点存在右节点,且并未访问过
			stk.Pop();
			stk.Push(2);
			pCurrent = pCurrent->GetRight();
			stk.Push(1);
			while (pCurrent->GetLeft() != NULL || pCurrent->GetRight() != NULL)
			{
				if (pCurrent->GetLeft() != NULL)
				{
					pCurrent = pCurrent->GetLeft();
					stk.Push(1);
				}
				else if (pCurrent->GetRight() != NULL)
				{
					stk.Pop();
					stk.Push(2);
					pCurrent = pCurrent->GetRight();
					stk.Push(1);
				}
			}
		}
		return *this;
	}

private:
	ChainStack<int> stk;        //保存访问节点的遍历次数的栈
};

#endif
