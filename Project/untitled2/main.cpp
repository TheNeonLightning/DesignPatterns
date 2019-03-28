#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <unordered_map>
#include <cmath>

using std::pow;
using std::pair;
using std::vector;
using std::queue;
using std::set;
using std::cin;
using std::cout;
using std::priority_queue;
using std::swap;
using std::string;
using std::endl;
using std::unordered_map;

class Position {
public:
    vector<int> position;
    int null_position;
    int size = 9;
    double number;

    bool DownCheck();

    bool UpCheck();

    bool LeftCheck();

    bool RightCheck();

    void Up();

    void Down();

    void Left();

    void Right();

    Position Up_();

    Position Down_();

    Position Left_();

    Position Right_();

    Position(vector<int> starting_position);

    bool PossibilityCheck();
};

string SolutionSearch(const Position& position);

////////////////////////////////////////////////////////////////////////////////

int main() {
    vector<int> starting_position(9);
    for (int i = 0; i < 9; ++i) {
        cin >> starting_position[i];
    }
    Position position(starting_position);
    if (!position.PossibilityCheck()) {
        cout << -1;
        return 0;
    }
    string result = SolutionSearch(position);
    cout << result.size() << endl << result;
}

////////////////////////////////////////////////////////////////////////////////


    bool Position::DownCheck() {
        if (null_position > 5) {
            return false;
        } else {
            return true;
        }
    }

    bool Position::UpCheck() {
        if (null_position < 3) {
            return false;
        } else {
            return true;
        }
    }

    bool Position::LeftCheck() {
        if ((null_position == 0) || (null_position == 3) || (null_position == 6)) {
            return false;
        } else {
            return true;
        }
    }

    bool Position::RightCheck() {
        if ((null_position == 2) || (null_position == 5) || (null_position == 8)) {
            return false;
        } else {
            return true;
        }
    }

    void Position::Up() {
        swap(position[null_position], position[null_position - 3]);
        null_position = null_position - 3;
    }

    void Position::Down() {
        swap(position[null_position], position[null_position + 3]);
        null_position = null_position + 3;
    }

    void Position::Left() {
        swap(position[null_position], position[null_position - 1]);
        null_position = null_position - 1;
    }

    void Position::Right() {
        swap(position[null_position], position[null_position + 1]);
        null_position = null_position + 1;
    }

    Position Position::Up_() {
        Position next = *this;
        next.Up();
        next.number = 0;
        for (int i = 0; i < 9; ++i) {
            next.number = next.number + next.position[i] * pow(10,8 - i);
        }
        return next;
    }
    Position Position::Down_() {
        Position next = *this;
        next.Down();
        next.number = 0;
        for (int i = 0; i < 9; ++i) {
            next.number = next.number + next.position[i] * pow(10,8 - i);
        }
        return next;
    }
    Position Position::Left_() {
        Position next = *this;
        next.Left();
        next.number = 0;
        for (int i = 0; i < 9; ++i) {
            next.number = next.number + next.position[i] * pow(10,8 - i);
        }
        return next;
    }
    Position Position::Right_() {
        Position next = *this;
        next.Right();
        next.number = 0;
        for (int i = 0; i < 9; ++i) {
            next.number = next.number + next.position[i] * pow(10,8 - i);
        }
        return next;
    }

Position::Position(vector<int> starting_position) {
        position = std::move(starting_position);
        for (int i = 0; i < size; ++i) {
            if (position[i] == 0) {
                null_position = i;
                break;
            }
        }
        number = 0;
        for (int i = 0; i < 9; ++i) {
            number = number + position[i] * pow(10,8 - i);
        }
    }

    bool Position::PossibilityCheck() {
        int counter = 0;
        for (int i = 0; i < size; ++i) {
            for (int j = 8; j > i; --j) {
                if (position[i] != 0) {
                    if ((position[i] > position[j]) && (position[j] != 0)) {
                        counter = counter + 1;
                    }
                }
            }
        }
        if (counter % 2 == 0) {
            return true;
        } else {
            return false;
        }
    }

string SolutionSearch(const Position& position) {
    queue<Position> buffer;
    int solution = 123456780;
    if (position.number == solution) { // проверка начальной позиции
        return "";
    }
    unordered_map<int, string> visited;
    buffer.push(position);
    visited.emplace<pair<int, string>>({position.number, ""});
    while (!buffer.empty()) {
        Position current = buffer.front();
        buffer.pop();
        if (current.RightCheck()) { // проверка на возможность совершения соответствующего шага
            Position next = current.Right_(); // соответствующий шаг, возвращает новую позицию
            if (visited.count(next.number) == 0) {
                if (next.number == solution) { // проверка следующей позиции
                    return visited[current.number] + 'R';
                }
                buffer.push(next);
                visited.emplace<pair<int, string>>({next.number, visited[current.number] + 'R'}); // кладём в таблицу
                // номер следующего элемента (ключ) и строку, обозначающую путь до него
            }
        }
        if (current.LeftCheck()) { // проверка на возможность совершения соответствующего шага
            Position next = current.Left_(); // соответствующий шаг, возвращает новую позицию
            if (visited.count(next.number) == 0) {
                if (next.number == solution) { // проверка следующей позиции
                    return visited[current.number] + 'L';
                }
                buffer.push(next);
                visited.emplace<pair<int, string>>({next.number, visited[current.number] + 'L'}); // кладём в таблицу
                // номер следующего элемента (ключ) и строку, обозначающую путь до него
            }
        }
        if (current.UpCheck()) { // проверка на возможность совершения соответствующего шага
            Position next = current.Up_(); // соответствующий шаг, возвращает новую позицию
            if (visited.count(next.number) == 0) {
                if (next.number == solution) { // проверка следующей позиции
                    return visited[current.number] + 'U';
                }
                buffer.push(next);
                visited.emplace<pair<int, string>>({next.number, visited[current.number] + 'U'}); // кладём в таблицу
                // номер следующего элемента (ключ) и строку, обозначающую путь до него
            }
        }
        if (current.DownCheck()) { // проверка на возможность совершения соответствующего шага
            Position next = current.Down_(); // соответствующий шаг, возвращает новую позицию
            if (visited.count(next.number) == 0) {
                if (next.number == solution) { // проверка следующей позиции
                    return visited[current.number] + 'D';
                }
                buffer.push(next);
                visited.emplace<pair<int, string>>({next.number, visited[current.number] + 'D'}); // кладём в таблицу
                // номер следующего элемента (ключ) и строку, обозначающую путь до него
            }
        }
    }
}