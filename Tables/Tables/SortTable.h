#pragma once
#ifndef __SORTTAB_H
#define __SORTTAB_H
//������������� ������ ������, ������� +����������
#include "ScanTable.h"

enum TSortMethods{SELECT_SORT=1, QUICK_SORT=2};

class TSortTable : public TScanTable
{
private:
	TTabRecord *pBuff;	//����� ��� ���������� ��������
	TSortMethods SortMethod;	//������ ������ ����������
	void SortData(void);	//���������� ������
	void SelectSort();	//�������	
	void QuickSort();	//�������
	void QuickSorter(int first, int last);
public:
	TSortTable(int Size = TabMaxSize) :TScanTable(Size)
	{
		pBuff = new TTabRecord[DataCount];
	}
	~TSortTable()
	{
		delete[]pBuff;
	}
	TSortTable(const TScanTable &tab);
	TSortTable & operator =(const TScanTable &tab);	//������������
	TSortMethods GetSortMethod(void) { return SortMethod; }
	void SetSortMethod(TSortMethods sm) { SortMethod = sm; }
	//�������� ������
	virtual bool FindRecord(TKey k);	//����� ������
	virtual int InsRecord(TKey k,TValue Val);	//�������� ������
	virtual int DelRecord(TKey k);	//������� ������
};
#endif
