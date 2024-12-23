#include <bits/stdc++.h>
using namespace std;

#define N 5

class TSP {
private:
    struct CustomVertex {
        int vertexNum, totalCost;
        pair<int, int> edge;
        bool visited[N];
        vector<int> pathNodes;
        int reducedMat[N][N];

        CustomVertex() : vertexNum(0), totalCost(0), edge(-1, -1) {
            fill(begin(visited), end(visited), false);
            for (int i = 0; i < N; ++i)
                fill(begin(reducedMat[i]), end(reducedMat[i]), 0);
        }

        CustomVertex(int num, int p, int matrix[N][N]) : vertexNum(num), totalCost(0), edge(p, num) {
            fill(begin(visited), end(visited), false);
            visited[num] = true;
            for (int i = 0; i < N; ++i)
                copy(begin(matrix[i]), end(matrix[i]), begin(reducedMat[i]));
        }

        void resetPath() {
            pathNodes.clear();
            fill(begin(visited), end(visited), false);
        }

        void copyVisitedArray(const bool v[N]) {
            copy(v, v + N, visited);
            visited[vertexNum] = true;
        }

        void copyPathNodes(const vector<int>& v) {
            pathNodes = v;
        }
    };

    int reducedCost(int matrix[N][N]) {
        int cost = 0;
        for (int i = 0; i < N; ++i) {
            int rowMin = *min_element(begin(matrix[i]), end(matrix[i]));
            if (rowMin != INT_MAX) {
                cost += rowMin;
                for (int j = 0; j < N; ++j)
                    if (matrix[i][j] != INT_MAX)
                        matrix[i][j] -= rowMin;
            }
        }
        for (int j = 0; j < N; ++j) {
            int colMin = INT_MAX;
            for (int i = 0; i < N; ++i)
                colMin = min(colMin, matrix[i][j]);
            if (colMin != INT_MAX) {
                cost += colMin;
                for (int i = 0; i < N; ++i)
                    if (matrix[i][j] != INT_MAX)
                        matrix[i][j] -= colMin;
            }
        }
        return cost;
    }

    void setInfinity(int matrix[N][N], int row, int col, const bool v[N]) {
        fill(begin(matrix[row]), end(matrix[row]), INT_MAX);
        for (int i = 0; i < N; ++i)
            matrix[i][col] = INT_MAX;
        for (int i = 0; i < N; ++i)
            if (v[i])
                matrix[col][i] = INT_MAX;
    }

    void displayPath(const vector<int>& v, int node) {
        for (int i : v) cout << i + 1 << "->";
        cout << node + 1;
    }

public:
    void TSPsoln(int matrix[N][N], int start) {
        CustomVertex root(start, -1, matrix);
        root.totalCost = reducedCost(root.reducedMat);
        root.resetPath();
        root.visited[root.vertexNum] = true;

        multimap<int, CustomVertex> temp;
        temp.insert({root.totalCost, root});

        bool found = false;
        CustomVertex shortPath;
        int minCost = INT_MAX;

        while (!temp.empty() && !found) {
            auto [cost, curr] = *temp.begin();
            temp.erase(temp.begin());
            curr.pathNodes.push_back(curr.vertexNum);

            for (int i = 0; i < N; ++i) {
                if (curr.reducedMat[curr.vertexNum][i] != INT_MAX) {
                    CustomVertex child(i, curr.vertexNum, curr.reducedMat);
                    child.copyVisitedArray(curr.visited);
                    child.copyPathNodes(curr.pathNodes);
                    setInfinity(child.reducedMat, curr.vertexNum, child.vertexNum, child.visited);
                    child.totalCost = curr.totalCost + curr.reducedMat[curr.vertexNum][i] + reducedCost(child.reducedMat);

                    temp.insert({child.totalCost, child});

                    if (all_of(begin(child.visited), end(child.visited), [](bool v) { return v; })) {
                        child.pathNodes.push_back(child.vertexNum);
                        if (child.totalCost < minCost) {
                            shortPath = child;
                            minCost = child.totalCost;
                        }
                        found = true;
                        break;
                    }
                }
            }
        }

        if (found) {
            cout << "Shortest Path : ";
            for (int i : shortPath.pathNodes) cout << i + 1 << " -> ";
            cout << "1\nTotal cost: " << minCost << endl;
        } else {
            cout << "No valid path found!" << endl;
        }
    }
};

int main() {
    int adj[N][N] = {
        {INT_MAX, 20, 30, 10, 11},
        {15, INT_MAX, 16, 4, 2},
        {3, 5, INT_MAX, 2, 4},
        {19, 6, 18, INT_MAX, 3},
        {16, 4, 7, 16, INT_MAX}
    };

    TSP solver;
    solver.TSPsoln(adj, 0);

    return 0;
}
