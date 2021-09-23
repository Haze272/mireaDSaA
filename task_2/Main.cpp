#include <iostream>
#include <string>
#include <list>

using namespace std;

// Необходимо для поиска переменной по имени
bool operator==(string left, const string right)
{
    return left == right;
}

size_t hasher(string id)
{
    // Если имя переменной составляет один символ - возвращается его код,
    // умноженный на два
    if (id.length() == 1)
        return 2 * size_t(id[0]);

    // Иначе возвращается сумма кодов первых двух символов
    return size_t(id[0]) + size_t(id[1]);
}

// Класс "Хэш-таблица", основанная на методе цепочек
// Метод цепочек заключается в следующем: таблица представляет собой массив
// связных списков фиксированного размера. Вычисленный хэш-функцией хэш является
// индексом в этом массиве списков. Известно, что список по этому индексу будет
// содержать все идентификаторы, для которых функция вернула одинаовый хэш.
// Осталось только найти идентификатор в данном списке и возвратить ссылку на
// него.
class HashTable
{
public:
    static const size_t min_hash_value = int('A') + int('0');
    static const size_t max_hash_value = int('z') + int('z');
    static const size_t hash_table_size = max_hash_value - min_hash_value;

public:
    void add(const string id)
    {
        // Добавление идентификатора в список, расположенный в таблице по
        // индексу, вычисленному хэш-функцией (с учётом смещения)
        m_hash_table[hasher(id) - min_hash_value].push_back(id);
    }

    
    string get(const string id_name)
    {
        // Сохраняется ссылка на список, в котором потенциально будет
        // расположен идентификатор (для простоты)
        list<string>& line = m_hash_table[hasher(id_name) - min_hash_value];

        // Поиск идентификаторы в списке по имени
        list<string>::iterator it = find(line.begin(), line.end(), id_name);

        // Если идентификатор найден - возвращаем ссылку на него
        return *it;
    }

private:
    // Хэш-таблица - массив связных списков идентификаторов
    list<string> m_hash_table[hash_table_size];
};

int main()
{
    
    HashTable ht;

    
    ht.add("a");
    ht.add("aa");
    ht.add("if");
    ht.add("fi");

    cout << hasher("a") << endl;
    cout << hasher("aa") << endl;
    cout << hasher("if") << endl;
    cout << hasher("fi") << endl;

    cout << endl;

    cout << int('a') << endl;
    cout << int('A') << endl;
    cout << int('0') << endl;
    cout << int('z') << endl;

    cout << endl;

    cout << ht.get("a") << endl;
    cout << ht.get("aa") << endl;
    cout << ht.get("if") << endl;
    cout << ht.get("fi") << endl;

    return 0;
}