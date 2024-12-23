#include <bits/stdc++.h> // Includes all standard C++ libraries
using namespace std; // Uses the standard namespace

#define N 4 // Defines the number of vertices in the TSP problem

class TSP { // Defines the TSP class
private:
    struct CustomVertex { // Defines a custom vertex structure
        int vertexNum, totalCost; // Vertex number and total cost
        pair<int, int> edge; // Edge represented by a pair of vertices
        bool visited[N]; // Array to mark visited vertices
        vector<int> pathNodes; // Vector to store the path of nodes
        int reducedMat[N][N]; // Reduced cost matrix for the current vertex

        // Default constructor
        CustomVertex() : vertexNum(0), totalCost(0), edge(-1, -1) {
            fill(begin(visited), end(visited), false); // Initialize visited array to false
            for (int i = 0; i < N; ++i)
                fill(begin(reducedMat[i]), end(reducedMat[i]), 0); // Initialize reduced matrix to 0
        }

        // Parameterized constructor
        CustomVertex(int num, int p, int matrix[N][N]) : vertexNum(num), totalCost(0), edge(p, num) {
            fill(begin(visited), end(visited), false); // Initialize visited array to false
            visited[num] = true; // Mark the current vertex as visited
            for (int i = 0; i < N; ++i)
                copy(begin(matrix[i]), end(matrix[i]), begin(reducedMat[i])); // Copy the matrix
        }

        // Resets the path
        void resetPath() {
            pathNodes.clear(); // Clears the path vector
            fill(begin(visited), end(visited), false); // Reset the visited array
        }

        // Copies the visited array
        void copyVisitedArray(const bool v[N]) {
            copy(v, v + N, visited); // Copy the visited array
            visited[vertexNum] = true; // Mark the current vertex as visited
        }

        // Copies the path nodes
        void copyPathNodes(const vector<int>& v) {
            pathNodes = v; // Copy the path nodes
        }
    };

    // Reduces the cost matrix and returns the reduced cost
    int reducedCost(int matrix[N][N]) {
        int cost = 0; // Initialize cost to 0
        for (int i = 0; i < N; ++i) {
            int rowMin = *min_element(begin(matrix[i]), end(matrix[i])); // Find the minimum element in the row
            if (rowMin != INT_MAX) { // If the minimum element is not infinity
                cost += rowMin; // Add the minimum element to the cost
                for (int j = 0; j < N; ++j)
                    if (matrix[i][j] != INT_MAX)
                        matrix[i][j] -= rowMin; // Subtract the minimum element from each element in the row
            }
        }
        cout << "After Row Reduction the Matrix : " << endl; // Print the message
        displayMatrix(matrix); // Display the matrix

        for (int j = 0; j < N; ++j) {
            int colMin = INT_MAX; // Initialize column minimum to infinity
            for (int i = 0; i < N; ++i)
                colMin = min(colMin, matrix[i][j]); // Find the minimum element in the column
            if (colMin != INT_MAX) { // If the minimum element is not infinity
                cost += colMin; // Add the minimum element to the cost
                for (int i = 0; i < N; ++i)
                    if (matrix[i][j] != INT_MAX)
                        matrix[i][j] -= colMin; // Subtract the minimum element from each element in the column
            }
        }
        cout << "After Column Reduction the Matrix : " << endl; // Print the message
        displayMatrix(matrix); // Display the matrix

        return cost; // Return the total reduced cost
    }

    // Sets the row and column of a vertex to infinity in the matrix
    void setInfinity(int matrix[N][N], int row, int col, const bool v[N]) {
        fill(begin(matrix[row]), end(matrix[row]), INT_MAX); // Set the row to infinity
        for (int i = 0; i < N; ++i)
            matrix[i][col] = INT_MAX; // Set the column to infinity
        for (int i = 0; i < N; ++i)
            if (v[i])
                matrix[col][i] = INT_MAX; // Set the corresponding elements to infinity
    }

