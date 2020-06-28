#pragma once
//������� � ���������� ������-�������� �������������
#define TabHashStep 7
#include"HashTable.h"

class TArrayHashTable:public THashTable
{
protected:
	TTabRecord *pRecs;	//������ ��� ������� �������
	int TabSize;	//����������� ��������� ���������� �������
	int HashStep;	//��� ���������� �������������
	int FreePos;	//������ ��������� ������, ������������ ��� ������
	int CurrPos;	//����� ������� ������ ��� ���������� ������
	TTabRecord Mark;	//������ ��� ��������� ����� � ���������� �������� 
	TTabRecord Empty;	//������ ��� ��������� �� ������� �����
	//������� ��������� �������������
	int GetNextPos(int pos) { return (pos + HashStep) % TabSize; }
public:
	TArrayHashTable(int Size = TabMaxSize, int Step = TabHashStep);
	virtual ~TArrayHashTable();
	//�������������� ������
	virtual bool IsFull()const { return DataCount >= TabSize; }	//���������?
	//�������� ������
	virtual bool FindRecord(TKey k);	//����� ������
	virtual int InsRecord(TKey k,TValue Val);	//��������
	virtual int DelRecord(TKey k);	//������� ������
	//���������
	virtual int Reset(void);	//���������� �� ������ ������
	virtual int IsTabEnded(void)const;	//������� ���������?
	virtual int GoNext(void);	//������� � ��������� ������
	//(=1 ����� ���������� GoNext ��� ��������� ������ �������)
	//������
	virtual TKey GetKey(void)const;	//���� ������� ������
	virtual TValue GetValue(void)const;	//�������� ������� ������
};

