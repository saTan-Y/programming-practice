#include <iostream>
#include <algorithm>
#include <stack>
using namespace std;

struct STreeNode {
	int value;
	STreeNode* pLeft;
	STreeNode* pRight;
	STreeNode(int v):value(v),pLeft(NULL),pRight(NULL){}
};

typedef void(*VISIT)(int value);

class CBinaryTree {
private:
	STreeNode* m_pRoot;
private:
	void Destroy(STreeNode* pRoot);
	bool _Insert(STreeNode*& pRoot, int value);
	bool _Insert2(int value);
	void _PreOrder(STreeNode* pRoot, VISIT Visit) const;
	void _PreOrder2(VISIT Visit) const;
	void _InOrder(STreeNode* pRoot, VISIT Visit) const;
	void _InOrder2(VISIT Visit) const;
	void _InOrder3(VISIT Visit) const;
	void _PostOrder(STreeNode* pRoot, VISIT Visit) const;
	void _PostOrder2(VISIT Visit) const;
	void DeleteChildless(STreeNode* pParent, STreeNode* pNode);
	void DeleteSingleSon(STreeNode* pParent, STreeNode* pNode);
	bool _LargestBST(STreeNode* pRoot, int& nMin, int& nMax, int& count, int& nNumber, STreeNode*& pNode) const;
public:
	CBinaryTree();
	~CBinaryTree();
	bool Insert(int value);
	bool Delete(int value);
	STreeNode* Find(int value) const;
	void PreOrder(VISIT Visit) const;
	void InOrder(VISIT Visit) const;
	void PostOrder(VISIT Visit) const;
	int LargestBST(STreeNode*& pNode) const;	//计算this中包含的最大二叉搜索树
};

STreeNode* CBinaryTree::Find(int value) const {
	if (!m_pRoot) return NULL;
	STreeNode* pNode = m_pRoot;
	while (pNode) {
		if (pNode->value < value) {
			pNode = pNode->pRight;
		}
		else if (value < pNode->value) {
			pNode = pNode->pLeft;
		}
		else return pNode;
	}
	return NULL;
}

bool CBinaryTree::Insert(int value) {
	return _Insert(m_pRoot, value);
}

bool CBinaryTree::_Insert(STreeNode*& pRoot, int value) {
	if (!pRoot) {
		pRoot = new STreeNode(value);
		return true;
	}
	if (value < pRoot->value) {
		pRoot = pRoot->pLeft;
		return _Insert(pRoot, value);
	}
	if (pRoot->value < value) {
		pRoot = pRoot->pRight;
		return _Insert(pRoot, value);
	}
	return false;
}

bool CBinaryTree::Insert(int value) {
	return _Insert2(value);
}

bool CBinaryTree::_Insert2(int value) {
	if (!m_pRoot) {
		m_pRoot = new STreeNode(value);
		return true;
	}
	STreeNode* pNode = m_pRoot;
	STreeNode* pPre = m_pRoot;
	while (pNode) {
		pPre = pNode;
		if (value < pNode->value) {
			pNode = pNode->pLeft;
		}
		if (pNode->value < value) {
			pNode = pNode->pRight;
		}
	}
	if (value < pPre->value) {
		pPre->pLeft = new STreeNode(value);
	}
	if (pPre->value < value) {
		pPre->pRight = new STreeNode(value);
	}
}

void CBinaryTree::DeleteChildless(STreeNode* pParent, STreeNode* pCur) {
	if (pCur == m_pRoot)
		m_pRoot = NULL;
	else if (pParent->pLeft == pCur)
		pParent->pLeft = NULL;
	else if (pParent->pRight == pCur)
		pParent->pRight = NULL;
	delete pCur;
}

void CBinaryTree::DeleteSingleSon(STreeNode* pParent, STreeNode* pCur) {
	STreeNode* pCur2 = pCur->pLeft?pCur->pLeft:pCur->pRight;
	if (pCur == m_pRoot)
		m_pRoot = NULL;
	else if (pParent->pLeft == NULL)
		pParent->pRight = pCur2;
	else if (pParent->pRight == NULL)
		pParent->pLeft = pCur2;
	delete pCur;
}

bool CBinaryTree::Delete(int value) {
	if (!m_pRoot)
		return false;
	STreeNode* pParent = m_pRoot;
	STreeNode* pCur = m_pRoot;
	while (pCur) {
		if (value < pParent->value) {
			pParent = pCur;
			pCur = pParent->pLeft;
		}
		else if (pParent->value < value) {
			pParent = pCur;
			pCur = pParent->pRight;
		}
		else
			break;
	}
	if (!pCur)
		return false;
	if (!pCur->pLeft == NULL && !pCur->pRight == NULL) {
		DeleteChildless(pParent, pCur);
		//return true;
	}
	else if (!pCur->pLeft == NULL || !pCur->pRight == NULL) {
		DeleteSingleSon(pParent, pCur);
		//return true;
	}
	else {
		STreeNode* pTemp1 = pCur;
		STreeNode* pTemp2 = pCur->pLeft;
		STreeNode* pTemp3 = pTemp2->pRight;
		while (pTemp3) {
			pTemp1 = pTemp2;
			pTemp2 = pTemp3;
			pTemp3 = pTemp3->pRight;
		}
		pCur->value = pTemp2->value;
		if (!pTemp2->pLeft)
			DeleteChildless(pTemp1, pTemp2);
		else 
			DeleteSingleSon(pTemp1, pTemp2);
		delete pTemp2;
	}
	return true;
}

