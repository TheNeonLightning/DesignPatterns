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

class ListGraph {
private:

    vector<vector<pair<int, int>>> vertices_neighbors;

public:

    ListGraph(int vertices_count);

    ~ListGraph();

    void AddEdge(int from, int distance, int to);

    int VerticesCount() const;

    void GetNextVertices(int vertex, vector<pair<int, int>> &vertices) const;

};

int ShortestRouteSearch(const ListGraph& graph, int start, int end);

////////////////////////////////////////////////////////////////////////////////

int main() {
    int cities, roads, from, distance, to;
    cin >> cities >> roads;
    ListGraph graph(cities);
    for (int i = 0; i < roads; ++i) {
        cin >> from >> to >> distance;
        graph.AddEdge(from, distance, to);
        graph.AddEdge(to, distance, from);
    }
    cin >> from >> to;
    cout << ShortestRouteSearch(graph, from, to);
}
////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////ListGraph////////////////////////////////////

ListGraph::ListGraph(int vertices_count) {
    vertices_neighbors.resize(vertices_count);
}

ListGraph::~ListGraph() {}

void ListGraph::AddEdge(int from, int distance, int to) {
    vertices_neighbors[from].push_back({distance, to});
}

int ListGraph::VerticesCount() const {
    return static_cast<int>(vertices_neighbors.size());
}

void ListGraph::GetNextVertices(int vertex, vector<pair<int, int>>& vertices) const {
    vertices.clear();
    vertices = vertices_neighbors[vertex];
}

////////////////////////////////////////////////////////////////////////////////

int ShortestRouteSearch(const ListGraph& graph, int start, int end) {
    int size = graph.VerticesCount();
    pair<int, int> current;
    vector<pair<int, int>> vertices;
    vector<int> distance(size, -1);
    priority_queue<pair<int, int>, std::vector<pair<int, int>>, std::greater<pair<int, int>>> buffer;
    set<int> used;
    buffer.push({0, start});
    while (!buffer.empty()) {
        current = buffer.top();
        if (current.second == end) {
            return distance[end];
        }
        buffer.pop();
        used.insert(current.second);
        graph.GetNextVertices(current.second, vertices);
        for (int i = 0; i < static_cast<int>(vertices.size()); i++) {
            if (used.count(vertices[i].second) == 0) {
                if ((distance[vertices[i].second] > current.first + vertices[i].first)
                    || (distance[vertices[i].second] == -1)) {
                    buffer.push({current.first + vertices[i].first, vertices[i].second});
                    distance[vertices[i].second] = current.first + vertices[i].first;
                }
            }
        }
    }
}