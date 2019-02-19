// Дано невзвешенное дерево. Расстоянием между двумя вершинами будем называть количество ребер в пути, соединяющем эти две вершины. Для каждой вершины определите расстояние до самой удаленной от нее вершины.
// Формат ввода:
// В первой строке записано количество вершин n ≤ 10000. Затем следует n - 1 строка, описывающая ребра дерева.
// Каждое ребро - это два различных целых числа - индексы вершин в диапазоне [0, n-1].
// Индекс корня – 0. В каждом ребре родительской вершиной является та, чей номер меньше.
// Формат вывода:
// Выход должен содержать n строк. В i-ой строке выводится расстояние от i-ой вершины до самой удаленной от нее.
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;
using std::pair;
using std::max;
using std::endl;

class Tree {

private:
    int size;
    int index_first; // самый удалённый от корня элемент
    int index_second; // самый удалённый от index_first элемент

    struct Node {
        int parent_index;
        int distance_first; // расстояние от index_first
        int distance_second; // расстояние от index_second
        vector<int> SubsequentElements;
    };
    vector<Node> Elements;
    Node root;

    void DistanceDownSearch_First(int current_index, int distance, pair<int, int> &result);

    void DistanceDownSearch_Second(int current_index, int distance);

    void DistanceUpSearch_First(int current_index, int distance, pair<int, int> &result, int previous);

    void DistanceUpSearch_Second(int current_index, int distance, int previous);

public:

    Tree();

    void Insert(int parent_index, int index);

    void MostRemoteSearch(); // поиск самого удалённого от корня элемента (далее index_first)

    void Index_First_Pass(); // одновременно проход по дереву от index_first и поиск самого удалённого от index_first (далле index_second)

    void Index_Second_Pass(vector<int> &result); // проход по дереву от index_second, поиск непосредственного результата для каждого элемента
};
////////////////////////////////////////////////////////////////////////////////
int main() {
    int number, parent_index, index;
    vector<int> result;
    cin >> number;
    Tree tree;
    for (int i = 0; i < (number - 1); i++) {
        cin >> parent_index;
        cin >> index;
        tree.Insert(parent_index, index);
    }
    tree.MostRemoteSearch();
    tree.Index_First_Pass();
    tree.Index_Second_Pass(result);
    for (int i = 0; i < result.size(); i++) {
        cout << result[i] << endl;
    }
}
////////////////////////////////////////////////////////////////////////////////
Tree::Tree():
        size(0),
        index_first(0),
        index_second(0)
{
    Elements.push_back(root);
}

void Tree::Insert(int parent_index, int index) {
    Node node;
    node.parent_index = parent_index;
    Elements.push_back(node);
    Elements[parent_index].SubsequentElements.push_back(index);
    size++;
}

void Tree::MostRemoteSearch() {
    pair<int, int> result; // пара, в которой во время прохода по дереву будет храниться текущая наибольшая дистанция и соответствующий индекс
    DistanceDownSearch_First(0, 0, result); // начинаем как с шага в поддерево (в корень), соответственно наверх за время прохода подъёма не будет
    index_first = result.second; // после прохода, в созданной паре храниться нужный индекс
}

void Tree::Index_First_Pass() {
    pair<int, int> result;
    DistanceUpSearch_First(index_first, 0, result, index_first); // начинаем с шага наверх от index_first
    index_second = result.second;
}

void Tree::Index_Second_Pass(vector<int> &result) { // получаем массив, в который запишем найденный расстояния
    DistanceUpSearch_Second(index_second, 0, index_second); // начинаем с шага наверх от index_second
    for (int i = 0; i < Elements.size(); i++) {
        result.push_back(max(Elements[i].distance_first, Elements[i].distance_second)); // в соответствующую позицию массива кладём большее из двух расстояний (от элемента до index_first и от элемента до index_second)
    }
}

/*void Tree::DistanceDownSearch_First(int current_index, int distance, pair<int, int> &result) { // шаг в поддерево одновременно с поиском наиболее удалённого от index_first
    Elements[current_index].distance_first = distance; // выставляем текущую дистанцию в просматриваемом элементе
    if ((Elements[current_index].SubsequentElements.empty()) && (result.first <= distance)) { // если пришли в лист проверем дистанцию в паре, и меняем пару если текущая дистанция больше сохранённой
        result.first = distance;
        result.second = current_index;
    }
    for (int i = 0; i < Elements[current_index].SubsequentElements.size(); i++) {
        DistanceDownSearch_First(Elements[current_index].SubsequentElements[i], distance + 1, result); // после шага в поддерево возможен только шаг в поддерево
    }
}*/

