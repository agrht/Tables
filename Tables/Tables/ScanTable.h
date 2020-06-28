#pragma once
#ifndef ScanTableH
#define ScanTableH
//таблица с неупорядоченными записями "Просмотровая таблица" (не следим за порядком)
//#include"stdafx.h"
#include"ArrayTable.h"

class TScanTable: public TArrayTable
{
public:
	TScanTable(int Size = TabMaxSize) :TArrayTable(Size) {};
	//основные методы
	virtual bool FindRecord(TKey k);	//найти запись
	virtual int InsRecord(TKey k,TValue pVal);	//вставить запись
	virtual int DelRecord(TKey k);	//удалить запись
};
#endif
