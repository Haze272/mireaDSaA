#include <iostream>
#include <string>
#include <list>
#include <typeinfo>

using namespace std;

// ячейка хеш-таблицы
struct Cell
{
    // "N/A" символизирует пустоту поля
    string key_ = "N/A";
    string name_ = "N/A";

    bool isEmpty() const {
        return key_ == "N/A" && name_ == "N/A";
    }

    void output() {
        cout << " " << key_ << endl;
        cout << " " << name_ << endl;
        cout << "-------------------------" << endl;
    }
};

// хеш-функция
int hashIndex(string key, int hashLen) 
{
    int sum = 0;
    for (int i = 0; i < key.length(); i++)
        sum += key[i];
    return sum % hashLen;
}

class HashTable // хеш-таблица
{
    int LEN_ = 8;    // размер хэш-таблицы
    Cell* H_;               // массив, что хранит элементы таблицы
public:
    HashTable() {
        H_ = new Cell[LEN_];
    }

    void add(Cell cell) {
        // rehash??
        if ((((double)realElemCount() + 1) / (double)LEN_) >= 0.75) {
            cout << "-----------REHASHING-----------" << endl;
            rehashTable();
        }

        int index = hashIndex(cell.key_, LEN_); // находим его индекс
        bool found = 0;
        while (found != true) {
            if (index == LEN_)
                index = 0;
            if (H_[index].isEmpty() == true) {
                H_[index] = cell; // даем значение элементу по найденному индексу
                return;
            }
            else {
                index++;
            }
        }
        
        
    }
    int find(string key) // найти индекс элемента с заданным ключом
    {
        int index = hashIndex(key, LEN_);         // находим его индекс

        for (int i = index; i < LEN_; i++)        // начинаем сдвигаться с указанного места, 
            if (H_[i].key_ == key)                // пока не найдем элемент с таким же ключом
                return i;
        return -1;                                // -1 значит, что мы не нашли такой элемент
    }

    string deleteElem(string key)
    {
        int index = find(key);                    // ищем такой элемент в таблице
        if (index == -1) return "error";          // если не нашли вернуть строку "ошибка"
        string name = H_[index].name_;            // вытаскиваем значение

        H_[index].key_ = H_[index].name_ = "N/A"; // "обнуляем" элемент

        return name;
    }

    int realElemCount() {
        int counter = 0;
        for (int i = 0; i < LEN_; i++)
            if (!H_[i].isEmpty()) {
                counter++;
            }
        return counter;
    }

    void output() {
        for (int i = 0; i < LEN_; i++)
            if (!H_[i].isEmpty()) {
                cout << " i: " << i << endl;
                H_[i].output();
            }
    }

    void rehashTable() {
        Cell* oldH_ = H_;
        H_ = new Cell[LEN_ * 2];

        for (int i = 0; i < LEN_; i++) {
            if (!oldH_[i].isEmpty()) {
                this->add(oldH_[i]);
            }
        }
        LEN_ *= 2;
    }

    int getLen() {
        return LEN_;
    }
};

int main()
{

    HashTable ht;

    ht.add({ "John", "79256709044" });
    ht.add({ "Pablo", "79999961265" });
    ht.add({ "Olbap", "79999675265" });
    ht.add({ "Marywanna", "7420420420" });
    ht.add({ "Pedro", "71488657899" });
    ht.output();
    cout << "The hashtable size is " << ht.getLen() << endl;

    ht.add({ "Lo Wan Hung", "72283221337" }); // This element gonna rehash the entire hashtable
    cout << "The new hashtable size is " << ht.getLen() << endl;
    ht.output();

    return 0;
}