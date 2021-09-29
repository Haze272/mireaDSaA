#include <iostream>
#include <string>
#include <list>
#include <typeinfo>
#include <fstream>

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

    void writeToFile() {
        ofstream ffout;

        ffout.open("hashTable.dat", ios::binary | ios::out);

        if (!ffout)
        {
            cout << "file not open";
            return;
        }

        for (int i = 0; i < LEN_; i++) {
            if (!H_[i].isEmpty()) {
                ffout.write((char*)&H_[i], sizeof(Cell));
                ffout.clear();
            }
        }
        ffout.close();
    }

    // Метод, читающий записи из файла и вставляющий их в хэш-таблицу
    void readTheFile(Cell& Y)
    {
        
        fstream in("hashTable.dat", ios::binary | ios::in); // Открываем поток ввода
        
        in.read((char*)&Y, sizeof Y); //Считываем информацию в объект Y
        while (!in.eof())
        {
            add(Y);
            in.read((char*)&Y, sizeof Y);
        }
        in.close(); //Закрываем открытый файл
        
    }
};

int main()
{
    HashTable ht;
    system("CLS"); //Очистка экрана
    Cell Yx;
    ht.readTheFile(Yx);
    ht.output();

    cin.get();

    return 0;
}