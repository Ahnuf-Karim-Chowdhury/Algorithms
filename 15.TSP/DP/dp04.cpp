#include <iostream>
#include <vector>
#include <limits.h>
#include <algorithm>
#include <set>

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
        for (int i = 0; i < path.size(); ++i) {
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
        dp.resize(N, vector<int>(1 << N, INF));  // DP table to track the cost of visiting all sets
        parent.resize(N, vector<int>(1 << N, -1));  // Parent table for path reconstruction
    }

    // Solve TSP using a dynamic programming approach without bitwise operations
    void solveTSP(int start) {
        dp[start][1 << start] = 0;  // Start at the given node with only the start node visited

        // Iterate over all sets of visited nodes
        for (int mask = 1; mask < (1 << N); ++mask) {
            for (int u = 0; u < N; ++u) {
                if (mask & (1 << u)) {  // u is in the current set
                    for (int v = 0; v < N; ++v) {
                        if (!(mask & (1 << v)) && adjMatrix[u][v] != INF) {  // v is not yet visited
                            int newMask = mask | (1 << v);
                            if (dp[v][newMask] > dp[u][mask] + adjMatrix[u][v]) {
                                dp[v][newMask] = dp[u][mask] + adjMatrix[u][v];
                                parent[v][newMask] = u;
                            }
                        }
                    }
                }
            }
        }

        // Find the minimum cost to return to the starting node
        int minCost = INF;
        int lastNode = -1;
        int fullMask = (1 << N) - 1;  // All nodes visited

        for (int u = 0; u < N; ++u) {
            if (dp[u][fullMask] != INF && adjMatrix[u][start] != INF) {
                int cost = dp[u][fullMask] + adjMatrix[u][start];
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
        int currNode = lastNode;
        int mask = fullMask;

        while (currNode != -1) {
            path.push_back(currNode);
            int temp = parent[currNode][mask];
            mask ^= (1 << currNode);  // Remove the current node from the mask
            currNode = temp;
        }

        path.push_back(start);  // Return to the starting node
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
