#include <iostream>
#include <vector>
#include <limits.h>

using namespace std;

#define N 5
#define INF INT_MAX

class TSP {
private:
    int adjMatrix[N][N];
    vector<vector<int>> dp;
    vector<vector<int>> parent;

    // Function to print the path
    void printPath(int mask, int u, int start) {
        if (mask == (1 << start)) {  // Base case, we've returned to the start
            cout << u + 1 << " -> ";
            return;
        }
        printPath(mask ^ (1 << u), parent[mask][u], start);  // Recursive path reconstruction
        cout << u + 1 << " -> ";
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
        dp.resize(1 << N, vector<int>(N, INF));
        parent.resize(1 << N, vector<int>(N, -1));
    }

    void solveTSP(int start) {
        dp[1 << start][start] = 0; // Starting from the start node

        // Fill DP table
        for (int mask = 1; mask < (1 << N); ++mask) {
            for (int u = 0; u < N; ++u) {
                if (mask & (1 << u)) { // u must be in the subset represented by mask
                    for (int v = 0; v < N; ++v) {
                        if (!(mask & (1 << v)) && adjMatrix[u][v] != INF) {
                            int newMask = mask | (1 << v);
                            if (dp[mask][u] != INF && dp[mask][u] + adjMatrix[u][v] < dp[newMask][v]) {
                                dp[newMask][v] = dp[mask][u] + adjMatrix[u][v];
                                parent[newMask][v] = u;
                            }
                        }
                    }
                }
            }
        }

        // Reconstruct the shortest path
        int endMask = (1 << N) - 1;  // Mask that indicates all nodes have been visited
        int minCost = INF;
        int endNode = -1;
        for (int i = 0; i < N; ++i) {
            if (dp[endMask][i] != INF && adjMatrix[i][start] != INF) {
                int cost = dp[endMask][i] + adjMatrix[i][start];
                if (cost < minCost) {
                    minCost = cost;
                    endNode = i;
                }
            }
        }

        if (minCost == INF) {
            cout << "No valid path found!" << endl;
            return;
        }

        cout << "Shortest Path : ";
        printPath(endMask, endNode, start);  // Reconstruct path back to start
        cout << start + 1 << endl;  // Print start node at the end
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
