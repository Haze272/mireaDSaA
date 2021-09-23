#include <iostream>
#include <string>
#include <list>

using namespace std;

class hashObject
{
public:
    hashObject(const string& name, const size_t article)
        :o_name(name), o_article(article) {}

    string getName() const { // const после скобок указывает на то, что функция не модифицирует состояние объекта для которого она вызывается.
        return o_name;
    }

    int getArticle() const {
        return o_article;
    }

private:
    string o_name;
    int o_article;
};

size_t hasher(const hashObject& id)
{
    // Если имя переменной составляет один символ - возвращается его код,
    // умноженный на два
    if (id.getName().length() == 1)
        return 2 * size_t(id.getName()[0]);

    // Иначе возвращается сумма кодов первых двух символов
    return size_t(id.getName()[0]) + size_t(id.getName()[1]);
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
    void add(const hashObject& id)
    {
        // Добавление идентификатора в список, расположенный в таблице по
        // индексу, вычисленному хэш-функцией (с учётом смещения)
        m_hash_table[hasher(id) - min_hash_value].push_back(id.getArticle());
    }

    void showTable() {
        list<hashObject>::iterator it

        cout << "--------------------------" << endl;
        cout << "key    values" << endl;
        for (int i = min_hash_value; i <= max_hash_value; i++) {
            if (this->m_hash_table[i].empty() == false) {
                // todo: вывод всех элементов

            }
        }
    }

public:
    // Хэш-таблица - массив связных списков идентификаторов
    list<int> m_hash_table[hash_table_size];
};

int main()
{
    
    HashTable ht;

    
    ht.add(hashObject("aa", 545466));
    ht.add(hashObject("aa", 777777));
    ht.add(hashObject("if", 898889));
    ht.add(hashObject("fi", 777450));

    // cout << hasher(hashObject("aa", 545466)) << endl; // 194
                                                         // 194 - 113 = искомый индекс

    cout << ht.m_hash_table[194 - 113].front() << endl;
    cout << ht.m_hash_table[194 - 113].back() << endl;

    cout << endl;
    ht.showTable();

    return 0;
}