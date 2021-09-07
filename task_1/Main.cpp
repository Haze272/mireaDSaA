#include <iostream>

using namespace std;

void exercise1() {
	cout << "Exercise #1" << endl;

	// Определить переменную целого типа, присвоить ей значение, используя
	//	константу в шестнадцатеричной системе счисления.
	// Разработать оператор присваивания и его выражение, которое установит
	//	заданные в задании биты исходного значения переменной в значение 1,
	//	используя соответствующую маску и поразрядную операцию.
	// Номер бита - 3-ий, 11-ый, 5-ый 0010 1000 0010

	const int ns16 = 0x282;
	int variable = ns16;
	cout << variable;
}

int main() {
	exercise1();

	return 0;
}

void exercise2() {
	cout << "Exercise #2" << endl;
}

void exercise3() {
	cout << "Exercise #3" << endl;
}

void exercise4() {
	cout << "Exercise #4" << endl;
}

void exercise5() {
	cout << "Exercise #5" << endl;
}