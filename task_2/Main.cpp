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
    const int LEN_ = 88;    // размер хэш-таблицы
    Cell* H_;               // массив, что хранит элементы таблицы
public:
    HashTable() {
        H_ = new Cell[LEN_];
    }

    void add(Cell cell) {
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

    void output() {
        for (int i = 0; i < LEN_; i++)
            if (!H_[i].isEmpty()) {
                cout << " i: " << i << endl;
                H_[i].output();
            }
    }
};

int main()
{

    HashTable ht;

    ht.add({ "John", "79256709044" });
    ht.add({ "Pablo", "79999961265" });
    ht.add({ "nhoJ", "86496932" });
    ht.add({ "Muhhamad", "796796798" });

    ht.output();

    cout << "\n\n\n\n\n";

    ht.deleteElem("John");
    ht.output();
    return 0;
}