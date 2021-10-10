#include <iostream>
#include <string>
#include <fstream>
#include <time.h>

using namespace std;

struct Cell
{
    string name = "N/A";
    string article = "N/A";

    struct Cell* nextCell = nullptr;

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
    Cell* anyElement;
public:
    HashTable() {
        hashArr = new Cell[hashLength];
        anyElement = new Cell;
    }

    ~HashTable() {
        delete[] hashArr;
    }

    void insertElement(string name, string article) {
        anyElement->name = name;
        anyElement->article = article;

        size_t hashValue = hashIndex(anyElement->article, hashLength);

        if (hashArr[hashValue].isEmpty()) {
            hashArr[hashValue] = *anyElement;
        }
        else {
            hashArr[hashValue].nextCell = anyElement;
        }
    }

    void showChain(Cell& cell) {
        cout << "  " << cell.article << "     " << cell.name << endl;
        
        if (cell.nextCell) {
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

string randomArticle() {
    string result, g;
    int rDigit;
    for (int i = 0; i < 6; i++) {
        if (i == 0) {
            rDigit = 1 + rand() % 9;
        }
        else {
            rDigit = 0 + rand() % 9;
        }
        
        g = to_string(rDigit);
        result += g;
    }
    
    return result;
}

int main() {
    srand(time(0));
    cout << "Testing fisting\n";
    
    HashTable ht;

    for (int i = 0; i < 20; i++) {
        ht.insertElement("Element" + to_string(i), randomArticle());
    }

    ht.showTable();
}