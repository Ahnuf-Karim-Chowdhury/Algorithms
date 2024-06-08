#include <bits/stdc++.h>
#include <limits.h>
using namespace std;

// Edge structure to store the graph edges
struct Edge {
    int vertex;
    int weight;
};

// Comparator for the priority queue to make it a min-heap
struct Compare {
    bool operator()(pair<int, int> const& a, pair<int, int> const& b) {
        return a.second > b.second;
    }
};

// Function to perform Prim's algorithm
vector<int> primMST(int n, vector<vector<Edge>>& graph, int start) {
    // Priority queue to store (vertex, key) pairs
    priority_queue<pair<int, int>, vector<pair<int, int>>, Compare> minHeap;

    // Vectors to store the minimum edge weight to reach a vertex and the parent vertex
    vector<int> key(n, INT_MAX);
    vector<int> parent(n, -1);

    // To track vertices included in the MST
    vector<bool> inMST(n, false);

    // Initialize the start vertex
    key[start] = 0;
    minHeap.push({start, 0});

    while (!minHeap.empty()) {
        // Extract the vertex with the minimum key value
        int u = minHeap.top().first;
        minHeap.pop();

        // If the vertex is already included in the MST, skip it
        if (inMST[u]) continue;

        // Mark the vertex as included in the MST
        inMST[u] = true;

        // Iterate over all adjacent vertices
        for (const auto& edge : graph[u]) {
            int v = edge.vertex;
            int weight = edge.weight;

            // If v is not in the MST and weight of (u, v) is smaller than current key of v
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
    int n; // Number of vertices
    int e; // Number of edges
    cout << "Enter number of vertices and edges: ";
    cin >> n >> e;

    // Adjacency list representation of the graph
    vector<vector<Edge>> graph(n);

    cout << "Enter the edges (u v weight):" << endl;
    for (int i = 0; i < e; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }

    int start; // Starting vertex for Prim's algorithm
    cout << "Enter the starting vertex: ";
    cin >> start;

    vector<int> mst = primMST(n, graph, start);

    // Display the resulting MST
    cout << "Minimum Spanning Tree:" << endl;
    for (int i = 0; i < n; ++i) {
        if (i != start) {
            cout << mst[i] << " - " << i << endl;
        }
    }

    return 0;
}
