#include <iostream>
#include <string>
#include "HashTable.h"


using namespace std;

int main() {
	HashTable hashid;

	cout << hashid.hasher("stoypa", 100) << endl;     // 72
	cout << hashid.hasher("apyots", 100) << endl;     // 72
	cout << hashid.hasher("stoypas", 100) << endl;    // 87
	cout << hashid.hasher("stoypasa", 100) << endl;   // 84
	cout << hashid.hasher("marina", 100) << endl;     // 32
	cout << hashid.hasher("gsmarina", 100) << endl;   // 50
	return 0;
}