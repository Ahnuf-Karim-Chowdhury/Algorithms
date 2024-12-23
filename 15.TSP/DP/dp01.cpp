#include <bits/stdc++.h>
using namespace std;

#define N 5

class TSP {
private:
    int dist[N][N];
    int dp[1 << N][N];
    int path[1 << N][N];  // To track the last city leading to the minimum cost

    // Function to calculate the minimum cost path using DP with bitmasking
    int tsp(int mask, int pos, int n) {
        // Base case: all cities have been visited
        if (mask == (1 << n) - 1) {
            return dist[pos][0]; // Return to the starting city
        }

        // Check if this state has already been computed
        if (dp[mask][pos] != -1) {
            return dp[mask][pos];
        }

        int ans = INT_MAX;
        int best_city = -1;
        // Try to go to all other cities
        for (int city = 0; city < n; ++city) {
            // If the city is not yet visited
            if (!(mask & (1 << city))) {
                int newAns = dist[pos][city] + tsp(mask | (1 << city), city, n);
                if (newAns < ans) {
                    ans = newAns;
                    best_city = city;
                }
            }
        }

        // Track the city leading to the minimum cost
        path[mask][pos] = best_city;
        return dp[mask][pos] = ans;
    }

    void printMatrix(int matrix[N][N]) {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (matrix[i][j] == INT_MAX)
                    cout << "x\t";
                else
                    cout << matrix[i][j] << "\t";
            }
            cout << endl;
        }
    }

    void printPath(vector<int> &nodes, int node) {
        for (int i = 0; i < nodes.size(); ++i) {
            cout << nodes[i] + 1;
            if (i < nodes.size() - 1)
                cout << "->";
        }
        cout << "->" << node + 1;
    }

    void printFullPath(int mask, int pos) {
        vector<int> pathNodes;
        int currentMask = mask;
        int currentPos = pos;

        while (true) {
            pathNodes.push_back(currentPos);
            if (currentMask == (1 << N) - 1) break;
            int nextCity = path[currentMask][currentPos];
            if (nextCity == -1) break;
            currentMask |= (1 << nextCity);
            currentPos = nextCity;
        }
        reverse(pathNodes.begin(), pathNodes.end());
        printPath(pathNodes, pathNodes.back());
        cout << endl;
    }

public:
    TSP(int matrix[N][N]) {
        // Initialize the distance matrix
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                dist[i][j] = matrix[i][j];
            }
        }

        // Initialize DP table with -1 (uncomputed state)
        memset(dp, -1, sizeof(dp));
        memset(path, -1, sizeof(path));
    }

    void solveTSP() {
        int result = tsp(1, 0, N);
        
        cout << "Minimum cost: " << result << endl << endl;

        // Output the path and matrices during the process
        for (int mask = 1; mask < (1 << N); ++mask) {
            for (int pos = 0; pos < N; ++pos) {
                if (dp[mask][pos] != -1 && mask != 1) {
                    cout << "Path: ";
                    printFullPath(mask, pos);
                    cout << endl << "Node: " << pos + 1 << " Cost: " << dp[mask][pos] << endl;
                    printMatrix(dist);
                    cout << endl;
                }
            }
        }

        // Output the shortest path
        cout << "Shortest Path : ";
        vector<int> finalPath;
        int currentMask = (1 << N) - 1;
        int currentPos = 0;
        finalPath.push_back(currentPos);
        while (currentMask != 1) {
            int nextCity = path[currentMask][currentPos];
            finalPath.push_back(nextCity);
            currentMask &= ~(1 << currentPos);
            currentPos = nextCity;
        }
        finalPath.push_back(0);

        for (int i = 0; i < finalPath.size(); ++i) {
            cout << finalPath[i] + 1;
            if (i < finalPath.size() - 1)
                cout << "->";
        }
        cout << endl;
        cout << "Total cost: " << result << endl;
    }
};

int main() {
    int adjacencyMatrix[N][N] = {
        {INT_MAX, 20, 30, 10, 11},
        {15, INT_MAX, 16, 4, 2},
        {3, 5, INT_MAX, 2, 4},
        {19, 6, 18, INT_MAX, 3},
        {16, 4, 7, 16, INT_MAX}
    };

    TSP solver(adjacencyMatrix);
    solver.solveTSP();

    return 0;
}
