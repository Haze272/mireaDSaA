#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include <time.h>

using namespace std;

struct Cell
{
    string name = "N/A";
    string article = "N/A";

    struct Cell* nextCell;

    bool isEmpty() const {
        return article == "N/A" && name == "N/A";
    }
};

int hashIndex(string key, int hashLen)
{
    int sum = 0;
    for (int i = 0; i < key.length(); i++)
        sum += key[i];
    return sum % hashLen;
}

class HashTable {
public:
    size_t hashLength = 8;
    Cell* hashArr;
public:
    HashTable() {
        hashArr = new Cell[hashLength];
    }

    ~HashTable() {
        delete[] hashArr;
    }

    void insertElement(Cell& cell) {
        size_t hashValue = hashIndex(cell.article, hashLength);

        if (hashArr[hashValue].isEmpty()) {
            hashArr[hashValue] = cell;
        }
        else {
            hashArr[hashValue].nextCell = &cell;
        }
    }

    void showChain(Cell& cell) {
        cout << "  " << cell.article << "     " << cell.name << endl;
        if (cell.nextCell != nullptr) {
            showChain(*cell.nextCell);
        }
    }

    void showTable() {
        for (int i = 0; i < hashLength; i++) {
            if (!hashArr[i].isEmpty()) {
                cout << "Hash: " << i << endl;
                cout << "  Article    Name" << endl;
                showChain(hashArr[i]);
            }
        }
    }
};

/*
Cell elem1 = { "Dildo", "111111" };
void govno(Cell& idiot) {
    elem1.nextCell = &idiot;
}
*/

int main() {
    cout << "Testing fisting\n";
    HashTable ht;

    Cell elem1 = { "Fresh Ball", "886745" };
    ht.insertElement(elem1);
    Cell elem2 = { "Latex Gloves", "745886" };
    ht.insertElement(elem2);
    //ht.insertElement({ "Elegant", "777777" });
    // ht.showTable();
    cout << ht.hashArr[6].nextCell->article;
    
    //cout << ht.hashArr[6].nextCell->name;

    /*
    Cell elem2 = { "Vagina", "888888" };

    govno(elem2);

    cout << elem1.nextCell->article;
    */

}