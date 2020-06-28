#include "TreeTable.h"

bool TTreeTable::IsFull()const
{
	TTreeNode *pNode = new TTreeNode();
	bool temp = pNode == NULL;
	delete pNode;
	return temp;
}

bool TTreeTable::FindRecord(TKey k)
{
	Efficiency = 0;
	pPrev = NULL;
	pCurrent = pRoot;
	while (pCurrent != NULL)
	{
		Efficiency++;
		if (pCurrent->Key == k)
			break;
		pPrev = pCurrent;
		if (pCurrent->Key < k)
			pCurrent = pCurrent->pRight;
		else
			pCurrent = pCurrent->pLeft;
	}
	if (pCurrent != NULL)
	{
		return true;
	}
	else
	{
		pCurrent = pPrev;
		return false;
	}
}

void TTreeTable::Draw(void) 
{
	cout << "Table printing" << endl;
	DrawTreeTab(pRoot, 0);
}

int TTreeTable::InsRecord(TKey k, TValue pVal)
{
	Efficiency = 0;
	if (IsFull())
		return TabFull;
	else if (FindRecord(k) == true)
		return TabRecDbl;
	else
	{
		TTreeNode *tmp = new TTreeNode(k, pVal);
		if (pRoot == NULL)
		{
			pRoot = tmp;
		}
		else
		{
			if (k < pCurrent->Key)
			{
				pCurrent->pLeft = tmp;
			}
			else 
			{
				pCurrent->pRight = tmp;
			}
		}
		Efficiency++;
		DataCount++;
		return TabOK;
	}
}

int TTreeTable::DelRecord(TKey k)
{
	Efficiency = 0;
	if (FindRecord(k) == false)
	{
		return TabNoRec;
	}
	else
	{
		TTreeNode *pNode = pCurrent;
		if (pNode->pRight == NULL) //один потомок слева
		{
			if (pPrev == NULL)
			{//удаление корня
				pRoot = pNode->pLeft;
			}
			else
			{//удаление вершины
				if (pPrev->pRight == pNode)
				{
					pPrev->pRight = pNode->pLeft;
				}
				else
				{
					pPrev->pLeft = pNode->pLeft;
				}
			}
			Efficiency++;
		}
		else if (pNode->pLeft == NULL) //один потомок справа
		{
			if (pPrev == NULL)
			{//удаление корня
				pRoot = pNode->pRight;
			}
			else
			{//удаление вершины
				if (pPrev->pRight == pNode)
				{
					pPrev->pRight = pNode->pRight;
				}
				else
				{
					pPrev->pLeft = pNode->pRight;
				}
			}
			Efficiency++;
		}
		else
		{//два потомка поиск крайнего справа у левого поддерева
			TTreeNode *pN = pNode->pLeft;
			pPrev = pNode;
			while (pN->pRight !=NULL)
			{
				pPrev = pN;
				pN = pN->pRight;
				Efficiency++;
			}
		//вместо удаления pNode удаляется pN
			pNode->Value = pN->Value;
			pNode->Key = pN->Key;
			if (pPrev->pRight == pN)
			{
				pPrev->pRight = pN->pLeft;
			}
			else
			{
				pPrev->pLeft = pN->pLeft;
			}
			pNode = pN;
			Efficiency++;
		}
		delete pNode;
		DataCount--;
		return TabOK;
	}
}

void TTreeTable::DrawTreeTab(TTreeNode *pNode, int Level)
{
	//Efficiency = 0;
	if (pNode != NULL)
	{//печать таблицы с соблюдением ярусов
		DrawTreeTab(pNode->pRight, Level + 1);
		for (int i = 0; i < 2 * Level; i++)
		{
			std::cout << " ";
			Efficiency++;
		}
		Efficiency++;
		std::cout << *pNode;
		std::cout << std::endl;
		DrawTreeTab(pNode->pLeft, Level + 1);
	}
}

void TTreeTable::DeleteTreeTab(TTreeNode *pNode)
{
	if (pNode != NULL)
	{//удаление дерева с вершиной pNode
		DeleteTreeTab(pNode->pLeft);
		DeleteTreeTab(pNode->pRight);
		delete pNode;
	}
}

int TTreeTable::Reset()
{
	TTreeNode *pNode = pCurrent = pRoot;   
	while (!St.empty()) St.pop();  
	CurrPos = 0;
	while (pNode != NULL)
	{
		St.push(pNode);
		pCurrent = pNode;
		pNode = pNode->pLeft;
	}
	return IsTabEnded();
}

int TTreeTable::IsTabEnded() const
{
	return CurrPos >= DataCount;
}

int TTreeTable::GoNext()
{
	if (!IsTabEnded() && pCurrent != NULL)
	{
		TTreeNode *pNode = pCurrent = pCurrent->pRight;  
		St.pop();
		while (pNode != NULL)
		{
			St.push(pNode);
			pCurrent = pNode;
			pNode = pNode->pLeft;
		}	
		if (pCurrent == NULL && !St.empty())
		{
			pCurrent = St.top();
		}
		CurrPos++;
	}
	return IsTabEnded();
}

TKey TTreeTable::GetKey()const
{
	if (pCurrent != NULL)
	{
		return pCurrent->Key;
	}
	else throw NULL;
}

TValue TTreeTable::GetValue()const
{
	if (pCurrent != NULL)
	{
		return pCurrent->Value;
	}
	else throw NULL;
}

void TTreeTable::PrintTreeTab(std::ostream &os, TTreeNode *pNode)
{
	if (pNode != NULL)
	{
		for (int i = 0; i < Level; i++)
			os << " ";
		os << pNode->Key << std::endl;
		Level++;
		PrintTreeTab(os, pNode->pRight);
		PrintTreeTab(os, pNode->pLeft);
		Level--;
	}
}