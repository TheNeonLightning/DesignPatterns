// Реализуйте структуру данных типа “множество строк” на основе динамической хеш-таблицы с открытой адресацией.
// Хранимые строки непустые и состоят из строчных латинских букв. Хеш-функция строки должна быть реализована с
// помощью вычисления значения многочлена методом Горнера. Начальный размер таблицы должен быть равным 8-ми.
// Перехеширование выполняйте при добавлении элементов в случае, когда коэффициент заполнения таблицы достигает 3/4.
// Структура данных должна поддерживать операции добавления строки в множество, удаления строки из множества и проверки
// принадлежности данной строки множеству.
// 1_1. Для разрешения коллизий используйте квадратичное пробирование.
// ФОРМАТ ВВОДА:
// Каждая строка входных данных задает одну операцию над множеством. Запись операции состоит из типа операции и
// следующей за ним через пробел строки, над которой проводится операция. Тип операции – один из трех символов:
// + означает добавление данной строки в множество; - означает удаление строки из множества; ? означает проверку
// принадлежности данной строки множеству. При добавлении элемента в множество НЕ ГАРАНТИРУЕТСЯ, что он отсутствует в
// этом множестве. При удалении элемента из множества НЕ ГАРАНТИРУЕТСЯ, что он присутствует в этом множестве.
// ФОРМАТ ВЫВОДА:
// Программа должна вывести для каждой операции одну из двух строк OK или FAIL, в зависимости от того,
// встречается ли данное слово в нашем множестве.

#include <iostream>
#include <vector>

using std::vector;
using std::cin;
using std::cout;
using std::string;
using std::endl;

class HashTable {

private:

    size_t size;
    size_t capacity;
    const double max_load_factor;

    struct ElemType {
        string value;
        bool nil = true;
        bool deleted = false;
    };

    vector<ElemType> table;

    struct HashFunc {
    public:
        void SetTableSize(size_t capacity);

        size_t operator() (const string &value, int sample_number) const;

        HashFunc(size_t capacity);

    private:
        size_t table_capacity;
        int multiplier;
        double first_coefficient;
        double second_coefficient;
    };

    HashFunc hash_function;

    inline bool CheckLoadFactor() const;

    void Rehash();

    size_t Find(const string &value) const;

public:

    bool Insert(const string &value);

    bool Search(const string &value) const;

    bool Erase(const string &value);

    HashTable();
};

////////////////////////////////////////////////////////////////////////////////
int main() {
    HashTable table;
    while (true) {
        char operation;
        string line;
        bool result;
        int index;
        cin >> operation;
        if (cin.fail()) {
            break;
        }
        cin >> line;
        if (operation == '+') {
            result = table.Insert(line);
        } else if (operation == '-') {
            result = table.Erase(line);
        } else if (operation == '?') {
            result = table.Search(line);
        }
        if (result) {
            cout << "OK" << endl;
        } else {
            cout << "FAIL" << endl;
        }
    }
}
////////////////////////////////////////////////////////////////////////////////

///////////////////////////////HashFunc/////////////////////////////////////////

size_t HashTable::HashFunc::operator() (const string &value, int sample_number) const {
    size_t index = 0, i = 0;
    while (i != value.size()) {
        index = (index * multiplier + value[i]) % table_capacity;
        i++;
    }
    index = index + first_coefficient * sample_number + second_coefficient * sample_number * sample_number;
    index = index % table_capacity;
    return index;
}


HashTable::HashFunc::HashFunc(size_t capacity):
table_capacity(capacity),
multiplier(257),
first_coefficient(0.5),
second_coefficient(0.5)
{}

void HashTable::HashFunc::SetTableSize(size_t capacity) {
    table_capacity = capacity;
}

///////////////////////////////HashTable////////////////////////////////////////

inline bool HashTable::CheckLoadFactor() const {
    double current_load_factor = static_cast<double>(size) / capacity;
    return current_load_factor < max_load_factor;
}

void HashTable::Rehash() {
    size_t local_size = capacity;
    capacity = capacity * 2; // увеличиваем значение размера таблицы
    hash_function.SetTableSize(capacity); // увеличиваем значение размера таблицы в HashFunc
    vector<ElemType> new_table(capacity);
    for (size_t i = 0; i < local_size; i++) {
        if (!table[i].nil) {
            if (table[i].deleted) {
                size = size - 1;
            } else {
                size_t index = hash_function(table[i].value, 0);
                int number = 1;
                while (!new_table[index].nil) {
                    index = hash_function(table[i].value, number);
                    number = number + 1;
                }
                new_table[index] = table[i];
            }
        }
    }
    table = std::move(new_table);
}

bool HashTable::Insert(const string &value) {
    if (!CheckLoadFactor()) {
        Rehash();
    }
    size_t index = Find(value);
    if ((!table[index].nil) && (!table[index].deleted)) { // если find вернул не deleted и не nil, то значит искомый элемент найден и вставка не производится
        return false;
    }
    if (!table[index].deleted) { // если кладём элемент на место удалённого ранее, то не увеличиваем размер
        size = size + 1;
    }
    table[index] = {value, false, false};
    return true;
}

bool HashTable::Search(const string &value) const{
    size_t index = Find(value);
    if ((!table[index].nil) && (!table[index].deleted)) { // если find вернул не deleted и не nil, то значит искомый элемент найден
        return true;
    } else {
        return false;
    }
}

size_t HashTable::Find(const string &value) const {
    size_t index = hash_function(value,0), hash_deleted;
    int i = 1;
    bool find_deleted = false; // обнаружен ли удалённый элемент
    while (!table[index].nil) {
        if ((table[index].deleted) && (!find_deleted)) { // если нашли, запоминаем первый обнаруженный удалённый элемент (index)
            hash_deleted = index;
            find_deleted = true;
        }
        if ((table[index].value == value) && (!table[index].deleted)) {
                return index;

        }
        index = hash_function(value, i);
        i = i + 1;
    }
    if (find_deleted) { // если искомый элемент не найден, возвращаем либо первый встретившийся удалённый, либо nil
        return hash_deleted;
    } else {
        return index;
    }
}

bool HashTable::Erase(const string &value) {
    size_t index = Find(value);
    if ((table[index].nil) || (table[index].deleted)) { // если find вернул deleted или nil, то значит удаляемый элемент не найден
        return false;
    }
    table[index].deleted = true;
    return true;
}

HashTable::HashTable():
        size(0),
        capacity(8),
        max_load_factor(0.75),
        table(vector<ElemType>(capacity)),
        hash_function(capacity)
{}
// Время работы выполнения операции: O(1); (O(1/(1-max_load_factor))
// Доп. память на выполнение операции: O(1);