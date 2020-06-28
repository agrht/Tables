#include "SortTable.h"

//создание упор€доченной таблицы по просматриваемой таблице
TSortTable::TSortTable(const TScanTable &tab)
{
	*this = tab;
}

//присваивание упор€доченной таблицы значени€ просматриваемой таблицы
TSortTable & TSortTable ::operator = (const TScanTable &tab)
{
	if (pRecs != NULL)
	{
		delete[]pRecs;
		delete[]pBuff;
		pRecs = NULL;
	}
	TabSize = tab.GetTabSize();
	DataCount = tab.GetDataCount();
	pRecs = new TTabRecord[TabSize];
	pBuff = new TTabRecord[TabSize];
	for (int i = 0; i < DataCount; i++)
	{
		pRecs[i] = tab.pRecs[i];
	}
	SortData();
	CurrPos = 0;
	return *this;
}

int TSortTable::InsRecord(TKey k, TValue Val)
{//вставить запись
	Efficiency = 0;
	if (IsFull()) 
	{
		return TabFull;
	}
	else
	{
		int temp = FindRecord(k);
		Efficiency ++;
		for (int i = DataCount; i > CurrPos; i--)
			pRecs[i] = pRecs[i - 1];
		pRecs[CurrPos].Key = k;
		pRecs[CurrPos].Value =  Val;
		//pRecs[CurrPos] = new TTabRecord(k, pVal);
		DataCount++;
	}
}

int TSortTable::DelRecord(TKey k) 
{
	Efficiency = 0;
	bool temp = FindRecord(k);
	for (int i = CurrPos; i < DataCount - 1; i++)
		pRecs[i] = pRecs[i + 1];
	DataCount--;
	Efficiency++;
	return TabOK;
}

void TSortTable::QuickSort()
{
	QuickSorter(0, DataCount - 1);
}

void TSortTable::QuickSorter(int first, int last)
{ 
	Efficiency = 0;
	TTabRecord elem = pRecs[(first + last) / 2];
	int i = first, j = last;
	while (i < j)
	{
		while (pRecs[i] < elem)
		{
			Efficiency++;
			i++;
		}
		while (pRecs[j] > elem)
		{
			Efficiency++;
			j--;
		}
		if (i <= j)
		{
			Efficiency++;
			TTabRecord tmp = pRecs[i];
			pRecs[i] = pRecs[j];
			pRecs[j] = tmp;
			i++;
			j--;
		}
		if (first < j)
		{
			QuickSorter(first, j);
		}
		if (i < last)
		{
			QuickSorter(i, last);
		}
	}
 }

bool TSortTable::FindRecord(TKey k)
{	//найти запись
	//двоичныintй поиск
	Efficiency = 0;
	int i, i1 = 0, i2 = DataCount - 1; //границы области поиска
	while (i1 <= i2)
	{
		Efficiency++;
		i = (i1 + i2) >> 1; //середина области поиска
		if (pRecs[i].Key == k)
		{
			i1 = i + 1;
			i2 = i;
			break;
		}
		if (pRecs[i].Key > k)
			i2 = i - 1;
		else
			i1 = i + 1;
	}
		if ((i2 < 0) || (pRecs[i2].Key < k))
			i2++;
		CurrPos = i2;
		if ((i2 < DataCount) && (pRecs[i].Key == k))
		{
			return true;
		}
		return false;
}

void TSortTable::SelectSort()
{
	Efficiency = 0;
	int index = 0;
	for (int i = 0; i < DataCount; i++)
	{
		index = i; //индекс текущего минимального элемента
		for (int j = i + 1; j < DataCount; j++)
		{
			Efficiency++;
			if (pRecs[j] < pRecs[index])
			{
				index = j;
			}
		}
		if (i != index)
		{
			Efficiency++;
			//ќбмен записей i и index
			TTabRecord tmp = pRecs[i];
			pRecs[i] = pRecs[index];
			pRecs[index] = tmp;
		}
	}
}

void TSortTable::SortData() 
{
	Efficiency = 0;
	switch (SortMethod)
	{
	/*case SELECT_SORT:
		SelectSort();break;*/
	case QUICK_SORT:
			QuickSort();break;
	}
}

