#include <iostream>
#include <string>
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
public:                                                  // TODO: make it private
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
        
        if (cell.nextCell) {
            cout << "DAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAMN\n";
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

    /*
    Cell elem1 = { "Fresh Ball", "886745" };
    ht.insertElement(elem1);
    Cell elem2 = { "Latex Gloves", "745886" };
    ht.insertElement(elem2);
    */
    // ht.showTable();
    Cell* elem1 = new Cell;
    elem1->article = "886745";
    elem1->name = "Fresh Ball";
    ht.insertElement(*elem1);

    Cell* elem2 = new Cell;
    elem2->article = "745886";
    elem2->name = "Latex Gloves";
    ht.insertElement(*elem2);

    ht.showTable();
    //cout << ht.hashArr[6].nextCell->article;

}