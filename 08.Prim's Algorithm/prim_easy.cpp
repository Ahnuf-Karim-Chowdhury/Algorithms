#include <iostream>
#include <vector>
#include <limits.h>
using namespace std;

const int INF = INT_MAX;

vector<int> primMST(int n, vector<vector<pair<int, int>>>& graph, int s) {
    vector<int> key(n, INF);   // Minimum weights to connect to the tree
    vector<int> parent(n, -1); // Stores the MST
    vector<bool> inMST(n, false); // To track vertices included in the MST

    key[s] = 0;

    for (int i = 0; i < n - 1; i++) {
        int u = -1;

        for (int v = 0; v < n; v++) {
            if (!inMST[v] && (u == -1 || key[v] < key[u])) {
                u = v;
            }
        }

        inMST[u] = true;

        for (const auto& edge : graph[u]) {
            int v = edge.first;
            int weight = edge.second;

            if (!inMST[v] && weight < key[v]) {
                key[v] = weight;
                parent[v] = u;
            }
        }
    }

    return parent;
}

int main() {
    int n; // Number of vertices
    int e; // Number of edges
    cout << "Enter number of vertices and edges: ";
    cin >> n >> e;

    vector<vector<pair<int, int>>> graph(n);

    cout << "Enter the edges (u v weight):" << endl;
    for (int i = 0; i < e; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }

    int s; // Starting vertex for Prim's algorithm
    cout << "Enter the starting vertex: ";
    cin >> s;

    vector<int> mst = primMST(n, graph, s);

    cout << "Minimum Spanning Tree:" << endl;
    for (int i = 0; i < n; i++) {
        if (i != s) {
            cout << mst[i] << " - " << i << endl;
        }
    }

    return 0;
}

/* 
4 5
2 3 4
0 3 5
0 2 6
0 1 10
1 3 15

s=0



 */