#include <iostream>
#include <vector>

#define N 4

using namespace std;

void printSolution(vector<vector<int>> &board) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            if (board[i][j])
                cout << "Q ";
            else
                cout << ". ";
        cout << "\n";
    }
    cout << "\n";
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

void solveNQUtil(vector<vector<int>> &board, int col) {
    if (col >= N) {
        printSolution(board);
        return;
    }

    for (int i = 0; i < N; i++) {
        if (isSafe(board, i, col)) {
            board[i][col] = 1;
            solveNQUtil(board, col + 1);
            board[i][col] = 0;
        }
    }
}

void solveNQ() {
    vector<vector<int>> board(N, vector<int>(N, 0));
    solveNQUtil(board, 0);
}

int main() {
    solveNQ();
    return 0;
}
