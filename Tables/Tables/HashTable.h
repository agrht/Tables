#pragma once
//�������-������� ����� ��� ������ � ���������� ������
#ifndef __HASHTAB__H
#define __HASHTAB__H
 
#include "Table.h"

class THashTable : public TTable
{
protected:
	virtual unsigned int HashFunc(const TKey key);
public:
	THashTable() :TTable() {}
};
#endif
