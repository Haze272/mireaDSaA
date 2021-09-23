#pragma once
class HashTable
{
public:
	void insertElem();     // Вставить ключ в таблицу
	void deleteElem();     // Удалить ключ из таблицы
	int findKey();         // Найти ключ в таблице
	void rehashTable();    // Рехешировать таблицу
	void tableShow();      // Вывод хештаблицы в консоль

	int hasher();          // Непосредственно хэш-функция
};