void Tree::DistanceDownSearch_First(int current_index, int distance, pair<int, int> &result) {
    vector<int> visit_list;
    vector<int> distances;
    visit_list.push_back(current_index);
    distances.push_back(distance);
    while (!visit_list.empty()) {
        current_index = visit_list.back();
        visit_list.pop_back();
        distance = distances.back();
        Elements[current_index].distance_first = distance;
        if (Elements[current_index].SubsequentElements.empty()) { // если пришли в лист проверем дистанцию в паре, и меняем пару если текущая дистанция больше сохранённой
            if (result.first < distance) {
                result.first = distance;
                result.second = current_index;
            }
        } else {
            visit_list.reserve(visit_list.size() + Elements[current_index].SubsequentElements.size());
            visit_list.insert(visit_list.end(), Elements[current_index].SubsequentElements.begin(), Elements[current_index].SubsequentElements.end());
            for (int i = 0; i < Elements[current_index].SubsequentElements.size(); i++) {
                distances.push_back(distance + 1);
            }
        }
    }
}


/*void Tree::DistanceUpSearch_First(int current_index, int distance, pair<int, int> &result, int previous) { // шаг наверх от элемента одновременно с поиском наиболее удалённого от index_first
    Elements[current_index].distance_first = distance; // выставляем текущую дистанцию в просматриваемом элементе
    if ((Elements[current_index].SubsequentElements.empty()) || (current_index == 0)) { // если пришли в лист или в корень (корень может оказаться самым дальним, но не является листом) проверем дистанцию в паре, и меняем пару если текущая дистанция больше сохранённой
        if (result.first <= distance) {
            result.first = distance;
            result.second = current_index;
        }
    }
    for (int i = 0; i < Elements[current_index].SubsequentElements.size(); i++) { // от текущего элемента делаем шаг во все поддеревья
        if (Elements[current_index].SubsequentElements[i] != previous) { // кроме того, из которого пришли
            DistanceDownSearch_First(Elements[current_index].SubsequentElements[i], distance + 1, result);
        }
    }
    if (current_index != 0) { // если не в корне, то не перестаём подниматься дальше
        DistanceUpSearch_First(Elements[current_index].parent_index, distance + 1, result, current_index);
    }
}
*/

void Tree::DistanceUpSearch_First(int current_index, int distance, pair<int, int> &result, int previous) { // шаг наверх от элемента одновременно с поиском наиболее удалённого от index_first
    Elements[current_index].distance_first = distance; // выставляем текущую дистанцию в просматриваемом элементе
    if ((Elements[current_index].SubsequentElements.empty()) || (current_index == 0)) { // если пришли в лист или в корень (корень может оказаться самым дальним, но не является листом) проверем дистанцию в паре, и меняем пару если текущая дистанция больше сохранённой
        if (result.first <= distance) {
            result.first = distance;
            result.second = current_index;
        }
    }
    for (int i = 0; i < Elements[current_index].SubsequentElements.size(); i++) { // от текущего элемента делаем шаг во все поддеревья
        if (Elements[current_index].SubsequentElements[i] != previous) { // кроме того, из которого пришли
            DistanceDownSearch_First(Elements[current_index].SubsequentElements[i], distance + 1, result);
        }
    }
    if (current_index != 0) { // если не в корне, то не перестаём подниматься дальше
        DistanceUpSearch_First(Elements[current_index].parent_index, distance + 1, result, current_index);
    }
}

void Tree::DistanceDownSearch_Second(int current_index, int distance) { // шаг в поддерево без какого-либо поиска, этим и отличается от _First варианта (решил сделать их отдельными, а не одну версию, с костылями)
    Elements[current_index].distance_second = distance; // выставляем текущую дистанцию в просматриваемом элементе
    for (int i = 0; i < Elements[current_index].SubsequentElements.size(); i++) {
        DistanceDownSearch_Second(Elements[current_index].SubsequentElements[i], distance + 1); // после шага в поддерево возможен только шаг в поддерево
    }
}

void Tree::DistanceUpSearch_Second(int current_index, int distance, int previous) { // шаг наверх без какого-либо поиска
    Elements[current_index].distance_second = distance; // выставляем текущую дистанцию в просматриваемом элементе
    for (int i = 0; i < Elements[current_index].SubsequentElements.size(); i++) { // от текущего элемента делаем шаг во все поддеревья
        if (Elements[current_index].SubsequentElements[i] != previous) { // кроме того, из которого пришли
            DistanceDownSearch_Second(Elements[current_index].SubsequentElements[i], distance + 1);
        }
    }
    if (current_index != 0) { // если не в корне, то не перестаём подниматься дальше
        DistanceUpSearch_Second(Elements[current_index].parent_index, distance + 1, current_index);
    }
}
// Время работы: O(n);
// Доп. память: O(n);