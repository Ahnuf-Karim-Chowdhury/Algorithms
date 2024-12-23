#include <bits/stdc++.h>
using namespace std;

#define N 5

class TSP {
private:
    struct CustomVertex {
        int vertexNum;
        pair<int, int> edge;
        int totalCost;
        bool visited[N];
        vector<int> pathNodes;
        int reducedMat[N][N];

        CustomVertex() {
            vertexNum = 0;
            totalCost = 0;
            edge = make_pair(-1, -1);
            initializeVisitedAndReducedMatrix();
        }

        CustomVertex(int num, int p, int matrix[N][N]) {
            vertexNum = num;
            totalCost = 0;
            edge = make_pair(p, num);
            initializeVisitedAndReducedMatrix();
            copyReducedMatrix(matrix);
            visited[num] = true;
        }

        void initializeVisitedAndReducedMatrix() {
            for (int i = 0; i < N; ++i) {
                visited[i] = false;
                for (int j = 0; j < N; ++j) {
                    reducedMat[i][j] = 0;
                }
            }
        }

        void copyReducedMatrix(int matrix[N][N]) {
            for (int i = 0; i < N; ++i) {
                for (int j = 0; j < N; ++j) {
                    reducedMat[i][j] = matrix[i][j];
                }
            }
        }

        void resetPath() {
            pathNodes.clear();
            for (int i = 0; i < N; ++i) {
                visited[i] = false;
            }
        }

        void copyVisitedArray(bool v[N]) {
            for (int i = 0; i < N; ++i) {
                visited[i] = v[i];
            }
            visited[vertexNum] = true;
        }

        void copyPathNodes(vector<int> &v) {
            pathNodes.clear();
            for (int i = 0; i < v.size(); ++i) {
                pathNodes.push_back(v[i]);
            }
        }
    };

    int reducedCost(int matrix[N][N]) {
        int cost = 0;
        for (int i = 0; i < N; ++i) {
            int smallest = INT_MAX;
            for (int j = 0; j < N; ++j) {
                if (matrix[i][j] < smallest)
                    smallest = matrix[i][j];
            }
            for (int k = 0; k < N; ++k) {
                if (matrix[i][k] != INT_MAX)
                    matrix[i][k] -= smallest;
            }
            if (smallest != INT_MAX)
                cost += smallest;
        }

        for (int i = 0; i < N; ++i) {
            int smallest = INT_MAX;
            for (int j = 0; j < N; ++j) {
                if (matrix[j][i] < smallest)
                    smallest = matrix[j][i];
            }
            for (int k = 0; k < N; ++k) {
                if (matrix[k][i] != INT_MAX)
                    matrix[k][i] -= smallest;
            }
            if (smallest != INT_MAX)
                cost += smallest;
        }
        return cost;
    }

    void removeNode(vector<CustomVertex> &v) {
        int cost = INT_MAX;
        int temp = 0;

        for (int i = 0; i < v.size(); ++i) {
            if (v[i].totalCost < cost) {
                cost = v[i].totalCost;
                temp = i;
            }
        }

        swap(v[temp], v[v.size() - 1]);
    }

    void setInfinity(int matrix[N][N], int row, int col, bool v[N]) {
        for (int i = 0; i < N; ++i) {
            matrix[row][i] = INT_MAX;
            matrix[i][col] = INT_MAX;
        }
        for (int i = 0; i < N; ++i) {
            if (v[i] == true) {
                matrix[col][i] = INT_MAX;
            }
        }
    }

    void displayPath(vector<int> &v, int node) {
        for (int i = 0; i < v.size(); ++i) {
            cout << v[i] + 1 << "->";
        }
        cout << node + 1;
    }

public:
    void TSPsoln(int matrix[N][N], int start) {
        CustomVertex root = CustomVertex(start, -1, matrix);
        root.totalCost = reducedCost(root.reducedMat);
        root.resetPath();
        root.visited[root.vertexNum] = true;

        vector<CustomVertex> temp;
        temp.push_back(root);

        bool found = false;
        int itr = 0;

        CustomVertex shortPath;
        int minCost = INT_MAX;

        while (!temp.empty() && !found) {
            removeNode(temp);
            CustomVertex curr = temp[temp.size() - 1];

            temp.pop_back();
            curr.pathNodes.push_back(curr.vertexNum);

            itr++;

            for (int i = 0; i < N; ++i) {
                if (curr.reducedMat[curr.vertexNum][i] != INT_MAX) {
                    CustomVertex child = CustomVertex(i, curr.vertexNum, curr.reducedMat);

                    child.copyVisitedArray(curr.visited);
                    child.copyPathNodes(curr.pathNodes);

                    setInfinity(child.reducedMat, curr.vertexNum, child.vertexNum, child.visited);

                    child.totalCost = curr.totalCost + curr.reducedMat[curr.vertexNum][i] + reducedCost(child.reducedMat);

                    cout << "Path: ";
                    displayPath(child.pathNodes, child.vertexNum);
                    cout << endl;

                    cout << "Node: " << child.vertexNum + 1 << " ";
                    cout << "Cost: " << child.totalCost << endl;

                    for (int k = 0; k < N; ++k) {
                        for (int j = 0; j < N; ++j) {
                            if (child.reducedMat[k][j] == INT_MAX)
                                cout << "x\t";
                            else
                                cout << child.reducedMat[k][j] << "\t";
                        }
                        cout << endl;
                    }

                    temp.push_back(child);

                    int trueCount = 0;
                    for (int i = 0; i < N; ++i) {
                        if (child.visited[i] == true)
                            trueCount++;
                    }
                    if (trueCount == N) {
                        child.pathNodes.push_back(child.vertexNum);
                        cout << "Path: ";
                        displayPath(child.pathNodes, child.vertexNum);
                        cout << endl << endl;

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
            for (int i = 0; i < shortPath.pathNodes.size(); ++i) {
                cout << shortPath.pathNodes[i] + 1 << " -> ";
            }
            cout << "1" << endl;
            cout << "Total cost: " << minCost << endl;
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
