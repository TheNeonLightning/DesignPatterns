//Задача 1-3 (Post-Order)
// Дано число N ≤ 104 и последовательность целых чисел из [-231..231] длиной N.
// Требуется построить бинарное дерево, заданное наивным порядком вставки.
// Т.е., при добавлении очередного числа K в дерево с корнем root, если root→Key ≤ K,
// то узел K добавляется в правое поддерево root; иначе в левое поддерево root.
// Выведите элементы в порядке post-order (снизу вверх).
// Рекурсия запрещена.
#include <vector>
#include <iostream>

using std::cin;
using std::cout;
using std::vector;
using std::endl;

template <class T, class Cmp = std::less<>>
class BinarySearchTree {
public:
    BinarySearchTree(const Cmp& compare = Cmp());
    ~BinarySearchTree();
    void Insert(const T &key);
    void TraverseDFS(vector<T> &array); //Post-Order
private:
    struct Node {
        T data;
        Node* left;
        Node* right;
    };
    Cmp cmp_;
    Node* root;
    int size;
};

////////////////////////////////////////////////////////////////////////////////
int main(){
    int number, element;
    cin >> number;
    vector<int> array; //для вывода ответа
    BinarySearchTree<int> tree;
    for (int i = 0; i < number; ++i) {
        cin >> element;
        tree.Insert(element);
    }
    tree.TraverseDFS(array);
    for (int i = 0; i < number; i++) {
        element = array.back();
        array.pop_back();
        cout << element << ' ';
    }
}
////////////////////////////////////////////////////////////////////////////////


template <class T, class Cmp>
BinarySearchTree<T, Cmp>::BinarySearchTree(const Cmp& compare): // конструктор, получает на вход первый элемент и строит дерево с уже имеющимся корнем
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
    if (previous == nullptr) {
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
void BinarySearchTree<T, Cmp>::TraverseDFS(vector<T> &array) {
    vector<Node*> turn_point; //для возвращения в элемент, с нерассмотренным левым поддеревом
    Node* current = root;
    int visited = 0, marker = 0;
    T element;
    while (visited < size) {
        if (marker == 0) { // marker == 0 означает, что элемент рассматривается впервые
            array.push_back(current->data);
            visited = visited + 1;
        }
        if ((current->right != nullptr) && (marker == 0)) { // marker != 0 означает, что элемент уже был рассмотрен, и нужно проверять левое поддерево
            turn_point.push_back(current);
            current = current->right;
        } else {
            if (current->left != nullptr) {
                current = current->left;
                marker = 0;
            } else {
                current = turn_point.back(); //если нет ни левого, ни правого поддерева возвращаемся, к точке поворота и рассматриваем уже наличие левого поддерева (marker ставим 1)
                turn_point.pop_back();
                marker = 1;
            }
        }
    }
}
//Время работы: O(n^2);
//Доп. память: O(n);