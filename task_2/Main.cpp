#include <iostream>
#include <string>
#include <list>
#include <typeinfo>

using namespace std;

struct Cell // ячейка хеш-таблицы
{
    // "N/A" символизирует пустоту поля 
    string key_ = "N/A";
    string phoneNo_ = "N/A";

    bool isEmpty() const // ячейка пустая?
    {
        return key_ == "N/A" && phoneNo_ == "N/A";
    }
    void output() // вывести поля ячейки
    {
        cout << " " << key_ << endl;
        cout << " " << phoneNo_ << endl;
        cout << "-------------------------" << endl;
    }
};

int hashIndex(string key, int hashLen) // хеш-функция
{ // алгоритм взял из гарвардского видео-курса
    int sum = 0;
    for (int i = 0; i < key.length(); i++)
        sum += key[i];
    return sum % hashLen;
}

struct HashTable // хеш-таблица
{
    const int LEN_ = 99; // максимальный размер
    Cell* H_; // массив, что хранит элементы таблицы

    HashTable() // конструктор
    {
        H_ = new Cell[LEN_];
    }
    ~HashTable() // деструктор
    {
        delete[] H_;
    }
    void add(Cell cell) // добавить новый элемент
    {
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
        int index = hashIndex(key, LEN_); // находим его индекс

        for (int i = index; i < LEN_; i++) // начинаем сдвигаться с указанного места, 
            if (H_[i].key_ == key) // пока не найдем элемент с таким же ключом
                return i;
        return -1; // -1 значит, что мы не нашли такой элемент
    }
    string ext(string key) // извлечь элемент по заданному ключу (по сути, удалить его)
    {
        int index = find(key); // ищем такой элемент в таблице
        if (index == -1) return "error"; // если не нашли вернуть строку "ошибка"
        string phoneNo = H_[index].phoneNo_; // вытаскиваем значение

        H_[index].key_ = H_[index].phoneNo_ = "N/A"; // "обнуляем" элемент

        return phoneNo;
    }
    void output() // вывести не пустые элементы
    {
        for (int i = 0; i < LEN_; i++)
            if (!H_[i].isEmpty()) // если элемент не пустой
            {
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
    return 0;
}