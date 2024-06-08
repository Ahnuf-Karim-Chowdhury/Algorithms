#include <iostream>
#include <vector>
#include <limits>
using namespace std;

int extractMin(const vector<int>& d, const vector<bool>& visited) {
    int min = numeric_limits<int>::max(), min_index = -1;

    for (size_t i = 0; i < d.size(); i++)
        if (!visited[i] && d[i] <= min)
            min = d[i], min_index = i;

    return min_index;
}

void printPath(const vector<int>& parent, const vector<int>& d, int j) {
    if (parent[j] == -1) {
        cout << j << " (Cost: " << d[j] << ")";
        return;
    }

    printPath(parent, d, parent[j]);

    cout << " -> " << j << " (Cost: " << d[j] << ")";
}

void printSolution(const vector<int>& d, const vector<int>& parent, int s, int dest) {
    cout << "Shortest distances from vertex " << s << " to all other vertices:" << endl;
    for (size_t i = 0; i < d.size(); i++) {
        if (d[i] != numeric_limits<int>::max())
            cout << "Vertex " << i+1 << ": " << d[i] << endl;
        else
            cout << "Vertex " << i+1 << ": Not reachable" << endl;
    }

    cout << "Shortest path from " << s << " to " << dest << ": ";
    printPath(parent, d, dest);
    cout << endl;
}

void dijkstra(const vector<vector<int>>& graph, int s, int dest) {
    int V = graph.size();
    vector<int> d(V, numeric_limits<int>::max());
    vector<bool> visited(V, false);
    vector<int> parent(V, -1);

    d[s] = 0;

    for (int c = 0; c < V - 1; c++) {
        int u = extractMin(d, visited);

        visited[u] = true;

        for (int i = 0; i < V; i++) {
            if (!visited[i] && graph[u][i] && d[u] != numeric_limits<int>::max() &&
                d[u] + graph[u][i] < d[i]) {
                d[i] = d[u] + graph[u][i];
                parent[i] = u;
            }
        }
    }

    printSolution(d, parent, s, dest);
}

int main() {
    int n, m;
    cout << "Enter number of vertices and edges: ";
    cin >> n >> m;

    vector<vector<int>> graph(n, vector<int>(n, 0));

    cout << "Enter the edges (source destination weight):" << endl;
    for (int i = 0; i < m; i++) {
        int u, v, weight;
        cin >> u >> v >> weight;
        graph[u][v] = weight;
        //graph[v][u] = weight; // For undirected graph
    }

    int s, dest;
    cout << "Enter the starting and ending vertices: ";
    cin >> s >> dest;

    dijkstra(graph, s, dest);

    return 0;
}
/* 
0 1 4
0 2 2
1 2 3
2 3 1
 */