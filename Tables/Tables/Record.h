#pragma once
#ifndef _record_h
#define _record_h
#include<iostream>
#include<string>

//using namespace std

typedef int TKey;
typedef std::string TValue;

class TTabRecord
{
protected:
	TKey Key; //ключ записи
	TValue Value; //значение
public:
	TTabRecord(){}
	TTabRecord(TKey k) { Key = k; }
	TTabRecord(TKey k, TValue Val) { Key = k; Value = Val; }
	void SetKey(TKey k) { Key = k; }
	TKey GetKey(void) { return Key; }
	void SetValue(TValue p) { Value = p; }
	TValue GetValue(void) { return Value; }
	virtual int operator== (const TTabRecord &tr) { return Key == tr.Key; }
	virtual int operator!= (const TTabRecord &tr) { return Key != tr.Key; }
	virtual int operator< (const TTabRecord &tr) { return Key > tr.Key; }
	virtual int operator> (const TTabRecord &tr) { return Key < tr.Key; }
	friend std::ostream& operator<< (std::ostream &os, const TTabRecord& tr)
	{
		return os << tr.Key << "  " << tr.Value;
	}
	friend class TArrayTable; //+
	friend class TScanTable; //+
	friend class TSortTable; //+
	friend class TTreeTable;
	friend class TTreeNode;
	friend class THashTable; //+
	friend class TArrayHashTable; //+
	//friend class TListHash;
};
#endif