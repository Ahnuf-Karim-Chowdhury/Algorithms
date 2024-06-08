#include <bits/stdc++.h>
using namespace std;

// Define a structure to represent an edge
struct Edge {
    int u, v, weight;
    //sorting by edge weight
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

// A class to represent the disjoint-set data structure
class DisjointSet {
public:
    DisjointSet(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }

    // Find the representative of the set containing 'u'
    int findSet(int u) {
        if (u != parent[u]) {
            parent[u] = findSet(parent[u]); // Path compression
        }
        return parent[u];
    }

    // Union by rank
    void unionSets(int u, int v) {
        int rootU = findSet(u);
        int rootV = findSet(v);
        if (rootU != rootV) {
            if (rank[rootU] > rank[rootV]) {
                parent[rootV] = rootU;
            } else if (rank[rootU] < rank[rootV]) {
                parent[rootU] = rootV;
            } else {
                parent[rootV] = rootU;
                ++rank[rootU];
            }
        }
    }

private:
    vector<int> parent;
    vector<int> rank;
};

// Function to perform Kruskal's algorithm
vector<Edge> kruskal(vector<Edge>& edges, int n) {
    vector<Edge> mst; // This will store the resulting MST
    DisjointSet ds(n);

    // Step 4: Sort edges in increasing order of weights
    sort(edges.begin(), edges.end());

    // Step 6-9: Process each edge in order
    for (const Edge& edge : edges) {
        if (ds.findSet(edge.u) != ds.findSet(edge.v)) {
            mst.push_back(edge);          // Step 8: Add edge to the MST
            ds.unionSets(edge.u, edge.v); // Step 9: Union the sets
        }
    }

    return mst;
}

int main() {
    int n = 4; 
    vector<Edge> edges = { {0, 1, 10}, {0, 2, 6}, {0, 3, 5}, {1, 3, 15}, {2, 3, 4} };

    vector<Edge> mst = kruskal(edges, n);

    cout << "Edges in the Minimum Spanning Tree:" << endl;
    for (const Edge& edge : mst) {
        cout << edge.u << " -- " << edge.v << " == " << edge.weight << endl;
    }

    return 0;
}
