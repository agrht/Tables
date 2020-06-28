#include "ScanTable.h"

bool TScanTable::FindRecord(TKey k)
{ //найти запись
	Efficiency = 0;
	int i;
	for (i = 0; i < DataCount; i++)
	{
		Efficiency++;
		if (pRecs[i].Key == k)
			break;
	}
	if (i < DataCount)
	{
		CurrPos = i;
		return true;
	}
	return false;
}

int TScanTable::InsRecord(TKey k, TValue Val)
{ 
	Efficiency = 0;
	if (IsFull()) 
	{
		return TabFull;
	}
	else 
	{
		pRecs[DataCount].Key = k;
		pRecs[DataCount].Value = Val;
		DataCount++;
		Efficiency++;
		return TabOK;
	}
}

int TScanTable::DelRecord(TKey k)
{
	Efficiency = 0;
	int temp = FindRecord(k);
	if (temp == 0) 
	{
		return temp;
	}
	else
	{
		pRecs[CurrPos] = pRecs[DataCount - 1];
		DataCount--;
		Efficiency++;
		return TabOK;
	}
}