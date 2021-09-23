#include "HashTable.h"

/*
	Суть алгоритма вычисления
индекса: к коду первого символа ключа прибавляется код последнего символа
ключа, результат - остаток от деления на длину таблицы.
	Этот метод приводит к коллизиям, только для ключей с одинаковыми
последним и первым символами.
*/
/*
int HashTable::hasher(string key, int L) {
	return (((int)key[0]) + ((int)key[key.size()])) % L;
}
*/
int HashTable::hasher(string key, int L) {
	int sum = 0;
	for (int k = 0; k < key.length(); k++)
		sum = sum + int(key[k]);
	return sum % L;
}