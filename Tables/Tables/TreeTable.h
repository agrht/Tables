#pragma once
//������� �� ���������� �������� � ���� �������� ������

#ifndef __TREETAB_H
#define __TREETAB_H

#include <stack>
#include "Table.h"
#include "TreeNode.h"

class TTreeTable: public TTable
{
protected:
	TTreeNode *pRoot;	//��������� �� ������ ������
	TTreeNode *pCurrent;	//��������� �� ������� �������
	TTreeNode *pPrev;	//��������� �� ���������� �������
	int CurrPos;	//����� ������� �������
	std::stack<TTreeNode*> St;	//���� ��� ���������
	int Level;
	void PrintTreeTab(std::ostream &os, TTreeNode *pNode);	//������
	void DrawTreeTab(TTreeNode *pNode, int Level);	//������ � �������
	void DeleteTreeTab(TTreeNode *pNode);	//��������
public:
	TTreeTable() : TTable() { CurrPos = 0; pRoot =  pCurrent = NULL; }
	~TTreeTable() { DeleteTreeTab(pRoot); }
	//�������������� ������
	virtual bool IsFull()const;	//���������?
	virtual int Reset(void);
	virtual int IsTabEnded(void) const;
	virtual int GoNext(void);
	//�������� ������ 
	virtual bool FindRecord(TKey k);	//����� ������
	virtual int InsRecord(TKey k, TValue Val);	//��������
	virtual int DelRecord(TKey k);	//������� ������
	//���������
	virtual TKey GetKey(void) const;	//���� ������� ������
	virtual TValue GetValue(void)const;	//��������
	void Draw(void);
	friend std::istream & operator >>(istream& is, TTreeTable &tab)
	{
		int data_count;
		TKey k;
		TValue v;
		std::cout << "enter DataCount" << std::endl;
		is >> data_count;
		std::cout << "enter Key and Value" << std::endl;
		for (int i = 0; i < data_count; i++)
		{
			is >> k;
			is >> v;
			tab.InsRecord(k, v);
		}
		return is;
	}
	/*friend std::ostream & operator <<(ostream& os, TTreeTable &tab)
	{
		tab.PrintTable(os);
		return os;
	}*/
};
#endif
