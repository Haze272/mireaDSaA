#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <string>
#include <map>

using namespace std;

class HashTable
{
	map <int, string> hTable;
public:

	void insertElem(string productName, int article);  // Вставить ключ в таблицу
	void deleteElem(int hashIndex);                    // Удалить ключ из таблицы
	int findKey(string productName);                   // Найти ключ в таблице

	void tableShow();								   // Вывод хештаблицы в консоль
	void rehashTable();								   // Рехешировать таблицу

	int hasher(string, int);					   // Непосредственно хэш-функция
};

#endif // HASHTABLE_H