void CBinaryTree::PreOrder(VISIT Visit) const {
	_PreOrder(m_pRoot, Visit);
	//_PreOrder2(Visit);
}

void CBinaryTree::_PreOrder(STreeNode* pNode, VISIT Visit) const {
	if (pNode) {
		Visit(pNode->value);
		_PreOrder(pNode->pLeft, Visit);
		_PreOrder(pNode->pRight, Visit);
	}
}

void CBinaryTree::_PreOrder2(VISIT Visit) const {
	if (!m_pRoot)
		return;
	stack<STreeNode*> s;
	s.push(m_pRoot);
	STreeNode* p = m_pRoot;
	while (!s.empty()) {
		p = s.top();
		s.pop();
		Visit(p->value);
		if (p->pRight) {
			s.push(p->pRight);
		}
		if (p->pLeft)
			s.push(p->pLeft);
	}
}

void CBinaryTree::InOrder(VISIT Visit) const {
	_InOrder(m_pRoot, Visit);
	//_InOrder2(Visit);
}

void CBinaryTree::_InOrder(STreeNode* pNode, VISIT Visit) const {
	if (pNode) {
		_InOrder(pNode->pLeft, Visit);
		Visit(pNode->value);
		_InOrder(pNode->pRight, Visit);
	}
}

void CBinaryTree::_InOrder2(VISIT Visit) const {
	stack<STreeNode*> s;
	STreeNode* p = m_pRoot;
	s.push(m_pRoot);
	while (!s.empty()) {
		while (p->pLeft) {
			p = p->pLeft;
			s.push(p);
		}
		Visit(p->value);
		s.pop();
		if (!p->pRight) {
			p = p->pRight;
			s.push(p);
		}
	}
}

void CBinaryTree::_InOrder3(VISIT Visit) const {
	if (!m_pRoot)
		return;
	stack<pair<STreeNode*, int>> s;
	STreeNode* p = m_pRoot;
	s.push(make_pair(m_pRoot, 0));
	int count;
	while (!s.empty()) {
		p = s.top().first;
		count = s.top().second;
		s.pop();
		if (!count) {
			if (p->pRight)
				s.push(make_pair(p->pRight, 0));
			s.push(make_pair(p, 1));
			if (p->pLeft)
				s.push(make_pair(p->pLeft, 0));
		}
		else {
			Visit(p->value);
		}
	}
}

void CBinaryTree::PostOrder(VISIT Visit) const {
	_PostOrder(m_pRoot, Visit);
	//_InOrder2(Visit);
}

void CBinaryTree::_PostOrder(STreeNode* pNode, VISIT Visit) const {
	if (pNode) {
		_PostOrder(pNode->pLeft, Visit);
		_PostOrder(pNode->pRight, Visit);
		Visit(pNode->value);
	}
}

void CBinaryTree::_PostOrder2(VISIT Visit) const {
	if (!m_pRoot)
		return;
	stack<pair<STreeNode*, int>> s;
	STreeNode* p = m_pRoot;
	s.push(make_pair(m_pRoot, 0));
	int count;
	while (!s.empty()) {
		p = s.top().first;
		count = s.top().second;
		s.pop();
		if (!count) {
			s.push(make_pair(p, 1));
			if (p->pRight)
				s.push(make_pair(p->pRight, 0));
			if (p->pLeft)
				s.push(make_pair(p->pLeft, 0));
		}
		else {
			Visit(p->value);
		}
	}
}

void InPre2Post(const char* pInOrder, const char* pPreOrder, int length, char* pPostOrder, int nIndex) {
	if (!length)
		return;
	if (length == 1) {
		pPostOrder[nIndex] = *pPreOrder;
		nIndex++;
		return;
	}
	char root = *pPreOrder;
	int i = 0;
	for (; i < length; i++) {
		if (pInOrder[i] == root)
			break;
	}
	InPre2Post(pInOrder, pPreOrder + 1, i-1, pPostOrder, nIndex);
	InPre2Post(pInOrder + i, pPreOrder + i, length - i + 1, pPostOrder, nIndex);
	pPostOrder[nIndex] = root;
	nIndex++;
}

bool CanPostOrder(int *a, int size) {
	if (size <= 1)
		return true;
	int temp = a[size - 1];
	int i = 0;
	while (i<size-1) {
		if (a[i] > temp)
			break;
		i++;
	}
	int j = size - 2;
	while (j > i) {
		if (a[j] < temp)
			break;
		j--;
	}
	if (i != j)
		return false;
	return CanPostOrder(a, i) && CanPostOrder(a + i, size - i - 1);
}