#include <bits/stdc++.h>
#include <limits>
#include <tuple>
using namespace std;

const int INF = numeric_limits<int>::max();

// Edge structure 
struct Edge {
    int u, v, weight;
};

// Function to initialize single source 
void initializeSingleSource(vector<int>& dist, vector<int>& pred, int s, int n) {
    dist.assign(n, INF);
    pred.assign(n, -1);
    dist[s] = 0;
}

// Relax function to update the shortest path estimate
void relax(int u, int v, int weight, vector<int>& dist, vector<int>& pred) {
    if (dist[u] != INF && dist[v] > dist[u] + weight) {
        dist[v] = dist[u] + weight;
        pred[v] = u;
    }
}

// Bellman-Ford algorithm to detect negative-weight cycles and find shortest paths
bool bellmanFord(const vector<Edge>& edges, int s, vector<int>& dist, vector<int>& pred, int n) {
    initializeSingleSource(dist, pred, s, n);
    for (int i = 0; i < n - 1; ++i) {
        for (const Edge& edge : edges) {
            relax(edge.u, edge.v, edge.weight, dist, pred);
        }
    }
    for (const Edge& edge : edges) {
        if (dist[edge.u] != INF && dist[edge.v] > dist[edge.u] + edge.weight) {
            return false; // Negative-weight cycle detected
        }
    }
    return true;
}

// Dijkstra's algorithm using a priority queue
void dijkstra(const vector<vector<pair<int, int>>>& adj, int s, vector<int>& dist) {
    int n = adj.size();
    dist.assign(n, INF);
    dist[s] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.emplace(0, s);

    while (!pq.empty()) {
        int d, u;
        tie(d, u) = pq.top();
        pq.pop();
        if (d > dist[u])
            continue;

        for (const auto& [v, weight] : adj[u]) {
            if (dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;
                pq.emplace(dist[v], v);
            }
        }
    }
}

// Johnson's algorithm for all-pairs shortest paths
vector<vector<int>> johnson(int n, const vector<Edge>& edges) {
    // Create a new graph G' with an additional vertex s
    vector<Edge> newEdges = edges;
    int s = n;
    for (int i = 0; i < n; ++i) {
        newEdges.push_back({s, i, 0});
    }

    // Run Bellman-Ford on G' to find h(v)
    vector<int> h(n + 1), pred;
    if (!bellmanFord(newEdges, s, h, pred, n + 1)) {
        cout << "The input graph contains a negative-weight cycle" << endl;
        return {};
    }

    // Reweight the edges
    vector<vector<pair<int, int>>> adj(n);
    for (const Edge& edge : edges) {
        int u = edge.u, v = edge.v, weight = edge.weight + h[u] - h[v];
        adj[u].emplace_back(v, weight);
    }

    // Run Dijkstra's algorithm from each vertex
    vector<vector<int>> distMatrix(n, vector<int>(n));
    for (int u = 0; u < n; ++u) {
        dijkstra(adj, u, distMatrix[u]);
        for (int v = 0; v < n; ++v) {
            if (distMatrix[u][v] < INF) {
                distMatrix[u][v] += h[v] - h[u];
            }
        }
    }

    return distMatrix;
}

int main() {
    int n = 5;
    vector<Edge> edges = {
        {0, 1, 3},
        {0, 2, 8},
        {0, 4, -4},
        {1, 3, 1},
        {1, 4, 7},
        {2, 1, 4},
        {3, 0, 2},
        {3, 2, -5},
        {4, 3, 6}
    };

    vector<vector<int>> result = johnson(n, edges);
    if (!result.empty()) {
        cout << "The shortest path matrix is:" << endl;
        for (const auto& row : result) {
            for (int dist : row) {
                if (dist == INF)
                    cout << "INF ";
                else
                    cout << dist << " ";
            }
            cout << endl;
        }
    }
    return 0;
}
