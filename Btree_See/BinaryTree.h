#ifndef BINARY_TREE
#define BINARY_TREE


#include <iostream>
#include <string>
#include <stdexcept>
#include <stack>

using namespace std;

enum ChildID { LEFTCHILD = 0, RIGHTCHILD };//�ӽڵ����ͣ���ڵ�or�ҽڵ�;

template<class T> class BinaryTree;

template<class T> class BTreeNode
{
	friend class BinaryTree<T>;
public:
	BTreeNode() : pParent(0), pLChild(0), pRChild(0) {}
	BTreeNode(T elem, BTreeNode<T>* parent = 0, BTreeNode* lchild = 0, BTreeNode* rchild = 0) :
		pParent(parent), pLChild(lchild), pRChild(rchild), data(elem) {}

	T GetData() const; //��ȡ�ڵ�����;
	T& GetDataRef();         //��Ӧ���ṩ�����Ľӿڣ����������iterator�ܹ����ɷ��ʴ洢������;
	BTreeNode* GetParent() const;//��ȡ�ڵ�ĸ��ڵ�
	BTreeNode* GetLChild() const;//��ȡ�ڵ�����ӽڵ�
	BTreeNode* GetRChild() const;//��ȡ�ڵ���Һ��ӽڵ�
	void SetData(const T& elem);//�޸Ľڵ������;

	/*�����Ǹ��Ľڵ��ָ����ṹ��function���Ƿ������Ҫ��������ϸ����
	��Ϊ���Ľڵ㣬һ�㲻����ֱ�ӷ��ʽڵ��е�ָ�����ݣ������Щ��������
	����������Ժ��޸ģ����ƻ����Ľṹ;*/
	void SetParent(BTreeNode<T>* parent, ChildID CHID); //���õ�ǰ�ڵ�ĸ��ڵ㣬��ָ����ǰ�ڵ���Ϊ�ӽڵ������;
	void SetLeft(BTreeNode<T>* left);                 //���õ�ǰ�ڵ�����ӽڵ�;
	void SetRight(BTreeNode<T>* right);               //���õ�ǰ�ڵ�����ӽڵ�;


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

	if (CHID == LEFTCHILD) //��ǰ�ڵ���Ϊparent�����ӽڵ�;
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
	* �������������Ŀ����ԣ�����ֵ���͵���ȷ��ֵ�ÿ���
	* �������������ƻ����Ľṹ�����Һ����������ڴ�й©
	* ��һ���������ò�Ҫ�ṩ�������ӿ� ;
	*/
	virtual BTreeNode<T>* Parent(BTreeNode<T>* current); //����������㸸���;
	virtual BTreeNode<T>* LeftChild(BTreeNode<T>* current);      //���ؽڵ������;
	virtual BTreeNode<Ty>* RightChild(BTreeNode<T>* current);     //���ؽڵ���Һ���;

	virtual bool Insert(const T& item);        //����Ԫ��;
	virtual bool Find(const T& item) const;    //����Ԫ��;
	const BTreeNode<T>* GetRoot() const;      //ȡ����;

	//��������
	void PreOrder() const;   //ǰ��;
	void InOrder() const; //����;
	void PostOrder() const;  //����;

	//���������Բ�������
	int Size() const;
	int Size(const BTreeNode<T>* troot) const;
	int Height() const;
	int Height(const BTreeNode<T>* troot) const;
	bool operator==(const BinaryTree<T>& tree) const;

	//����Ľӿ����Բ�ͬ�ķ�ʽ������������
	BinaryTree<T>& AutoCreateTree(const std::string& expstr);            //�Զ��жϸ�ʽ������
	BinaryTree<T>& PreOrderCreateTree(const std::string& expstr);        //������
	BinaryTree<T>& PostOrderCreateTree(const std::string& expstr);       //��������

protected:
	BTreeNode< T>* Parent(BTreeNode<T>* start, BTreeNode<T>* current);
	int Insert(BTreeNode<T>* current, const T& item);
	void Travers(BTreeNode<T>* current, std::ostream& out) const;
	void Find(BTreeNode<T>* current, const T& item) const;
	void destroy(BTreeNode<T>* current);

	//�����ݹ�
	void InOrder(BTreeNode<T>* current) const;
	void PreOrder(BTreeNode<T>* current) const;
	void PostOrder(BTreeNode<T>* current) const;

	//���������Եݹ��������
	BTreeNode<T>* Copy(BTreeNode<T>* troot, BTreeNode<T>* parent);
	bool equal(BTreeNode<T>* troot1, BTreeNode<T>* troot2) const;


	//�����õĵݹ麯��
	BTreeNode<T>* PreOrderCreateNode(const char* &expstr, BTreeNode<T>* parent);    //����ݹ齨��������
	BTreeNode<T>* PostOrderCreateNode(const char* &expstr, BTreeNode<T>* parent);    //�����ݹ齨��������

	//����һ�����ڶ������ĵ�����iterator
private:
	class iterator;       //����������
	friend class iterator;
public:


	class PreOrder_iterator; //ǰ�������
	class InOrder_iterator;     //���������
	class PostOrder_iterator;   //���������
	class LevelOrder_iterator;  //���������

	friend class PreOrder_iterator;
	friend class InOrder_iterator;
	friend class PostOrder_iterator;
	friend class LevelOrder_iterator;

private:
	BTreeNode< T >* root;     //���ĸ�ָ��  
	T RefValue;              //���������ս��־

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
	destroy(root);              //����ɾ��������
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
	* ���ڽڵ㱣����parent�ĵ�ַ�����Կ���ֱ��ȡ�ø��ڵ�ĵ�ַ
	* ���ǽڵ������û��parent�����ݣ��ͱ�����õݹ��ѯ��Ѱ�Ҹ��ڵ�ĵ�ַ
	* ����Ƭ�����£���������Parent( BTreeNode<T> *start, BTreeNode<T>* current)

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
	//�ӽ��start��ʼ�������ڵ�current�ĸ���㣬
	//����ҵ��丸�ڵ㣬�������䷵�أ����򷵻� NULL
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
	//ǰ�������Ϊcurrent�Ķ�����
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
//�����������
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
	//�ݹ�˽�к������������������
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

//ǰ���������
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

//�����������
template <class T>
void BinaryTree<T>::PostOrder() const
{
	//�������
	std::cout << "PostOrder Travel Tree:/n";
	PostOrder(root);
	std::cout << std::endl;
}

template <class T>
void BinaryTree<T>::PostOrder(BTreeNode<T>* current) const {
	//����ݹ����

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
//����������Ľ����
template <class T>
int BinaryTree<T>::Size() const
{
	return Size(root);
}

template <class T>
int BinaryTree<T>::Size(const BTreeNode<T>* troot) const
{
	if (troot == NULL)  return 0;   //����,����0
	else return 1 + Size(troot->pLChild) + Size(troot->pRChild);

}

//����������ĸ߶�
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

//�ݹ鿽����˽�к�����
template <class T>
BTreeNode<T>* BinaryTree<T>::Copy(BTreeNode<T>* troot, BTreeNode<T>* parent)
{
	if (NULL == troot) return NULL;
	BTreeNode<T>* pNode = new BTreeNode<T>;
	pNode->data = troot->data;                          //��������
	pNode->pParent = parent;
	pNode->pLChild = Copy(troot->pLChild, pNode);        //�½�������
	pNode->pRChild = Copy(troot->pRChild, pNode);        //�½�������
	return pNode;                                     //�����������
}

//�ж϶����������Ƿ����
template <class T>
bool BinaryTree<T>::operator==(const BinaryTree<T>& tree) const
{
	return equal(root, tree.root);
}

//�ж϶�������ȵĵݹ����
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
		destroy(current->pLChild);    //�ݹ�ɾ������
		destroy(current->pRChild);     //���ҽڵ�
		delete current;
		current = NULL;                //����ָ��
	}
}

