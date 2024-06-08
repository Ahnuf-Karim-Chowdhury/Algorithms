#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <cmath>
#include <algorithm>
#include <functional>

using namespace std;

const double EPS = 1e-6;

// An edge class to represent a directed edge between two nodes with a certain cost.
struct Edge {
    double cost;
    int from, to;
    Edge(int from, int to, double cost) : from(from), to(to), cost(cost) {}
};

// Node class to track the nodes to visit while running Dijkstra's
struct Node {
    int id;
    double value;
    Node(int id, double value) : id(id), value(value) {}
    bool operator<(const Node& other) const {
        return value > other.value; // reversed for priority queue
    }
};

class DijkstrasShortestPathAdjacencyList {
public:
    DijkstrasShortestPathAdjacencyList(int n) : n(n) {
        createEmptyGraph();
    }

    void addEdge(int from, int to, double cost) {
        graph[from].emplace_back(from, to, cost);
    }

    vector<vector<Edge>> getGraph() {
        return graph;
    }

    vector<int> reconstructPath(int start, int end) {
        if (end < 0 || end >= n) throw invalid_argument("Invalid node index");
        if (start < 0 || start >= n) throw invalid_argument("Invalid node index");
        double dist = dijkstra(start, end);
        vector<int> path;
        if (dist == numeric_limits<double>::infinity()) return path;
        for (int at = end; at != -1; at = prev[at]) path.push_back(at);
        reverse(path.begin(), path.end());
        return path;
    }

private:
    int n;
    vector<double> dist;
    vector<int> prev;
    vector<vector<Edge>> graph;

    double dijkstra(int start, int end) {
        dist.assign(n, numeric_limits<double>::infinity());
        dist[start] = 0;

        priority_queue<Node> pq;
        pq.emplace(start, 0);

        vector<bool> visited(n, false);
        prev.assign(n, -1);

        while (!pq.empty()) {
            Node node = pq.top();
            pq.pop();
            visited[node.id] = true;

            if (dist[node.id] < node.value) continue;

            for (const Edge& edge : graph[node.id]) {
                if (visited[edge.to]) continue;

                double newDist = dist[edge.from] + edge.cost;
                if (newDist < dist[edge.to]) {
                    prev[edge.to] = edge.from;
                    dist[edge.to] = newDist;
                    pq.emplace(edge.to, dist[edge.to]);
                }
            }
            if (node.id == end) return dist[end];
        }
        return numeric_limits<double>::infinity();
    }

    void createEmptyGraph() {
        graph.resize(n);
    }
};

// Example usage
int main() {
    DijkstrasShortestPathAdjacencyList graph(5);
    graph.addEdge(0, 1, 4);
    graph.addEdge(0, 2, 1);
    graph.addEdge(2, 1, 2);
    graph.addEdge(1, 3, 1);
    graph.addEdge(2, 3, 5);

    vector<int> path = graph.reconstructPath(0, 3);
    for (int node : path) {
        cout << node << " ";
    }
    cout << endl;
    return 0;
}
