#pragma once

#include"Record.h"

#define BalOK 0
#define BalLeft -1
#define BalRight 1

class TTreeNode :public TTabRecord
{
protected:
	TTreeNode *pLeft, *pRight; //указатели на поддеревья
	//int Balance; //индекс балансировки вершины (-1,0,1)
public:
	TTreeNode() { pLeft = pRight = NULL; }
	TTreeNode(TKey k, TValue v, TTreeNode *pL = NULL, TTreeNode *pR = NULL) :TTabRecord(k, v), pLeft(pL), pRight(pR) {}
	TTreeNode* GetLeft() const { return pLeft; }
	TTreeNode* GetRight() const { return pRight; }

	friend class TTreeTable;	
};
