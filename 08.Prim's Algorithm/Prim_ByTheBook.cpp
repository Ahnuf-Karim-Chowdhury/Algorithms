#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>
using namespace std;

struct Edge {
    int vertex;
    int weight;
};

struct Compare {
    bool operator()(pair<int, int> const& a, pair<int, int> const& b) {
        return a.second > b.second;
    }
};

vector<int> primMST(int n, vector<vector<Edge>>& graph, int start) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, Compare> minHeap;
    vector<int> key(n, INT_MAX);
    vector<int> parent(n, -1);
    vector<bool> inMST(n, false);

    key[start] = 0;
    minHeap.push({start, 0});

    while (!minHeap.empty()) {
        int u = minHeap.top().first;
        minHeap.pop();

        if (inMST[u]) continue;

        inMST[u] = true;

        for (const auto& edge : graph[u]) {
            int v = edge.vertex;
            int weight = edge.weight;

            if (!inMST[v] && weight < key[v]) {
                key[v] = weight;
                minHeap.push({v, key[v]});
                parent[v] = u;
            }
        }
    }

    return parent;
}

int main() {
    int n;
    int e;
    cout << "Enter number of vertices and edges: ";
    cin >> n >> e;

    vector<vector<Edge>> graph(n);

    cout << "Enter the edges (u v weight):" << endl;
    for (int i = 0; i < e; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }

    int start;
    cout << "Enter the starting vertex: ";
    cin >> start;

    vector<int> mst = primMST(n, graph, start);

    cout << "Minimum Spanning Tree:" << endl;
    for (int i = 0; i < n; ++i) {
        if (i != start) {
            cout << mst[i] << " - " << i << endl;
        }
    }

    return 0;
}
