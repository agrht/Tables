#pragma once
//Таблицы с вычислимым входом-открытое перемешивание
#define TabHashStep 7
#include"HashTable.h"

class TArrayHashTable:public THashTable
{
protected:
	TTabRecord *pRecs;	//память для записей таблицы
	int TabSize;	//максимально возможное количество записей
	int HashStep;	//шаг вторичного перемешивания
	int FreePos;	//первая свободная строка, обнаруженная при поиске
	int CurrPos;	//номер текущей строки при завершении поиска
	TTabRecord Mark;	//маркер для индикации строк с удаленными записями 
	TTabRecord Empty;	//маркер для индикации не занятых строк
	//функция открытого перемешивания
	int GetNextPos(int pos) { return (pos + HashStep) % TabSize; }
public:
	TArrayHashTable(int Size = TabMaxSize, int Step = TabHashStep);
	virtual ~TArrayHashTable();
	//информационные методы
	virtual bool IsFull()const { return DataCount >= TabSize; }	//заполнена?
	//основные методы
	virtual bool FindRecord(TKey k);	//найти запись
	virtual int InsRecord(TKey k,TValue Val);	//вставить
	virtual int DelRecord(TKey k);	//удалить запись
	//навигация
	virtual int Reset(void);	//установить на первую запись
	virtual int IsTabEnded(void)const;	//таблица завершена?
	virtual int GoNext(void);	//переход к следующей записи
	//(=1 после применения GoNext для последней записи таблицы)
	//доступ
	virtual TKey GetKey(void)const;	//ключ текущей записи
	virtual TValue GetValue(void)const;	//значение текущей записи
};

