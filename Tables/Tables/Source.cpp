#include<iostream>
#include <random>
#include <string>
using namespace std;
#include "ScanTable.h"
#include "SortTable.h"
#include "ArrayHash.h"
#include "TreeTable.h"
#include "conio.h"


enum Table { SCAN_TABLE = 1, SORT_TABLE, ARRAYHASH_TABLE, TREE_TABLE  };
TTable *pPrint = NULL;
int *pKeys = NULL;
string *pVals = NULL;
TTreeNode *pNode = NULL;
int DataCount = 0;

void Choice(Table tab)
{
	setlocale(LC_ALL, "Russian");	
	cout << "Размер таблицы: ";
	cin >> DataCount;
	int size = DataCount*3;
	switch (tab)
	{
	case SCAN_TABLE:
		pPrint = new TScanTable(size);
		pKeys = new int[size];
		pVals = new string[size];
		for (int i = 0; i < DataCount; i++)
		{
			pKeys[i] = rand() % 100;
			pVals[i] = " " + to_string(pKeys[i]);
			pPrint->InsRecord(pKeys[i], pVals[i]);
		}
		break;
	case SORT_TABLE:		
		pPrint = new TSortTable(size);
		pKeys = new int[size];
		pVals = new string[size];
		for (int i = 0; i < DataCount; i++)
		{
			pKeys[i] = rand() % 100;
			pVals[i] = " " + to_string(pKeys[i]);
			pPrint->InsRecord(pKeys[i], pVals[i]);
		}
		break;	
	case ARRAYHASH_TABLE:
		pPrint = new TArrayHashTable(size);
		pKeys = new int[size];
		pVals = new string[size];
		for (int i = 0; i < DataCount; i++)
		{
			pKeys[i] = rand() % 700;
			pVals[i] = " " + to_string(pKeys[i]);
			pPrint->InsRecord(pKeys[i], pVals[i]);
		}
		break;	
	case TREE_TABLE:
		pPrint = new TTreeTable();
		pKeys = new int[size];
		pVals = new string[size];
		for (int i = 0; i < DataCount; i++)
		{
			pKeys[i] = rand() % 200;
			pVals[i] = " " + to_string(pKeys[i]);
			pPrint->InsRecord(pKeys[i], pVals[i]);
		}
		break;
	}
}

void Menu (Table tab)
{
	setlocale(LC_ALL, "Russian");
	int k = 0;
	int key;
	string val;
	do
	{
		cout << "1 Печать" << endl;
		cout << "2 Поиск элемента" << endl; 
		cout << "3 Вставка" << endl; 
		cout << "4 Удаление" << endl; 
		cout << "5 Выход" << endl;
		cin >> k;
		switch (k)
		{
		case 1:
		{
			if (tab != TREE_TABLE)
				cout << *pPrint;
			else
				((TTreeTable*)pPrint)->Draw();
			cout << " Эффективность  = " << pPrint->GetEfficiency() << endl;
			break;
		}
		case 2:
		{
			cout << " Ключ,который ищем ";
			cin >> key;		
			if (pPrint->FindRecord(key) == 1)
				cout << " Элемент найден" << endl;
			else 
				cout << " Элемент не найден" << endl;
			cout << " Эффективность  = " << pPrint->GetEfficiency() << endl;
			break;
		}
		case 3:
		{
			cout << "Ключ, который вставляем: ";
			cin >> key;
			cout << "Значение, которое вставляем: ";
			cin >> val;
			if (DataCount >= DataCount + 10)
				cout << "Размер превышает " << endl;
			else
			{
				pKeys[DataCount] = key;
				pVals[DataCount] = val;
				pPrint->InsRecord(key, pVals[DataCount]);
				DataCount++;
			}
			cout << " Эффективность  = " << pPrint->GetEfficiency() << endl;
			break;
		}
		case 4:
		{
			cout << "Ключ, удаляемого: ";
			cin >> key;
			pPrint->DelRecord(key);
			cout << " Эффективность  = " << pPrint->GetEfficiency() << endl;
			break;
		}
		case 5:
		{
			cout << "Выход";
			break;
		}
		}
	} while (k != 5);
}

int main()
{
	int Type;	
	setlocale(LC_ALL, "Russian");
	cout << "Вид таблицы" << endl;
	cout << "1 Scan Table" << endl;
	cout << "2 Sort Table" << endl;
	cout << "3 Array Hash Table" << endl;
	cout << "4 Tree Table" << endl;
	cin >> Type;
	Choice((Table)Type);
	Menu((Table)Type);
}