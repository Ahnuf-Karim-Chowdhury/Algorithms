#include <bits/stdc++.h>
using namespace std;
vector<vector<int>> res;

bool isSafe(int r, int col, vector<int>& b) {
    for (int pr = 0; pr < r; pr++) {
        int pc = b[pr];
        if (pc == col || abs(pc - col) == abs(pr - r)) {
            return false;
        }
    }
    return true;
}

void solveNQueens(int r, int l, vector<int>& b) {
    if (r == l) {
        res.push_back(b);
        return;
    }
    for (int col = 0; col < l; col++) {
        if (isSafe(r, col, b)) {
            b[r] = col;
            solveNQueens(r + 1, l, b);
        }
    }
}

void printNQueens(int l) {
    for (const auto& r : res) {
        for (int i = 0; i < l; i++) {
            cout << r[i] + 1 << " ";
        }
        cout << endl;
    }
}

int main() {
    int l;
    cout << "Enter the size of the board: ";
    cin >> l;
    vector<int> b(l, 0);
    solveNQueens(0, l, b);
    printNQueens(l);
    return 0;
}
