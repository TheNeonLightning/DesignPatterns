// В город N приехал цирк с командой атлетов. Они хотят удивить горожан города N — выстроить из своих тел башню
// максимальной высоты. Башня — это цепочка атлетов, первый стоит на земле, второй стоит у него на плечах, третий стоит
// на плечах у второго и т.д. Каждый атлет характеризуется силой si (kg) и массой mi (kg). Сила — это максимальная
// масса, которую атлет способен держать у себя на плечах. К сожалению ни один из атлетов не умеет программировать,
// так как всю жизнь они занимались физической подготовкой, и у них не было времени на изучение языков программирования.
// Помогите им, напишите программу, которая определит максимальную высоту башни, которую они могут составить. Известно,
// что если атлет тяжелее, то он и сильнее: если mi>mj, то si > sj. Атлеты равной массы могут иметь различную силу.
#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cin;
using std::cout;
using std::endl;
using std::pair;
using std::sort;

int Tower_Height(vector<pair<int, int>> &array) {
    int current_weight = 0, total_height = 0;
    sort(array.begin(),
         array.end()); // отсортированы по не убыванию (в sort при равных первых учитываются вторые элементы пар)
    for (int i = 0; i < array.size(); i++) { // начинаем строить башню с менее сильных атлетов
        if (current_weight <=
            array[i].second) { // идём по отсортированному массиву слева направо, если атлет может поднять текущую башню,
            total_height++; // то высоту увеличиваем, общую массу перерасчитываем
            current_weight = current_weight + array[i].first;
        }
    }
    return total_height;
}

int  main() {
    int weight, strength;
    vector<pair<int, int>> array;
    while (true) {
        cin >> weight;
        if (cin.fail()) {
            break;
        }
        cin >> strength;
        array.emplace_back(weight, strength);
    }
    cout << Tower_Height(array);
}

// Время работы: O(n log(n));
// Доп. память: O(n);