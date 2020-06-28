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

//�������� ������
bool TArrayHashTable::FindRecord(TKey k)
{
	Efficiency = 0;
	bool result = false;
	FreePos = -1;
	CurrPos = HashFunc(k) % TabSize;
	for (int i = 0; i < TabSize; i++)
	{
		Efficiency++;
		if (pRecs[CurrPos] == Empty)	//��������� ������-����� ������
			break;
		else if (pRecs[CurrPos] == Mark)	//��������� ������-���������� ������
		{
			if (FreePos == -1)
				FreePos = CurrPos;
		}
		else if (pRecs[CurrPos].Key == k) //����� ����
		{
			result = true;
			break;
		}
		CurrPos = GetNextPos(CurrPos); //�������� �������������
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
		bool res = FindRecord(k);	//����� �����
		if (res)
		{
			return TabRecDbl;
		}
		else
		{
			if (FreePos != -1)
			{
				CurrPos = FreePos; //���������� ������ ������ ������
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

//���������
int TArrayHashTable::Reset(void)	//���������� �� ������ ������
{
	CurrPos = 0;
	while (CurrPos < TabSize)	//����� ������� ������
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

int TArrayHashTable::IsTabEnded(void) const //������� ���������?
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

//������
TKey TArrayHashTable::GetKey(void) const
{
	return pRecs[CurrPos].GetKey();
}

TValue TArrayHashTable::GetValue(void) const
{
	return pRecs[CurrPos].GetValue();
}
