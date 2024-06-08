#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;

// Define a structure for the edges
struct Edge {
    int to;
    int weight;
};

// Define a structure for the priority queue (min-heap)
struct Node {
    int vertex;
    int distance;
    bool operator>(const Node& other) const {
        return distance > other.distance;
    }
};

// Function to initialize the single source
void initialize_single_source(vector<int>& dist, vector<int>& pred, int source, int V) {
    dist.assign(V, numeric_limits<int>::max());
    pred.assign(V, -1);
    dist[source] = 0;
}

// Function to relax the edge
void relax(int u, int v, int weight, vector<int>& dist, vector<int>& pred) {
    if (dist[u] != numeric_limits<int>::max() && dist[v] > dist[u] + weight) {
        dist[v] = dist[u] + weight;
        pred[v] = u;
    }
}

// Dijkstra's algorithm function
void dijkstra(const vector<vector<Edge>>& graph, int source) {
    int V = graph.size();
    vector<int> dist(V), pred(V);
    initialize_single_source(dist, pred, source, V);
    
    priority_queue<Node, vector<Node>, greater<Node>> Q;
    for (int i = 0; i < V; ++i) {
        Q.push({i, dist[i]});
    }

    vector<bool> inS(V, false);

    while (!Q.empty()) {
        int u = Q.top().vertex;
        Q.pop();

        if (inS[u]) continue;
        inS[u] = true;

        for (const auto& edge : graph[u]) {
            int v = edge.to;
            int weight = edge.weight;
            int oldDist = dist[v];
            relax(u, v, weight, dist, pred);
            if (dist[v] < oldDist) {
                Q.push({v, dist[v]});
            }
        }
    }

    // Print the shortest paths from the source to all other vertices
    for (int i = 0; i < V; ++i) {
        cout << "Vertex: " << i << ", Distance: " << dist[i] << ", Predecessor: " << pred[i] << endl;
    }
}

int main() {
    int V = 5; // Number of vertices
    vector<vector<Edge>> graph(V);

    // Example graph
    graph[0] = {{1, 10}, {3, 5}};
    graph[1] = {{2, 1}, {3, 2}};
    graph[2] = {{4, 4}};
    graph[3] = {{1, 3}, {2, 9}, {4, 2}};
    graph[4] = {{0, 7}, {2, 6}};

    int source = 0; // Source vertex
    dijkstra(graph, source);

    return 0;
}
