#include <iostream>
#include <vector>

#define N 4

using namespace std;

int solutionCount = 0;

void printSolution(vector<vector<int>> &board) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            if (board[i][j])
                cout << "Q ";
            else
                cout << ". ";
        cout << "\n";
    }
}

bool isSafe(vector<vector<int>> &board, int row, int col) {
    for (int i = 0; i < col; i++)
        if (board[row][i])
            return false;

    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j])
            return false;

    for (int i = row, j = col; j >= 0 && i < N; i++, j--)
        if (board[i][j])
            return false;

    return true;
}

bool solveNQUtil(vector<vector<int>> &board, int col) {
    if (col >= N) {
        solutionCount++;
        if (solutionCount == 2) {
            printSolution(board);
            return true; // Stop searching after finding the second solution
        }
        return false; // Continue searching for more solutions
    }

    for (int i = 0; i < N; i++) {
        if (isSafe(board, i, col)) {
            board[i][col] = 1;
            if (solveNQUtil(board, col + 1))
                return true;
            board[i][col] = 0;
        }
    }
    return false;
}

bool solveNQ() {
    vector<vector<int>> board(N, vector<int>(N, 0));
    if (solveNQUtil(board, 0) == false) {
        if (solutionCount < 2) {
            cout << "Less than two solutions exist";
        }
        return false;
    }
    return true;
}

int main() {
    solveNQ();
    return 0;
}
