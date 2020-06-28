#pragma once
#ifndef __SORTTAB_H
#define __SORTTAB_H
//упорядоченные методы поиска, вставки +сортировки
#include "ScanTable.h"

enum TSortMethods{SELECT_SORT=1, QUICK_SORT=2};

class TSortTable : public TScanTable
{
private:
	TTabRecord *pBuff;	//буфер для сортировки слиянием
	TSortMethods SortMethod;	//индекс метода сортировки
	void SortData(void);	//сортировка данных
	void SelectSort();	//выбором	
	void QuickSort();	//быстрая
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
	TSortTable & operator =(const TScanTable &tab);	//присваивание
	TSortMethods GetSortMethod(void) { return SortMethod; }
	void SetSortMethod(TSortMethods sm) { SortMethod = sm; }
	//основные методы
	virtual bool FindRecord(TKey k);	//найти запись
	virtual int InsRecord(TKey k,TValue Val);	//вставить запись
	virtual int DelRecord(TKey k);	//удалить запись
};
#endif