//define of Max function
template <class _T>
_T MAX(const _T& a, const _T& b)
{
	return (a >= b) ? a : b;
}

//*********************************************************
//1:����ʽ����������

template <class T>
BinaryTree<T>&
BinaryTree<T>::PreOrderCreateTree(const std::string& expstr)
{
	using namespace std;

	const char* exp = expstr.c_str();
	if (*exp != '#')    //��#��ͷ��ʾ�ַ�������������ʽ
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

//3��������ʽ����������
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


	if (*exp == '#' && *(exp + 1) == '#' && *(exp + 2) == '#')     //�� ##'X' ��ͷ��ʾ�ַ����Ǻ�������ʽ 'X'��ʾԪ��
	{
		destroy(root);
		exp += expstr.size() - 1;
		root = PostOrderCreateNode(exp, NULL);      //�����������
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
//���ֵ�������ʵ��

//iterator ��˽�еĻ��������,����û��ʵ�ֳ������ĵ����� const_iterator
//������ȷ�����û������ܷ��ʵ����������
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

	virtual iterator& GotoFirst() = 0;      //�α���������һ���ڵ�
	virtual bool IsEnd() = 0;               //�α��Ƿ��Ѿ�������ĩβ

	virtual iterator& operator++() = 0;         // �α�����
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
//����������ַ�ʽ��������
//1:���ü򵥼���ջ�ķǵݹ������Ҫ�������и��ڵ�������
//2������ջ�ķǵݹ�����������ע�Ͳ��֣�
//*********************************************************


//ǰ�����������(��ջ)

template <class T>
class BinaryTree<T>::PreOrder_iterator : public iterator {
	using iterator::pCurrent;
	using iterator::m_btree;
public:
	PreOrder_iterator() {}
	PreOrder_iterator(const BinaryTree<T>& tree)
	{
		m_btree = const_cast<BinaryTree<T>*>(&tree);
		GotoFirst();	//��������һ�����;  
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
			pCurrent = const_cast<BTreeNode<T>*>(m_btree->GetRoot());  //ǿ��ת��Ϊ�ǳ���ָ��
			stk.Push(1);    //��¼��ǰ���ĸ��ڵ���ʴ���
		}
		return *this;
	}

	bool IsEnd()
	{
		return pCurrent == NULL;
	}

	PreOrder_iterator& operator++();           // �α�����;
	//PreOrder_iterator operator++(int);

private:
	stack<int> stk;        //������ʽڵ�ı���������ջ;
};

template <class T>
BinaryTree<T>::PreOrder_iterator&
BinaryTree<T>::PreOrder_iterator::operator++() //ǰ���̽ڵ�;
{
	if (stk.IsEmpty())      //ȷ������������Ч��;
	{
		return *this;
	}

	//�������ӽڵ�

	if (pCurrent->GetLeft() == NULL) //��ڵ���Ч;
	{
		stk.Pop();
		stk.Push(2); //pCurrent �ڶ��η���;

		//��ѯ�ҽڵ�;
		if (pCurrent->GetRight() == NULL)  //�ҽڵ�Ҳ��Ч;
		{
			//����������Ч�Ľڵ�
			while (!stk.IsEmpty() && stk.Pop() == 2)
			{
				pCurrent = pCurrent->GetParent();
			}

			stk.Push(1);
			//�ڵ�����ӽڵ㲻�ɷ���,��������,���������ڵ�,ֹͣ����;
			while (pCurrent != NULL && pCurrent->GetRight() == NULL)
			{
				pCurrent = pCurrent->GetParent();
				stk.Pop();
			}

			//����Ѿ����������ڵ�,�׳��쳣;
			if (pCurrent == NULL)
			{
				//throw std::out_of_range("BinaryTree iterator over/n");
			}
			else
			{
				stk.Pop();
				stk.Push(2); //pCurrent���ʼ���2;

				pCurrent = pCurrent->GetRight();
				stk.Push(1);
			}
		}
		else //�ҽڵ���Ч
		{
			pCurrent = pCurrent->GetRight();
			stk.Push(1);
		}
	}
	else  //��ڵ���Ч
	{
		pCurrent = pCurrent->GetLeft();
		stk.Push(1);
	}
	return *this;
}


//�������������
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
		GotoFirst(); //��������һ�����   
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
				stk.Push(1); //�ڵ������1
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

	InOrder_iterator& operator++()           // �α�����1
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
			//�ҽڵ���Ч
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
	ChainStack<int> stk;        //������ʽڵ�ı���������ջ

};


//**********************************************************
//�������������
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
		GotoFirst(); //��������һ�����   
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
				stk.Push(1); //�ڵ������1
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

	PostOrder_iterator& operator++()            // �α�����1
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
			//���ڵ�����ҽڵ�,�Ҳ�δ���ʹ�
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
	ChainStack<int> stk;        //������ʽڵ�ı���������ջ
};

#endif
