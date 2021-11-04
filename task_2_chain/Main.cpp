#include <iostream>
#include <string>
#include <fstream>
#include <chrono>

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
    Cell* elementius;
public:
    HashTable() {
        this->hashArr = new Cell[hashLength];
        this->elementius = new Cell;
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
            updateFile();
        }
        else {
            elementius = &hashArr[hashValue];
            for (; elementius->nextCell != nullptr; elementius = (elementius)->nextCell);
            elementius->nextCell = createCell(name, article);
            updateFile();
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
                elementius = &oldHashArr[i];

                Cell *ptr = elementius;
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
        elementius = &this->hashArr[toFindHash];

        Cell *ptr = elementius;
        while ( ptr != nullptr) {
            if(ptr->article == art) {
                resultNode = ptr;
            }
            ptr = ptr->nextCell;
        }

        return resultNode;
    }

    void deleteElement(string toDelete) {
        size_t toFindHash = hashIndex(toDelete, this->hashLength);
        elementius = &this->hashArr[toFindHash];

        if (elementius->article == toDelete) {
            if (elementius->nextCell) {
                this->hashArr[toFindHash] = *(elementius->nextCell);
            } else {
                elementius->article = "N/A";
                elementius->name = "N/A";
            }
        } else {
            Cell *ptr = elementius;
            while (ptr->nextCell->article != toDelete) {
                ptr = ptr->nextCell;
            }

            ptr->nextCell = findElement(toDelete)->nextCell;
        }
        updateFile();
    }

    void updateFile() {
        ofstream ffout;

        ffout.open("hashTable.txt", ios::binary | ios::trunc);

        if (!ffout)
        {
            cout << "file not open";
            return;
        }

        for (int i = 0; i < this->hashLength; i++) {
            if (!hashArr[i].isEmpty()) {
                ffout.write((char*)&hashArr[i], sizeof(Cell));

                Cell *ptr = &hashArr[i];
                ptr = ptr->nextCell;
                while (ptr != nullptr) {
                    ffout.write((char*)ptr, sizeof(Cell));
                    ptr = ptr->nextCell;
                }
            }
        }
        ffout.close();
    }

    void readTheFile(Cell& Y) {
        fstream in("hashTable.txt", ios::binary | ios::in);

        in.read((char*)&Y, sizeof(Y));
        while (!in.eof())
        {
            insertElement(Y.name, Y.article);
            in.read((char*)&Y, sizeof(Y));
        }
        in.close();
    }

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

    void spawnRandomElement(int count) {
        string toName;

        for (int i = 0; i < count; i++) {
            toName = "Element" + to_string(i + 1);
            /*
            if (this->realEntriesCount() == this->hashLength * 3 / 4 - 1) {
                cout << "\n\nThe size of hash-table is: " << this->hashLength << "\n";
                this->showTable();
            }
            */
            this->insertElement(toName, randomArticle());
        }
    }
};



int main() {
    srand(time(0));

    /*Test for insert, show, delete and write/read file methods*/
    HashTable ht;
    // Element1, Element3 and Element5
    ht.insertElement("Element1", "111111");
    ht.insertElement("Element2", "333333");
    ht.insertElement("Element3", "555555");
    ht.insertElement("Element4", "777777");
    ht.insertElement("Element5", "999999");
    ht.showTable();
    cout << "-----------------\n";

    auto tDelStart = chrono::high_resolution_clock::now();

    ht.deleteElement("999999");

    auto tDelEnd = chrono::high_resolution_clock::now();
    auto durationDelete = chrono::duration_cast<std::chrono::microseconds>( tDelEnd - tDelStart ).count();

    cout << "The delete method was executed in " << durationDelete << endl;

    HashTable ht1;
    Cell celly;
    ht1.readTheFile(celly);
    ht1.showTable();

    /*Test for rehashing and many notes*/
    cout << "\n\n-----------HashTable 3-----------\n\n\n";
    HashTable ht2;
    ht2.spawnRandomElement(22);

    auto tStart = chrono::high_resolution_clock::now();

    ht2.insertElement("ElementToFind", "777777");

    auto tEnd = chrono::high_resolution_clock::now();
    auto durationIns = chrono::duration_cast<std::chrono::microseconds>( tEnd - tStart ).count();

    cout << "The Insert method was executed in " << durationIns << endl;

    ht2.showTable();

    cout << "--------------------\n";

    auto t1 = chrono::high_resolution_clock::now();
    Cell* toFind = ht2.findElement("777777");
    auto t2 = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();

    cout << "Found " << toFind->article << " " << toFind->name << endl;
    cout << "The find method was executed in " << duration << endl;



    cout << "\n\n-----------HashTable 4-----------\n\n\n";
    HashTable ht3;
    ht3.readTheFile(celly);
    ht3.showTable();

}