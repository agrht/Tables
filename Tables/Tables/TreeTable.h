#pragma once
//Таблицы со структурой хранения в виде деревьев поиска

#ifndef __TREETAB_H
#define __TREETAB_H

#include <stack>
#include "Table.h"
#include "TreeNode.h"

class TTreeTable: public TTable
{
protected:
	TTreeNode *pRoot;	//указатель на корень дерева
	TTreeNode *pCurrent;	//указатель на текущую вершину
	TTreeNode *pPrev;	//указатель на предыдущую вершину
	int CurrPos;	//номер текущей вершины
	std::stack<TTreeNode*> St;	//стек для итератора
	int Level;
	void PrintTreeTab(std::ostream &os, TTreeNode *pNode);	//Печать
	void DrawTreeTab(TTreeNode *pNode, int Level);	//Печать с ярусами
	void DeleteTreeTab(TTreeNode *pNode);	//Удаление
public:
	TTreeTable() : TTable() { CurrPos = 0; pRoot =  pCurrent = NULL; }
	~TTreeTable() { DeleteTreeTab(pRoot); }
	//информационные методы
	virtual bool IsFull()const;	//заполнена?
	virtual int Reset(void);
	virtual int IsTabEnded(void) const;
	virtual int GoNext(void);
	//основные методы 
	virtual bool FindRecord(TKey k);	//найти запись
	virtual int InsRecord(TKey k, TValue Val);	//вставить
	virtual int DelRecord(TKey k);	//удалить запись
	//навигация
	virtual TKey GetKey(void) const;	//ключ текущей записи
	virtual TValue GetValue(void)const;	//значение
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
