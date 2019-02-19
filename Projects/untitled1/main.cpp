// Дано число N < 106 и последовательность пар целых чисел из [-231, 231] длиной N.
// Построить декартово дерево из N узлов, характеризующихся парами чисел (Xi, Yi).
// Каждая пара чисел (Xi, Yi) определяет ключ Xi и приоритет Yi в декартовом дереве.
// Добавление узла в декартово дерево выполняйте второй версией алгоритма, рассказанного на лекции:
// При добавлении узла (x, y) выполняйте спуск по ключу до узла P с меньшим приоритетом.
// Затем разбейте найденное поддерево по ключу x так, чтобы в первом поддереве все ключи меньше x,
// а во втором больше или равны x. Получившиеся два дерева сделайте дочерними для нового узла (x, y).
// Новый узел вставьте на место узла P. Построить также наивное дерево поиска по ключам Xi.
// Равные ключи добавляйте в правое поддерево. Вычислить количество узлов в самом широком слое
// декартового дерева и количество узлов в самом широком слое наивного дерева поиска.
// Вывести их разницу. Разница может быть отрицательна.
#include <vector>
#include <iostream>
#include <utility>

using std::cin;
using std::cout;
using std::vector;
using std::endl;
using std::pair;

template <class T, class U, class TCmp = std::less<T>, class UCmp = std::less<U>>
class Treap {
private:
    struct Node {
        T data;
        U priority;
        Node* left;
        Node* right;
    };
    TCmp cmp_T;
    UCmp cmp_U;
    Node* root;
    int size;
    pair <Node*, Node*>  Split(Node* current, const T &key);
    void MaxWidth(Node* node, int current_level, vector<int> &levels);
public:
    Treap(const TCmp& compare_T = TCmp(), const UCmp& compare_U = UCmp());
    ~Treap();
    void Insert(const T &key, const U &priority_value);
    int FindWidth();
};

template <class T, class Cmp = std::less<>>
class BinarySearchTree {
public:
    BinarySearchTree(const Cmp& compare = Cmp());
    ~BinarySearchTree();
    void Insert(const T &key);
    int FindWidth();
private:
    struct Node {
        T data;
        Node* left;
        Node* right;
    };
    Cmp cmp_;
    Node* root;
    int size;
    void MaxWidth(Node* node, int current_level, vector<int> &levels);
};

////////////////////////////////////////////////////////////////////////////////
int main(){
    int number, element_x, element_y;
    cin >> number;
    Treap<int, int> tree_1;
    BinarySearchTree<int> tree_2;
    for (int i = 0; i < number; ++i) {
        cin >> element_x >> element_y;
        tree_1.Insert(element_x, element_y);
        tree_2.Insert(element_x);
    }
    int size_1 = tree_1.FindWidth();
    int size_2 = tree_2.FindWidth();
    int answer = size_1 - size_2;
    cout << answer << ' ';
}
////////////////////////////////////////////////////////////////////////////////

////////////////////////* BinarySearchTree *////////////////////////////////////
template <class T, class Cmp>
BinarySearchTree<T, Cmp>::BinarySearchTree(const Cmp& compare):
        cmp_(compare),
        root(nullptr),
        size(0)
{}

template <class T, class Cmp>
BinarySearchTree<T, Cmp>::~BinarySearchTree(){
    vector<Node*> return_point;
    return_point.push_back(root); // в начале в массив помещаем root
    Node* current;
    while (!return_point.empty()) { // пока массив не пуст
        current = return_point.back();
        return_point.pop_back();
        if (current != nullptr) { // если current == nullptr ничего не делаем
            return_point.push_back(current->left); // иначе добавляем левого ребёнка
            return_point.push_back(current->right); // и правого
            delete current; // удаляем текущий
        }
    }
}

template <class T, class Cmp>
void BinarySearchTree<T, Cmp>::Insert(const T &key){
    Node* current = root;
    Node* previous = nullptr;
    while (current != nullptr) { // если пришли в конец, туда и положим новый элемент
        if (cmp_(key,current->data)) {
            previous = current;
            current = current->left;
        } else {
            previous = current;
            current = current->right;
        }
    }
    current = new Node;
    current->data = key;
    current->left = nullptr;
    current->right = nullptr;
    size = size + 1;
    if (previous == nullptr) { // случай, когда элемент помещён в корень
        root = current;
        return;
    }
    if (cmp_(key,previous->data)) { // создаем путь из предыдущего в новый
        previous->left = current;
    } else {
        previous->right = current;
    }
}

template <class T, class Cmp>
void BinarySearchTree<T, Cmp>::MaxWidth(Node* node, int current_level, vector<int> &levels) {
    levels[current_level] = levels[current_level] + 1;
    if (node->left != nullptr) {
        MaxWidth(node->left, current_level + 1, levels); // расмотрев текущий элемент, рекурсивно рассматриваем следующий, передавая далее значение уровня на один больше предыдущего
    }
    if (node->right != nullptr) {
        MaxWidth(node->right, current_level + 1, levels);
    }
}

