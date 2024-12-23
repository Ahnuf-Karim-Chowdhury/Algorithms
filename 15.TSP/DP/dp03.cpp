#include <iostream>
#include <vector>
#include <set>
#include <limits.h>
#include <algorithm>

using namespace std;

#define N 5
#define INF INT_MAX

class TSP {
private:
    int adjMatrix[N][N];
    vector<vector<int>> dp;
    vector<vector<int>> parent;

    // Function to print the path
    void printPath(vector<int> &path) {
        for (int i = 0; i < path.size(); i++) {
            cout << path[i] + 1;  // Convert 0-indexed to 1-indexed
            if (i != path.size() - 1) {
                cout << " -> ";
            }
        }
        cout << endl;
    }

public:
    TSP(int matrix[N][N]) {
        // Initialize adjacency matrix
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                adjMatrix[i][j] = matrix[i][j];
            }
        }

        // Initialize DP and parent tables
        dp.resize(N, vector<int>(N * N, INF));  // N * N instead of 1 << N, to track all possible visited states
        parent.resize(N, vector<int>(N * N, -1));  // For path reconstruction
    }

    // Solve TSP using a set-based approach to track visited nodes
    void solveTSP(int start) {
        set<int> initialSet;
        initialSet.insert(start);  // Start node is visited

        dp[start][1] = 0;  // Initialize DP table with starting node visited

        // We use a map of sets to store visited nodes for each state
        vector<set<int>> visitedSets(N * N);

        // Add the start node set to the first state
        visitedSets[1] = initialSet;

        for (int setSize = 1; setSize < N; ++setSize) {  // Explore sets of increasing size
            for (int u = 0; u < N; ++u) {
                if (dp[u][setSize] == INF) continue;  // Skip unvisited sets

                for (int v = 0; v < N; ++v) {
                    if (u == v || visitedSets[setSize].count(v) || adjMatrix[u][v] == INF) continue;  // Avoid visiting already visited nodes

                    // Create a new set by adding v to the visited set
                    set<int> newSet = visitedSets[setSize];
                    newSet.insert(v);

                    int newSetSize = newSet.size();

                    if (dp[v][newSetSize] > dp[u][setSize] + adjMatrix[u][v]) {
                        dp[v][newSetSize] = dp[u][setSize] + adjMatrix[u][v];
                        parent[v][newSetSize] = u;
                        visitedSets[newSetSize] = newSet;  // Update visited set
                    }
                }
            }
        }

        // Find the minimum cost to return to the start node
        int minCost = INF;
        int lastNode = -1;
        set<int> allVisited;  // All nodes visited

        for (int i = 0; i < N; ++i) allVisited.insert(i);
        int allVisitedSize = allVisited.size();

        for (int u = 0; u < N; ++u) {
            if (dp[u][allVisitedSize] != INF && adjMatrix[u][start] != INF) {
                int cost = dp[u][allVisitedSize] + adjMatrix[u][start];  // Complete the tour by returning to start
                if (cost < minCost) {
                    minCost = cost;
                    lastNode = u;
                }
            }
        }

        // Print the shortest path and cost
        if (minCost == INF) {
            cout << "No valid path found!" << endl;
            return;
        }

        // Reconstruct the path
        vector<int> path;
        set<int> currSet = allVisited;
        int currNode = lastNode;

        while (currNode != -1) {
            path.push_back(currNode);
            int temp = parent[currNode][currSet.size()];
            currSet.erase(currNode);  // Remove current node from the set
            currNode = temp;
        }

        path.push_back(start);  // Go back to the start
        reverse(path.begin(), path.end());

        cout << "Shortest Path : ";
        printPath(path);
        cout << "Total cost: " << minCost << endl;
    }
};

int main() {
    int adjacencyMatrix[N][N] = {
        {INF, 20, 30, 10, 11},
        {15, INF, 16, 4, 2},
        {3, 5, INF, 2, 4},
        {19, 6, 18, INF, 3},
        {16, 4, 7, 16, INF}
    };

    TSP solver(adjacencyMatrix);
    solver.solveTSP(0);  // Start from node 1 (0-indexed as 0)

    return 0;
}
