#include "ArrayHash.h"

TArrayHashTable::TArrayHashTable(int Size,int Step):TabSize(Size),HashStep(Step)
{
	pRecs = new TTabRecord[TabSize];
	Empty = TTabRecord(-1);
	Mark = TTabRecord(-2);
	for (int i = 0; i < TabSize; i++)
	{
		pRecs[i] = Empty;
	}
}

TArrayHashTable::~TArrayHashTable()
{
	delete[] pRecs;
}

//основные методы
bool TArrayHashTable::FindRecord(TKey k)
{
	Efficiency = 0;
	bool result = false;
	FreePos = -1;
	CurrPos = HashFunc(k) % TabSize;
	for (int i = 0; i < TabSize; i++)
	{
		Efficiency++;
		if (pRecs[CurrPos] == Empty)	//свободная строка-конец поиска
			break;
		else if (pRecs[CurrPos] == Mark)	//удаленная строка-запоминаем первую
		{
			if (FreePos == -1)
				FreePos = CurrPos;
		}
		else if (pRecs[CurrPos].Key == k) //нашли ключ
		{
			result = true;
			break;
		}
		CurrPos = GetNextPos(CurrPos); //открытое перемешивание
	}
	return result;
}

int TArrayHashTable::InsRecord(TKey k, TValue Val)
{
	Efficiency = 0;
	if (IsFull())
	{
		return TabFull;
	}
	else
	{
		bool res = FindRecord(k);	//поиск ключа
		if (res)
		{
			return TabRecDbl;
		}
		else
		{
			if (FreePos != -1)
			{
				CurrPos = FreePos; //используем первую пустую строку
			}
			pRecs[CurrPos] = TTabRecord(k, Val);
			DataCount++;
			Efficiency ++;
			return TabOK;
		}
	}
}

int TArrayHashTable::DelRecord(TKey k)
{
	Efficiency = 0;
	if (IsEmpty())
	{
		return TabEmpty;
	}
	else
	{
		bool res = FindRecord(k);
		if (!res)
		{
			return TabNoRec;
		}
		else
		{
			pRecs[CurrPos] = Mark;
			DataCount--;
			Efficiency ++;
			return TabOK;
		}
	}
}

//навигация
int TArrayHashTable::Reset(void)	//установить на первую запись
{
	CurrPos = 0;
	while (CurrPos < TabSize)	//поиск занятой строки
	{
		if ((pRecs[CurrPos] != Empty) && (pRecs[CurrPos] != Mark))
		{
			break;
		}
		else
		{
			CurrPos++;
		}
	}
	return IsTabEnded();
}

int TArrayHashTable::IsTabEnded(void) const //таблица завершена?
{
	return CurrPos >= TabSize;
}

int TArrayHashTable::GoNext(void)
{
	CurrPos++;
	while (CurrPos < TabSize)
	{
		if (pRecs[CurrPos] != Empty && pRecs[CurrPos] != Mark)
			break;
		else CurrPos++;
	}
	return IsTabEnded();
}

//доступ
TKey TArrayHashTable::GetKey(void) const
{
	return pRecs[CurrPos].GetKey();
}

TValue TArrayHashTable::GetValue(void) const
{
	return pRecs[CurrPos].GetValue();
}
