#include <iostream>
#include <vector>
#include <limits.h>
using namespace std;

#define N 5

class TSP {
private:
    struct CustomVertex {
        int vertexNumber;
        pair<int, int> edge;
        int totalCost;
        bool visited[N];
        vector<int> pathNodes;
        int reducedMatrix[N][N];

        CustomVertex() {
            vertexNumber = 0;
            totalCost = 0;
            edge = make_pair(-1, -1);
            for (int i = 0; i < N; ++i) {
                visited[i] = false;
                for (int j = 0; j < N; ++j) {
                    reducedMatrix[i][j] = 0;
                }
            }
        }

        CustomVertex(int num, int p, int matrix[N][N]) {
            vertexNumber = num;
            totalCost = 0;
            edge = make_pair(p, num);
            for (int i = 0; i < N; ++i) {
                visited[i] = false;
                for (int j = 0; j < N; ++j) {
                    reducedMatrix[i][j] = matrix[i][j];
                }
            }
            visited[num] = true;
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
            visited[vertexNumber] = true;
        }

        void copyPathNodes(vector<int> &v) {
            pathNodes.clear();
            for (int i = 0; i < v.size(); ++i) {
                pathNodes.push_back(v[i]);
            }
        }
    };

    int reduceAndCalculateCost(int matrix[N][N]) {
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
    void solveTSP(int matrix[N][N], int start) {
        CustomVertex root = CustomVertex(start, -1, matrix);
        root.totalCost = reduceAndCalculateCost(root.reducedMatrix);
        root.resetPath();
        root.visited[root.vertexNumber] = true;

        vector<CustomVertex> temp;
        temp.push_back(root);

        bool found = false;
        int iterations = 0;

        CustomVertex shortestPath;
        int minCost = INT_MAX;

        while (!temp.empty() && !found) {
            removeNode(temp);
            CustomVertex current = temp[temp.size() - 1];

            temp.pop_back();
            current.pathNodes.push_back(current.vertexNumber);

            iterations++;

            for (int i = 0; i < N; ++i) {
                if (current.reducedMatrix[current.vertexNumber][i] != INT_MAX) {
                    CustomVertex child = CustomVertex(i, current.vertexNumber, current.reducedMatrix);

                    child.copyVisitedArray(current.visited);
                    child.copyPathNodes(current.pathNodes);

                    setInfinity(child.reducedMatrix, current.vertexNumber, child.vertexNumber, child.visited);

                    child.totalCost = current.totalCost + current.reducedMatrix[current.vertexNumber][i] + reduceAndCalculateCost(child.reducedMatrix);

                    cout << "Path: ";
                    displayPath(child.pathNodes, child.vertexNumber);
                    cout << endl;

                    cout << "Node: " << child.vertexNumber + 1 << " ";
                    cout << "Cost: " << child.totalCost << endl;

                    for (int k = 0; k < N; ++k) {
                        for (int j = 0; j < N; ++j) {
                            if (child.reducedMatrix[k][j] == INT_MAX)
                                cout << "x\t";
                            else
                                cout << child.reducedMatrix[k][j] << "\t";
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
                        child.pathNodes.push_back(child.vertexNumber);
                        cout << "Path: ";
                        displayPath(child.pathNodes, child.vertexNumber);
                        cout << endl << endl;
                        
                        if (child.totalCost < minCost) {
                            shortestPath = child;
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
            for (int i = 0; i < shortestPath.pathNodes.size(); ++i) {
                cout << shortestPath.pathNodes[i] + 1 << " -> ";
            }
            cout << "1" << endl;
            cout << "Total cost: " << minCost << endl;
        } else {
            cout << "No valid path found!" << endl;
        }
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

    TSP solver;
    solver.solveTSP(adjacencyMatrix, 0);

    return 0;
}
