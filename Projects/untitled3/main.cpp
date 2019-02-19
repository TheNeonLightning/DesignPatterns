// Дано число N и N строк. Каждая строка содержащит команду добавления или удаления натуральных чисел,
// а также запрос на получение k-ой порядковой статистики. Команда добавления числа A задается положительным числом A,
// команда удаления числа A задается отрицательным числом “-A”. Запрос на получение k-ой порядковой статистики задается
// числом k. Требуемая скорость выполнения запроса - O(log n).
#include <iostream>

using std::cin;
using std::cout;
using std::max;

template <class T, class Cmp = std::less<>>
class AVLtree {
private:
    struct Node {
        T data;
        int height;
        int weight; // используется для нахождения k-ой порядковой статистики
        Node* left;
        Node* right;
    };
    Node* root;
    int size;
    Cmp cmp_;
    Node* Balance(Node* node);

    Node* LeftRotation(Node* P_node) {
        Node* Changed_node = P_node->right;
        P_node->right = Changed_node->left;
        Changed_node->left = P_node;
        Height(P_node); // полсе вращения высота и вес элементов могли поменяться, нужно вычислить новые
        Height(Changed_node);
        return Changed_node;
    }

    Node* RightRotation(Node* P_node) {
        Node* Changed_node = P_node->left;
        P_node->left = Changed_node->right;
        Changed_node->right = P_node;
        Height(P_node);
        Height(Changed_node);
        return Changed_node;
    }

    void Height(Node* current) { // функция для исправления высот и параметра weight элемента после вращений
        int left, right,  left_weight = 0, right_weight = 0;
        if (current->left == nullptr) {
            left = 0;
        } else {
            left = current->left->height;
            left_weight = current->left->weight;
        }
        if (current->right == nullptr) {
            right = 0;
        } else {
            right = current->right->height;
            right_weight = current->right->weight;
        }
        current->height = max(left, right) + 1;
        current->weight = left_weight + right_weight + 1;
    }

    Node* Insert(Node* current, T key) {
        if (current == nullptr) {
            current = new Node;
            current->data = key;
            current->left = nullptr;
            current->right = nullptr;
            current->weight = 0;
        }else if (cmp_(current->data,key)) {
            current->right = Insert(current->right, key);
        } else {
            current->left = Insert(current->left, key);
        }
        return Balance(current);
    }

    Node* Erase(Node* current, T key) {
        if (cmp_(current->data,key)) { // поиск удаляемого элемента
            current->right = Erase(current->right, key);
        } else if (cmp_(key,current->data)) {
            current->left = Erase(current->left, key);
        } else { // далее расмматривается удаление элемента
            Node *left = current->left;
            Node *right = current->right;
            delete current; // сохранив правое и левое поддерево удаляем нужный элемент
            if (right == nullptr) { // если правого поддерева нет, возвращаем левое, даже если оно также отсутствует (тогда возвращаем nullptr)
                return left;
            }
            Node *min = right; // если правое есть, находим в нём минимальный элемент
            while (min->left != nullptr) {
                min = min->left;
            }
            min->right = Remove_min(right); // к минимальному элементу справа присоединяем правое поддерево удалённого без самого минимального
            min->left = left;
            return Balance(min);
        }
        return Balance(current);
    }

    Node* Remove_min(Node* current) { // удаление минимального
        if (current->left == nullptr) {
            return current->right;
        }
        current->left = Remove_min(current->left);
        return Balance(current);
    }

    int OrderStatistics(int position, Node* current) {
        int left; // обозначение для веса левого поддерева
        if (current->left == nullptr) {
            left = 0; // если левое поддерево отсутствует, считаем его вес 0
        } else {
            left = current->left->weight;
        }
        if (position == left) // количество элементов слева равно позиции искомого, значит искомый найден
            return current->data;
        else if (position < left) { // количество элементов слева больше позиции искомого, значит искомый следует искать слева
            return OrderStatistics(position, current->left);
        } else {
            return OrderStatistics(position - (left + 1), current->right); // количество элементов меньше позиции искомого, значит искомый следует искать справа
        }
    }

    void Delete(Node* current) { // функция используемая в деструкторе
        if (current->left != nullptr) {
            Delete(current->left);
        }
        if (current->right != nullptr) {
            Delete(current->right);
        }
        delete current;
    }
public:
    AVLtree(const Cmp& compare = Cmp()) {
        root = nullptr;
        size = 0;
    }

    ~AVLtree() {
        Delete(root);
    }

    void Insert_(T key) {
        size = size + 1;
        root = Insert(root, key);
    }
    void Erase_(T key) {
        size = size - 1;
        root = Erase(root, key);
    }
    void OrderStatistics_(int position) {
        cout << OrderStatistics(position, root) << ' ';
    }

};

template<class T, class Cmp>
AVLtree::Node *AVLtree<T, Cmp>::Balance(AVLtree::Node *node) {
    int left, right, left_weight = 0, right_weight = 0;
    if (node->left == nullptr) {
        left = 0;
    } else {
        left = node->left->height;
        left_weight = node->left->weight;
    }
    if (node->right == nullptr) {
        right = 0;
    } else {
        right = node->right->height;
        right_weight = node->right->weight;
    }
    node->height = (max(left, right) + 1); // новая высота
    node->weight = left_weight + right_weight + 1; // новый вес (вес листа считаю единицей)
    if ((node->height >= 3) && (left - right == -2)) {
        if ((node->right->left != nullptr) && (node->right->right != nullptr) && (node->right->left->height > node->right->right->height)) {
            node->right = RightRotation(node->right);
        }
        node = LeftRotation(node);
    }
    if ((node->height >= 3) && (left - right == 2)) {
        if ((node->left->right != nullptr) && (node->left->left != nullptr) && (node->left->right->height > node->left->left->height)) {
            node->left = LeftRotation(node->left);
        }
        node = RightRotation(node);
    }
    return node;
}

int main() {
    int number, key, position;
    cin >> number;
    AVLtree<int> tree;
    for (int i = 0; i < number; i++) {
        cin >> key >> position;
        if (key < 0) {
            key = -key;
            tree.Erase_(key);
        } else {
            tree.Insert_(key);
        }
        tree.OrderStatistics_(position);
    }
}
// Время работы:
// Доп. память: