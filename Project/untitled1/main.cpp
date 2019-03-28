#include <iostream>
#include <vector>
#include <queue>
#include <set>

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

    vector<vector<int>> vertices_matrix;

public:

    MatrixGraph(int vertices_count);

    ~MatrixGraph();

    void AddEdge(int from, int to, int distance);

    int VerticesCount() const;
    
};

void ShortestRoutesMatrix(const MatrixGraph& graph, vector<vector<int>>& result);

////////////////////////////////////////////////////////////////////////////////

int main() {
    int number, distance;
    cin >> number;
    vector<vector<int>> result(number);
    MatrixGraph graph(number);
    for (int i = 0; i < number; ++i) {
        for (int j = 0; j < number; ++j) {
            cin >> distance;
            result[i].push_back(distance);
            graph.AddEdge(i, j, distance);

        }
    }
    ShortestRoutesMatrix(graph, result);
    for (int i = 0; i < number; ++i) {
        for (int j = 0; j < number; ++j) {
            cout << result[i][j] << ' ';

        }
        cout << endl;
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

    void MatrixGraph::AddEdge(int from, int to, int distance) {
        vertices_matrix[from][to] = distance;
    }

    int MatrixGraph::VerticesCount() const {
        return static_cast<int>(vertices_matrix.size());
    }

////////////////////////////////////////////////////////////////////////////////

 void ShortestRoutesMatrix(const MatrixGraph& graph, vector<vector<int>>& result) {
    int vertices_number = graph.VerticesCount();
    for (int i = 0; i < vertices_number; ++i) {
        for (int u = 0; u < vertices_number; ++u) {
            for (int v = 0; v < vertices_number; ++v) {
                result[u][v] = min(result[u][v], result[u][i] + result[i][v]);
            }
        }
    }
}