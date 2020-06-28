#pragma once
#ifndef ScanTableH
#define ScanTableH
//������� � ���������������� �������� "������������ �������" (�� ������ �� ��������)
//#include"stdafx.h"
#include"ArrayTable.h"

class TScanTable: public TArrayTable
{
public:
	TScanTable(int Size = TabMaxSize) :TArrayTable(Size) {};
	//�������� ������
	virtual bool FindRecord(TKey k);	//����� ������
	virtual int InsRecord(TKey k,TValue pVal);	//�������� ������
	virtual int DelRecord(TKey k);	//������� ������
};
#endif
