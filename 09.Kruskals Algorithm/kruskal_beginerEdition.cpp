#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Define a structure to represent an edge
struct Edge {
    int u, v, weight;
};

// Function to find the representative (root) of the set containing 'u'
int findSet(int u, vector<int>& parent) {
    if (u != parent[u]) {
        parent[u] = findSet(parent[u], parent); // Path compression
    }
    return parent[u];
}

// Function to unite two sets
void unionSets(int u, int v, vector<int>& parent, vector<int>& rank) {
    int rootU = findSet(u, parent);
    int rootV = findSet(v, parent);
    if (rootU != rootV) {
        // Union by rank
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

// Function to perform Kruskal's algorithm
vector<Edge> kruskal(vector<Edge>& edges, int numVertices) {
    vector<Edge> mst; // This will store the resulting Minimum Spanning Tree (MST)
    vector<int> parent(numVertices);
    vector<int> rank(numVertices, 0);

    // Initialize disjoint-set for each vertex
    for (int i = 0; i < numVertices; ++i) {
        parent[i] = i;
    }

    // Sort edges in increasing order of their weights
    sort(edges.begin(), edges.end(), [](Edge a, Edge b) {
        return a.weight < b.weight;
    });

    // Process each edge in order
    for (const Edge& edge : edges) {
        // If u and v are in different sets, add the edge to the MST
        if (findSet(edge.u, parent) != findSet(edge.v, parent)) {
            mst.push_back(edge);          // Add edge to the MST
            unionSets(edge.u, edge.v, parent, rank); // Union the sets
        }
    }

    return mst;
}

int main() {
    int numVertices = 4; // Example number of vertices
    vector<Edge> edges = { {0, 1, 10}, {0, 2, 6}, {0, 3, 5}, {1, 3, 15}, {2, 3, 4} };

    vector<Edge> mst = kruskal(edges, numVertices);

    cout << "Edges in the Minimum Spanning Tree:" << endl;
    for (const Edge& edge : mst) {
        cout << edge.u << " -- " << edge.v << " == " << edge.weight << endl;
    }

    return 0;
}
