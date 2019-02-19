#include <iostream>
#include <vector>
#include <queue>


using std::vector;
using std::queue;
using std::cin;
using std::cout;

class ListGraph {
private:

    vector<vector<int>> vertices_neighbors;

public:

    vector<int> color;

    ListGraph(int vertices_count);

    ~ListGraph();

    void AddEdge(int from, int to);

    int VerticesCount() const;

    void GetNextVertices(int vertex, vector<int> &vertices) const;

    void GetPrevVertices(int vertex, vector<int> &vertices) const;

};

////////////////////////////////////////////////////////////////////////////////

int main() {
    int vertices, edge_number, from, to;
    cin >> vertices >> edge_number;
    ListGraph graph(vertices);
    for (int i = 0; i < edge_number; i++) {
        cin >> from >> to;
        graph.AddEdge(from, to);
    }

}

////////////////////////////////////////////////////////////////////////////////

ListGraph::ListGraph(int vertices_count) {
    vertices_neighbors.resize(vertices_count);
    color.resize(vertices_count);
}

ListGraph::~ListGraph() {}

void ListGraph::AddEdge(int from, int to) {
    vertices_neighbors[from].push_back(to);
}

int ListGraph::VerticesCount() const {
    return static_cast<int>(vertices_neighbors.size());
}

void ListGraph::GetNextVertices(int vertex, vector<int>& vertices) const {
    vertices.clear();
    vertices = vertices_neighbors[vertex];
}

void ListGraph::GetPrevVertices(int vertex, vector<int>& vertices) const {
    vertices.clear();
    for (size_t parent = 0; parent < static_cast<int>(vertices_neighbors.size()); parent++) {
        for (size_t child = 0; child < static_cast<int>(vertices_neighbors.size()); child++) {
            if (vertices_neighbors[parent][child] == vertex) {
                vertices.push_back(parent);
            }
        }
    }
}

void ListGraph::BFS(int index) {
    queue<int> to_visit;
    to_visit.push(index);
    int current_color = 1;
    vector<int> next_vertices;
    while (!to_visit.empty()) {
        GetNextVertices(to_visit.front(), next_vertices);
        for (int i = 0; i < static_cast<int>(next_vertices.size()); i++) {
            to_visit.push(next_vertices[i]);
        }
        next_vertices.clear();
        color[to_visit.front()] = current_color;
        current_color == 1 ? current_color = 2 : current_color = 1;
        to_visit.pop();
    }
}

void BipartiteGraphCheck(const ListGraph* graph) {
    for (int i = 0; i < graph->VerticesCount(); i++) {
        if (graph->color[i] == 0) {
            graph->BFS(i);
        }
    }
    for (int i = 0; i < graph->VerticesCount() - 1; i++) {
        if color[i] == color
