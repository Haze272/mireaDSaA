#include <iostream>
#include <string>
#include <list>
#include <typeinfo>

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

size_t hasher1(const string id)
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
    void add(const hashObject& id)
    {
        // Добавление идентификатора в список, расположенный в таблице по
        // индексу, вычисленному хэш-функцией (с учётом смещения)
        m_hash_table[hasher(id) - min_hash_value].push_back(id.getArticle());
    }

    void deleteElem(const hashObject& id) {
        size_t aHex = (hasher(id) - min_hash_value);
        
        for (list<int>::iterator vlad = m_hash_table[aHex].begin(); vlad != m_hash_table[aHex].end(); ++vlad) {
            if (*vlad == id.getArticle()) {
                vlad = m_hash_table[aHex].erase(vlad);
                return;
            }
        }
    }

    int findElem(const string id) {
        size_t aHex = hasher1(id) - min_hash_value;

        for (list<int>::iterator vlad = m_hash_table[aHex].begin(); vlad != m_hash_table[aHex].end(); ++vlad) {
            if (*vlad == aHex) {
                return *vlad;
            }
        }
    }

    void showTable() {

        cout << "--------------------------" << endl;
        cout << "hash    values" << endl;
        for (int i = 0; i < hash_table_size; i++) {
            if (this->m_hash_table[i].empty() == false) {
                cout << i + min_hash_value << "     ";
                if (m_hash_table[i].size() != 1) {
                    for (auto iter = m_hash_table[i].begin(); iter != m_hash_table[i].end(); iter++) {
                        cout << *iter << " ";
                    }
                }
                else if (m_hash_table[i].size() == 1) {
                    cout << m_hash_table[i].front();
                }
                else {
                    cerr << "GOVNO!!!\n";
                }
                
                cout << endl;
            }
        }
    }

public:
    // Хэш-таблица - массив связных списков идентификаторов
    // TODO: сделать поле приватным.
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
    /*
    cout << ht.m_hash_table[194 - 113].front() << endl;
    cout << ht.m_hash_table[194 - 113].back() << endl;

    cout << endl;

    //cout << ht.m_hash_table[131].front() << endl;
    cout << typeid(ht.m_hash_table[194 - 113].back()).name() << endl;
    //ht.showTable();
    cout << ht.m_hash_table[0].empty() << endl;

    cout << endl;
    */
    ht.showTable();
    
    ht.deleteElem(hashObject("aa", 777777));

    ht.showTable();

    ht.deleteElem(hashObject("aa", 545466));

    ht.showTable();

    cout << endl;

    cout << ht.findElem("aa");
    
    return 0;
}