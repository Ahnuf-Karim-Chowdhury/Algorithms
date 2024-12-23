#include <iostream>
#include <vector>

#define n 4

using namespace std;
vector<int>res;
void printSolution(vector<vector<int>> &board) {
    res.clear();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            if (board[i][j])
                res.push_back(j+1);
    }
}

bool isSafe(vector<vector<int>> &board, int row, int col) {
    for (int i = 0; i < col; i++)
        if (board[row][i])
            return false;

    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j])
            return false;

    for (int i = row, j = col; j >= 0 && i < n; i++, j--)
        if (board[i][j])
            return false;

    return true;
}

bool solveNQUtil(vector<vector<int>> &board, int col) {
    if (col >= n)
        return true;

    for (int i = 0; i < n; i++) {
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
    vector<vector<int>> board(n, vector<int>(n, 0));
    if (solveNQUtil(board, 0) == false) {
        cout << "Solution does not exist";
        return false;
    }
    printSolution(board);
    return true;
}

int main() {
    solveNQ();
    cout<<endl;
    for (int i=res.size()-1;i>=0;i--){
        cout<<res[i]<<" ";
    }
    return 0;
}
