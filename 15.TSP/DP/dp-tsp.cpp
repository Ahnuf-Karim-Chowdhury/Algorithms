#include <bits/stdc++.h>
using namespace std;

#define N 5

class TSP {
private:
    int dist[N][N];
    int dp[1 << N][N];

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
        // Try to go to all other cities
        for (int city = 0; city < n; ++city) {
            // If the city is not yet visited
            if (!(mask & (1 << city))) {
                int newAns = dist[pos][city] + tsp(mask | (1 << city), city, n);
                ans = min(ans, newAns);
            }
        }

        return dp[mask][pos] = ans;
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
    }

    void solveTSP() {
        int result = tsp(1, 0, N);
        cout << "Minimum cost: " << result << endl;
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