    // Displays the path
    void displayPath(const vector<int>& v, int node) {
        vector<char> cities = {'A', 'B', 'C', 'D'}; // Define the city names
        for (int i : v) cout << cities[i] << "->"; // Print the path
        cout << cities[node]; // Print the last node
    }

    // Displays the matrix
    void displayMatrix(int matrix[N][N]) {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (matrix[i][j] == INT_MAX)
                    cout << "x\t"; // Print x for infinity
                else
                    cout << matrix[i][j] << "\t"; // Print the element
            }
            cout << endl;
        }
    }

public:
    // Solves the TSP problem
    void TSPsoln(int matrix[N][N], int start) {
        CustomVertex root(start, -1, matrix); // Create the root vertex
        root.totalCost = reducedCost(root.reducedMat); // Calculate the reduced cost for the root
        root.resetPath(); // Reset the path for the root
        root.visited[root.vertexNum] = true; // Mark the root vertex as visited

        multimap<int, CustomVertex> temp; // Create a multimap to store vertices by cost
        temp.insert({root.totalCost, root}); // Insert the root vertex into the multimap

        bool found = false; // Flag to check if the solution is found
        CustomVertex shortPath; // Variable to store the shortest path
        int minCost = INT_MAX; // Initialize the minimum cost to infinity

        // While there are vertices to process and the solution is not found
        while (!temp.empty() && !found) {
            auto [cost, curr] = *temp.begin(); // Get the vertex with the minimum cost
            temp.erase(temp.begin()); // Remove the vertex from the multimap
            curr.pathNodes.push_back(curr.vertexNum); // Add the current vertex to the path

            // For each adjacent vertex
            for (int i = 0; i < N; ++i) {
                if (curr.reducedMat[curr.vertexNum][i] != INT_MAX) { // If the edge exists
                    CustomVertex child(i, curr.vertexNum, curr.reducedMat); // Create a child vertex
                    child.copyVisitedArray(curr.visited); // Copy the visited array
                    child.copyPathNodes(curr.pathNodes); // Copy the path nodes
                    setInfinity(child.reducedMat, curr.vertexNum, child.vertexNum, child.visited); // Set the infinity in the matrix
                    child.totalCost = curr.totalCost + curr.reducedMat[curr.vertexNum][i] + reducedCost(child.reducedMat); // Calculate the total cost for the child

                    // Print the path, node, cost, and reduced matrix
                    cout << "Path: ";
                    displayPath(child.pathNodes, child.vertexNum);
                    cout << "\nNode: " << char('A' + child.vertexNum) << " Cost: " << child.totalCost << endl;
                    displayMatrix(child.reducedMat);

                    temp.insert({child.totalCost, child}); // Insert the child into the multimap

                    // If all vertices are visited
                    if (all_of(begin(child.visited), end(child.visited), [](bool v) { return v; })) {
                        child.pathNodes.push_back(child.vertexNum); // Add the last vertex to the path
                        if (child.totalCost < minCost) { // If the cost is less than the minimum cost
                            shortPath = child; // Update the shortest path
                            minCost = child.totalCost; // Update the minimum cost
                        }
                        found = true; // Mark the solution as found
                        break;
                    }
                }
            }
        }

        // If a valid path is found
        if (found) {
            cout << "Shortest Path : ";
            for (int i : shortPath.pathNodes) cout << char('A' + i) << " -> "; // Print the shortest path
            cout << "A\nTotal cost: " << minCost << endl; // Print the total cost
        } else {
            cout << "No valid path found!" << endl; // Print no valid path found
        }
    }
};

int main() {
    int adj[N][N] = {
        {INT_MAX, 5, 7, 3}, // Adjacency matrix representing the graph
        {2, INT_MAX, 4, 2},
        {5, 2, INT_MAX, 3},
        {4, 2, 3, INT_MAX}
    };

    TSP t; // Create an instance of the TSP class
    t.TSPsoln(adj,0);

    return 0;

}