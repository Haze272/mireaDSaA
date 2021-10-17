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

static Cell* createCell(string name, string article) {
    Cell* cell = new Cell;
    cell->name = name;
    cell->article = article;
    cell->nextCell = nullptr;
    return cell;
}

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
    Cell* porn;
public:
    HashTable() {
        this->hashArr = new Cell[hashLength];
        this->porn = new Cell;
    }

    ~HashTable() {
        delete[] this->hashArr;
    }

    void insertElement(string name, string article) {
        if ((((double)this->realEntriesCount() + 1) / (double)this->hashLength) >= 0.75) {
            cout << "-----------REHASHING-----------" << endl;
            rehashTable();
        }

        size_t hashValue = hashIndex(article, this->hashLength);

        if (this->hashArr[hashValue].isEmpty()) {
            this->hashArr[hashValue] = *createCell(name, article);
        }
        else {
            porn = &hashArr[hashValue];
            for (; porn->nextCell != nullptr; porn = (porn)->nextCell);
            porn->nextCell = createCell(name, article);
        }
    }

    void showChain(Cell& cell) {
        cout << "  " << cell.article << "     " << cell.name << endl;
        
        if (cell.nextCell) {
            this->showChain(*cell.nextCell);
        }
    }

    void showTable() {
        for (int i = 0; i < this->hashLength; i++) {
            if (!this->hashArr[i].isEmpty()) {
                cout << "Hash: " << i << endl;
                cout << "  Article    Name" << endl;
                this->showChain(this->hashArr[i]);
            }
        }
    }

    int listCell(Cell& cell) {
        Cell* curNode = &cell;
        int len = 0;

        while (curNode) {
            len++;
            curNode = curNode->nextCell;
        }

        return len;
    }
    
    int realEntriesCount() {
        size_t count = 0;
        for (int j = 0; j < this->hashLength; j++) {
            if (!this->hashArr[j].isEmpty()) {
                count += this->listCell(this->hashArr[j]);
            }
        }
        
        return count;
    }

    void rehashTable() {
        Cell* oldHashArr = this->hashArr;
        this->hashArr = new Cell[this->hashLength * 2];
        size_t oldLEN_ = this->hashLength;
        this->hashLength *= 2;

        for (int i = 0; i < oldLEN_; i++) {
            if (!oldHashArr[i].isEmpty()) {
                porn = &oldHashArr[i];

                Cell *ptr = porn;
                while ( ptr != nullptr)
                {
                    this->insertElement(ptr->name, ptr->article);
                    ptr = ptr->nextCell;
                }
            }
        }
    }

    Cell* findElement(string art) {
        Cell* resultNode;
        size_t toFindHash = hashIndex(art, this->hashLength);
        porn = &this->hashArr[toFindHash];

        Cell *ptr = porn;
        while ( ptr != nullptr)
        {
            if(ptr->article == art) {
                resultNode = ptr;
            }
            ptr = ptr->nextCell;
        }

        return resultNode;
    }

    //void deleteElement() {}
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
    string toName, toArticle;
    
    for (int i = 0; i < 190; i++) {
        toName = "Element" + to_string(i + 1);
        if (ht.realEntriesCount() == ht.hashLength * 3 / 4 - 1) {
            cout << "\n\nThe size of hash-table is: " << ht.hashLength << "\n";
            ht.showTable();
        }
        ht.insertElement(toName, randomArticle());
    }

    ht.insertElement("ELEMENTO", "666666");

    cout << "\n\nThe size of hash-table is: " << ht.hashLength << "\n";
    ht.showTable();

    /* Test of find method
    cout << endl;
    Cell* wtf = ht.findElement("666666");
    cout << wtf->article << " " << wtf->name << endl;
    */
}