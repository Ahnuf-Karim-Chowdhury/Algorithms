#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v, weight;
};

bool Comparator(const Edge& a, const Edge& b) {
    return a.weight < b.weight;
}

class DisjointSet {
public:
    DisjointSet(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }

    int findSet(int u) {
        if (u != parent[u]) {
            parent[u] = findSet(parent[u]);
        }
        return parent[u];
    }

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

vector<Edge> kruskal(vector<Edge>& edges, int n) {
    vector<Edge> mst;
    DisjointSet ds(n);
    sort(edges.begin(), edges.end(), Comparator);
    for (const Edge& edge : edges) {
        if (ds.findSet(edge.u) != ds.findSet(edge.v)) {
            mst.push_back(edge);
            ds.unionSets(edge.u, edge.v);
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
