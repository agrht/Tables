#pragma once
#ifndef ArrayTableH
#define ArrayTableH
//базовый класс для всех производных классов, у которых записи хранятся в массиве 
//таблица на основе массива
#include "Table.h"

enum TDataPos{FIRST_POS,CURRENT_POS,LAST_POS};

class TArrayTable:public TTable
{
protected:
	//TTabRecord *pRecs;	//память для записи таблицы
	int TabSize;	//макс возм к-во записей
	int CurrPos;	//номер текущей записи (нумерация от 0)
public:
	friend class TSortTable;
	TTabRecord *pRecs;
	TArrayTable(int Size=TabMaxSize) 
	{
		pRecs = new TTabRecord[Size];
		TabSize = Size;
		DataCount = CurrPos = 0;
	}
	~TArrayTable()
	{
		delete[]pRecs;
	}
	//информационные методы
	virtual bool IsFull() const { return DataCount >= TabSize; }
	int GetTabSize() const { return TabSize; } //к-во записей
	//доступ
	//ключ
	virtual TKey GetKey(void) const
	{
		return GetKey(CURRENT_POS);
	}
	//значение
	virtual TValue GetValue(void) const
	{
		return GetValue(CURRENT_POS);
	}
	virtual TKey GetKey(TDataPos mode) const;	//ключ
	virtual TValue GetValue(TDataPos mode) const;	//значение
	//навигация
	virtual int Reset(void);	//установить на первую запись
	virtual int IsTabEnded(void)const;	//таблица завершена?
	virtual int GoNext(void);	//переход к следующей записи
	virtual int SetCurrentPos(int pos);	//установить текущую запись
	int GetCurrentPos(void)const
	{//получить номер текущей записи
		return CurrPos;
	}	
};
#endif