template <class T, class Cmp>
int BinarySearchTree<T, Cmp>::FindWidth() {
    vector<int> levels(size); // создается массив, каждый элемент которого соответствует одному уровню дерева (уровней дерева не более общего числа элементов)
    int max = 0;
    MaxWidth(root, 0, levels);
    for (int i = 0; i < size; i++) { // поиск максимального значения ширины
        if (levels[i] > max) {
            max = levels[i];
        }
    }
    return max;
}

//////////////////////////* Treap *///////////////////////////////////////
template <class T, class U, class TCmp, class UCmp>
Treap<T, U, TCmp, UCmp>::Treap(const TCmp& compare_T, const UCmp& compare_U):
        cmp_T(compare_T),
        cmp_U(compare_U),
        root(nullptr),
        size(0)
{}

template <class T, class U, class TCmp, class UCmp>
Treap<T, U, TCmp, UCmp>::~Treap(){
    vector<Node*> return_point;
    return_point.push_back(root); // в начале в массив помещаем root
    Node* current;
    while (!return_point.empty()) { // пока массив не пуст
        current = return_point.back();
        return_point.pop_back();
        if (current != nullptr) { // если current == nullptr ничего не делаем
            return_point.push_back(current->left); // иначе добавляем левого ребёнка
            return_point.push_back(current->right); // и правого
            delete current; // удаляем текущий
        }
    }
}

template <class T, class U, class TCmp, class UCmp>
pair <class Treap<T, U, TCmp, UCmp>::Node*, class Treap<T, U, TCmp, UCmp>::Node*>
Treap<T, U, TCmp, UCmp>::Split(class Treap<T, U, TCmp, UCmp>::Node* current, const T &key) { // разрезание дерева по ключу key
    pair <Node*, Node* > split_result;
    if (current == nullptr) {
        return {nullptr, nullptr};
    } else if (cmp_T(current->data,key)) {
        split_result = Split(current->right, key);
        current->right = split_result.first;
        return {current, split_result.second};
    } else {
        split_result = Split(current->left, key);
        current->left = split_result.second;
        return {split_result.first, current};
    }
}

template <class T, class U, class TCmp, class UCmp>
void Treap<T, U, TCmp, UCmp>::Insert(const T &key,const U &priority_value) {
    size = size + 1;
    Node* current = root;
    Node* previous = nullptr;
    Node* inserted = new Node;
    inserted->data = key;
    inserted->priority = priority_value;
    inserted->right = nullptr;
    inserted->left = nullptr;
    if (root == nullptr) { // случай когда, в дерево кладётся первый элемент
        root = inserted;
        return;
    }
    while (!cmp_U(current->priority,priority_value)) { // спускаемся как по обычному дереву, пока не встретим элемент с меньшим приоритетом, чем у нового элемента
        if (cmp_T(key,current->data)) {
            previous = current;
            if (current->left == nullptr) {
                current->left = inserted;
                return;
            }
            current = current->left;
        } else {
            previous = current;
            if (current->right == nullptr) {
                current->right = inserted;
                return;
            }
            current = current->right;
        }
    }
    pair <Node*, Node*> split_result;
    split_result = Split(current, key);
    inserted->left = split_result.first; // первое поддерево, полученное в результате работы Split содержит элементы строго меньше key, следовательно оно будет левым поддеревом нового элемента
    inserted->right = split_result.second; // аналогично, второе поддерево, остальные элементы разрезанного поддерева (больще или равно)->правое поддерево нового элемента
    if (previous == nullptr) { // случай, когда помещённый элемент встаёт на место корня
        root = inserted;
        return;
    }
    if (cmp_T(key,previous->data)) { // если новый элемент не стал корнем, создаем путь из предыдущего в новый
        previous->left = inserted;
    } else {
        previous->right = inserted;
    }
}

template <class T, class U, class TCmp, class UCmp>
void Treap<T, U, TCmp, UCmp>::MaxWidth(Node* node, int current_level, vector<int> &levels) {
    levels[current_level] = levels[current_level] + 1;
    if (node->left != nullptr) {
        MaxWidth(node->left, current_level + 1, levels);
    }
    if (node->right != nullptr) {
        MaxWidth(node->right, current_level + 1, levels);
    }
}

template <class T, class U, class TCmp, class UCmp>
int Treap<T, U, TCmp, UCmp>::FindWidth() {
    vector<int> levels(size);
    int max = 0;
    MaxWidth(root, 0, levels);
    for (int i = 0; i < size; i++) {
        if (levels[i] > max) {
            max = levels[i];
        }
    }
    return max;
}
//Время работы Insert: O(log n);
//Время работы FindWidth: O(n);
//Доп. память: O(n);