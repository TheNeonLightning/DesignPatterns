#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <cmath>

using std::pair;
using std::vector;
using std::set;
using std::cin;
using std::cout;
using std::priority_queue;
using std::vector;
using std::min;
using std::endl;

class MatrixGraph {
private:

    vector<vector<double>> vertices_matrix;

public:

    MatrixGraph(int vertices_count);

    ~MatrixGraph();

    void AddEdge(int from, int to, double distance);

    int VerticesCount() const;

    virtual void GetNextVertices(int vertex, vector<int> &vertices, vector<int>& distances) const;

};

bool ProfitCheck(const MatrixGraph& graph);

////////////////////////////////////////////////////////////////////////////////

int main() {
    int number;
    double value;
    cin >> number;
    MatrixGraph graph(number);
    for (int i = 0; i < number; ++i) {
        for (int j = 0; j < number; ++j) {
            if (i != j) {
                cin >> value;
                if (value != -1) {
                    graph.AddEdge(i, j, log(value));
                }
            }
        }
    }
    if (ProfitCheck(graph)) {
        cout << "YES";
    } else {
        cout << "NO";
    }
}

////////////////////////////////////////////////////////////////////////////////

MatrixGraph::MatrixGraph(int vertices_count) {
    vertices_matrix.resize(vertices_count);
    for (int i = 0; i < vertices_count; ++i) {
        vertices_matrix[i].resize(vertices_count);
    }
}

MatrixGraph::~MatrixGraph() {}

void MatrixGraph::AddEdge(int from, int to, double value) {
    vertices_matrix[from][to] = value;
}

int MatrixGraph::VerticesCount() const {
    return static_cast<int>(vertices_matrix.size());
}

void MatrixGraph::GetNextVertices(int vertex, vector<int>& vertices, vector<int>& distances) const {
    vertices.clear();
    distances.clear();
    for (int index_of_current = 0; index_of_current < static_cast<int>(vertices_matrix.size()); ++index_of_current) {
        if (vertices_matrix[vertex][index_of_current] != 0) {
            vertices.push_back(index_of_current);
            distances.push_back(vertices_matrix[vertex][index_of_current]);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

bool ProfitCheck(const MatrixGraph& graph) { // на основе алгоритма Белмана-Форда -> время работы O(V * E)
   unsigned long size = graph.VerticesCount();
    vector<int> vertices;
    vector<int> distances;
    vector<vector<double>> matrix(size + 1); // матрица кратчайших путей состоящих из k(столбцы) вершин до i(строки)
    // элемента
    vector<double> local(size, 100000);
    for (int i = 0; i < size + 1; ++i) {
        matrix[i] = local;
    }
    for (int i = 1; i < size; ++i) {
        matrix[0][i] = 100000; // считаю 100000 == infinity, заполняю первую строку 0 inf inf ... inf
    }
    matrix[0][0] = 0;
    for (int k = 1; k < size + 1; ++k) { // совершаю V - 1 шаг, как в обычном алгоритме
        for (int i = 0; i < size; ++i) {
            graph.GetNextVertices(i, vertices, distances);
            for (int j = 0; j < vertices.size(); ++j) {
                if (matrix[k - 1][i] != 100000) {
                    matrix[k][vertices[j]] = min(matrix[k][vertices[j]],
                                                 matrix[k - 1][i] + distances[j]);
                }
            }
        }
    }
    for (int i = 0; i < size; ++i) { // совершаю ещё один шаг
        if ((matrix[size][i] > 0) && (matrix[size][i] != 100000)) { // если существует неотрицательный цикл -> можно
            // заработать
            return true;
        }
    }
    return false;
}