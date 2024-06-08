#include <bits/stdc++.h>
using namespace std;

int extractMin(const vector<int> &d, const vector<bool> &visited) {
    int min = numeric_limits<int>::max(), min_index = -1;
    for (size_t i = 0; i < d.size(); i++)
        if (!visited[i] && d[i] <= min)
            min = d[i], min_index = i;
    return min_index;
}

void printPath(const vector<int> &parent, int j) {
    if (parent[j] == -1) {
        cout << j << " ";
        return;
    }
    printPath(parent, parent[j]);
    cout << "-> " << j << " ";
}

void printSolution(const vector<int> &d, const vector<int> &parent, int s, int dest) {
    cout << "Shortest distances from vertex " << s << " to all other vertices:" << endl;
    for (size_t i = 0; i < d.size(); i++) {
        if (d[i] != numeric_limits<int>::max())
            cout << "Vertex " << i << ": " << d[i] << endl;
        else
            cout << "Vertex " << i << ": Not reachable" << endl;
    }
    cout << "Shortest path from " << s << " to " << dest << ": ";
    printPath(parent, dest);
    cout << endl;
}

void dijkstra(const vector<vector<int>> &graph, int s, int dest) {
    int n = graph.size();
    vector<int> d(n, numeric_limits<int>::max());
    vector<bool> visited(n, false);
    vector<int> parent(n, -1);

    d[s] = 0;

    for (int c = 0; c < n - 1; c++) {
        int u = extractMin(d, visited);
        if (u == -1) break;  // All remaining vertices are unreachable
        visited[u] = true;

        for (int i = 0; i < n; i++) {
            if (!visited[i] && graph[u][i] && graph[u][i] != numeric_limits<int>::max() &&
                d[u] != numeric_limits<int>::max() && d[u] + graph[u][i] < d[i]) {
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

    vector<vector<int>> graph(n, vector<int>(n, numeric_limits<int>::max()));

    cout << "Enter the edges (source destination weight):" << endl;
    for (int i = 0; i < m; i++) {
        int u, v, weight;
        cin >> u >> v >> weight;
        graph[u][v] = weight;
        graph[v][u] = weight;
    }

    int s, dest;
    cout << "Enter the starting and ending vertices: ";
    cin >> s >> dest;

    dijkstra(graph, s, dest);

    return 0;
}


/*
4 5
0 1 10
0 2 20
1 2 5
1 3 15
2 3 20
 */
/* 
5 7
0 3 5
1 3 2
1 2 1
2 4 4
3 2 9
3 4 2
4 0 7
 */