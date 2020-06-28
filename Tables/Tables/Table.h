#pragma once
using namespace std;
#ifndef _table_h
#define _table_h

#include <iostream>
#include "record.h"

#define TabOK        0 // ошибок нет 
#define TabEmpty  -101 // таюлица пуста
#define TabFull   -102 // таблица полна
#define TabNoRec  -103 // нет записи
#define TabRecDbl -104 // дублирование записи
#define TabNoMem  -105 // нет памяти

#define TabMaxSize 25

class TTable
{
protected:
	int DataCount; //количество записей в таблице
	int Efficiency; //показатель эффективности выполнения операции
public:
	TTable() { DataCount = 0; Efficiency = 0; }
	virtual ~TTable() {}
	//информационные методы
	int GetDataCount() const { return DataCount; } //число записей
	int GetEfficiency() const { return Efficiency; } //получить эффективность
	void ClearEfficiency() { Efficiency = 0; }	//обнулить счётчик операций
	bool IsEmpty() const { return DataCount == 0; }	//пуста?
	virtual bool IsFull() const = 0;	//заполнена?
	//основные методы
	virtual bool FindRecord(TKey k) = 0;	//найти запись
	virtual int InsRecord(TKey k, TValue pVal) = 0;	//вставить
	virtual int DelRecord(TKey k) = 0;	//удалить запись
	//навигация
	virtual int Reset(void) = 0;	//установить на первую запись
	virtual int IsTabEnded(void) const = 0;	//таюлица завершена?
	virtual int GoNext(void) = 0; //переход к следующей записи 
	//доступ
	virtual TKey GetKey(void)const = 0;
	virtual TValue GetValue(void) const = 0;
	//Печать таблицы
	friend std::ostream& operator<<(std::ostream &os,TTable &tab) 
	{
		os << "Table printing" << std::endl;
		for (tab.Reset(); !tab.IsTabEnded(); tab.GoNext())
		{
			os << "Key:  " << tab.GetKey()
			   << "		Val:  " << tab.GetValue() << std::endl;
		}
		return os;
	}
	//вывод таблицы на форму
	/*void Print (System::Windows::Forms::DataGridView^ grid)
	{
		grid->ColumnCount = 2;
		grid->RowCount = DataCount;
		int i = 0;
		for (Reset(); !IsTabEnded(); GoNext())
		{
			grid[0, i]->Value = GetKey();
			grid[1, i]->Value = gcnew System::(GetValue().c_str());
			i++;
		}
	}*/
};
#endif