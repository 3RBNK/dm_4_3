#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;


void print_vec(const vector<int> &vec) {
    for (const auto x: vec)
        cout << x << " ";
    cout << endl;
}

void print_matrix(const vector<vector<int> > &graph) {
    for (const auto &row: graph)
        print_vec(row);
    cout << endl;
}



vector<vector<int> > get_edges(vector<vector<int> > graph) {
    vector<vector<int> > result;
    for (int i = 0; i < graph.size(); i++)
        for (int j = 0; j < graph.size(); j++)
            if (graph[i][j]) {
                result.push_back({i + 1, j + 1});
                graph[j][i] = 0;
            }
    return result;
}



void print_edges(const vector<vector<int>> &graph) {
    vector<vector<int>> edges = get_edges(graph);
    for (const auto &edge: edges)
        cout << "(" << edge[0] << ", " << edge[1] << ")" << endl;
}



// Выполняет поиск в глубину (DFS) для проверки связности графа
void dfs(int node, const vector<vector<int>> &graph, vector<bool> &visited) {
    visited[node] = true;
    for (int neighbor = 0; neighbor < graph.size(); ++neighbor)
        if (graph[node][neighbor] == 1 && !visited[neighbor])
            dfs(neighbor, graph, visited);
}

// Проверяет, является ли граф связным
bool is_contact(const vector<vector<int>> &graph) {
    const int n = static_cast<int>(graph.size());
    vector<bool> visited(n, false);

    dfs(0, graph, visited);

    for (bool wasVisited : visited)
        if (!wasVisited)
            return false;

    return true;
}



vector<vector<int> > kraskal(vector<vector<int> > graph) {
    vector<vector<int> > edges = get_edges(graph);

    vector<int> b(graph.size());
    for (int i = 0; i < graph.size(); i++)
        b[i] = i + 1;

    vector<vector<int> > forest{graph.size(), vector<int>(graph.size(), 0)};
    for (auto edge: edges) {
        int first_v = edge[0];
        int second_v = edge[1];

        if (b[first_v - 1] != b[second_v - 1]) {
            replace(b.begin(), b.end(), b[second_v - 1], b[first_v - 1]);

            forest[first_v - 1][second_v - 1] = 1;
            forest[second_v - 1][first_v - 1] = 1;
        }
    }
    return forest;
}


int main() {
    const vector<vector<int> > G = {
        {0, 1, 0, 1, 1, 0, 0, 0, 0},
        {1, 0, 1, 0, 0, 0, 0, 1, 1},
        {0, 1, 0, 0, 0, 1, 1, 0, 0},
        {1, 0, 0, 0, 1, 0, 0, 0, 0},
        {1, 0, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0, 0, 1, 0, 0},
        {0, 0, 1, 0, 0, 1, 0, 0, 0},
        {0, 1, 0, 0, 0, 0, 0, 0, 1},
        {0, 1, 0, 0, 0, 0, 0, 1, 0},
    };

    const vector<vector<int>> forest = kraskal(G);

    print_matrix(forest);
    print_edges(forest);

    return 0;
}
