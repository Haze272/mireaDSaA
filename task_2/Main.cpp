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

    // Метод структуры определяющий, пустая ли ячейка
    bool isEmpty() const {
        return key_ == "N/A" && name_ == "N/A";
    }

    // Метод вывода текущей ячейки
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

// Класс хэш-таблицы
class HashTable             
{
    int LEN_ = 8; // размер хэш-таблицы
    Cell* H_;     // массив, что хранит элементы таблицы
public:
    // Конструктор - в нем происходит инициализация таблицы
    HashTable() {
        H_ = new Cell[LEN_];
    }

    // Деструктор освободит память хэш-таблицы
    ~HashTable() {
        delete[] H_;
    }

    void add(Cell cell) {
        if ((((double)realElemCount() + 1) / (double)LEN_) >= 0.75) {   // Условие проверяет, будет ли учтён коеффицент заполненности при добавлении новой записи,
                                                                        //  если нет - произойдёт рехэширование
            cout << "-----------REHASHING-----------" << endl;          // Вывод предупреждения о рехэшировании
            rehashTable();                                              // Вызов метода рехэширования
        }

        int index = hashIndex(cell.key_, LEN_);                         // Получаем хэш записи
        bool found = 0;
        while (found != true) {
            if (index == LEN_)                                          // В случае, если коллизия произошла на последнем элементе хэш-таблицы - поиск свободной ячейки начнется с начала таблицы
                index = 0;
            if (H_[index].isEmpty() == true) {                          // Условие проверяет, занято ли место с этим значением хэша. Если занято - индекс инкрментируется
                H_[index] = cell;                                       // даем значение элементу по найденному индексу

                writeToFile(cell);                                      // добавление этой записи в файл
                return;
            }
            else {
                index++;
            }
        }
    }

    // Метод поиска индекса элемента с заданным ключом
    int find(string key) 
    {
        int index = hashIndex(key, LEN_);         // находим его индекс

        for (int i = index; i < LEN_; i++)        // начинаем сдвигаться с указанного места, 
            if (H_[i].key_ == key)                // пока не найдем элемент с таким же ключом
                return i;
        return -1;                                // -1 значит, что мы не нашли такой элемент
    }

    Cell* find1(string key)
    {
        int index = hashIndex(key, LEN_);         // находим его индекс

        for (int i = index; i < LEN_; i++)        // начинаем сдвигаться с указанного места, 
            if (H_[i].key_ == key)                // пока не найдем элемент с таким же ключом
                return &H_[i];
    }

    // Удаление записи из таблицы и файла
    string deleteElem(string key) {
        int index = find(key);                    // ищем такой элемент в таблице
        if (index == -1) return "error";          // если не нашли вернуть строку "ошибка"
        string name = H_[index].name_;            // вытаскиваем значение

        H_[index].key_ = H_[index].name_ = "N/A"; // "обнуляем" элемент

        return name;
    }

    // Вспомогательный метод: позволяет узнать, сколько записей присутствует в хэш-таблцице
    int realElemCount() {
        int counter = 0;
        for (int i = 0; i < LEN_; i++)
            if (!H_[i].isEmpty()) {
                counter++;
            }
        return counter;
    }

    // Метод вывода хэш-таблицы в консоль (пустые ячейки хэш-таблицы не учитываются)
    void output() {
        cout << "\n-------------------------\n--------Hashtable--------\n-------------------------\n\n";

        for (int i = 0; i < LEN_; i++)            // Цикл перебирает все элементы хэш-таблицы и проверяет каждый на существование там записи
            if (!H_[i].isEmpty()) {               // В случае, если по текущему индексу запись существует - она будет выведена в консоль
                cout << " i: " << i << endl;
                H_[i].output();
            }
        cout << endl << endl;
    }

    // Метод рехэширования
    void rehashTable() {
        Cell* oldH_ = H_;                         // Создаётся копия предыдущей хэш-таблицы
        H_ = new Cell[LEN_ * 2];                  // Полю-таблице присваивается новый массив с длинной, в два раза превышающей старую длину
        size_t oldLEN_ = LEN_;                    // Создаётся копия предущего размера хэш-таблицы (для перебора старых элементов)
        LEN_ *= 2;                                // Поле с значением длины хэш-таблицы умножается в два раза

        for (int i = 0; i < oldLEN_; i++) {       // Перебор старых элементов таблицы и добавление их в новую хэш-таблицу
            if (!oldH_[i].isEmpty()) {
                add(oldH_[i]);
            }
        }
        updateFile();                             // После рехэширования следует обновить файл с записями
    }

    // Метод для отладки - позволяет узнать текущий размер таблицы (нужен для проверки метода рехэширования)
    int getLen() {
        return LEN_;
    }

    // Метод вствки записи в бинарный файл
    void writeToFile(Cell& toCell) {
        ofstream ffout;

        ffout.open("hashTable.dat", ios::binary | ios::out);

        if (!ffout)
        {
            cout << "file not open";
            return;
        }
        
        ffout.write((char*)&toCell, sizeof(toCell));
        ffout.close();
    }

    // Метод, обновляющий файл с записями. Переносит все записи текущей хэш-таблицы в файл, удаляя предущее содержимое
    void updateFile() {
        ofstream ffout;

        ffout.open("hashTable.dat", ios::binary | ios::out | ios::trunc);

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
    HashTable ht;  // Создаём объект хэш-таблицы

    //-----------------------Тест хэш-таблицы-----------------------//

    ht.add({ "05.06.2002", "Margarita" });
    ht.add({ "27.02.2002", "Stepan" });    // Эта запись является коллизией с предыдущей записью
    ht.add({ "20.08.2002", "Max" });
    ht.add({ "14.02.2000", "Cupid" });
    ht.add({ "30.12.1999", "Gleb" });
    ht.output(); // Вывод всех элементов хэш-таблицы

    ht.add({ "09.04.2014", "Victoria" }); // Изначальный размер таблицы был 8, следовательно при добавлении этого элемента
                                          // коеффицент заполнения станет больше 0.75 и произойдёт рехеширование
    ht.output(); // Вывод всех элементов хэш-таблицы

    ht.deleteElem("30.12.1999"); // Удалим запись с ключом 30.12.1999
    ht.deleteElem("20.08.2002");
    ht.deleteElem("05.06.2002");
    ht.output(); // Снова выведем всю таблицу чтобы удостовериться, что запись была удалёна

    //-----------------------Тест записи/чтения-----------------------//

    HashTable ht2;

    Cell cell;
    ht2.readTheFile(cell); // Читаем записи из файла, который был заполнен предыдущей хэш-таблицей и заполням ими новую хэш-таблицу
    ht.output();


    

    cin.get();

    return 0;
}