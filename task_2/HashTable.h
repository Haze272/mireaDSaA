#pragma once
class HashTable
{
public:
	void insertElem();     // �������� ���� � �������
	void deleteElem();     // ������� ���� �� �������
	int findKey();         // ����� ���� � �������
	void rehashTable();    // ������������ �������
	void tableShow();      // ����� ���������� � �������

	int hasher();          // ��������������� ���-�������
};

