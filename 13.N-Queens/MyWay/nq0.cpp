#include <bits/stdc++.h>
using namespace std;
vector<int>res;
bool isSafe(int r, int col, vector<int>& b) {
    for (int pr = 0; pr < r; pr++) {
        int pc = b[pr];
        if (pc == col || abs(pc - r) == abs(pc - col)) {
            return false;
        }
    }
    return true;
}

void solveNQueens(int r, int l, vector<int>& b) {
    if (r == l) {
        for (int i = 0; i < l; i++) {
            for (int j = 0; j < l; j++) {
                if (b[i] == j) {
                    res.push_back(j+1);
                } 
            }
        }
        return;
    }
    for (int col = 0; col < l; col++) {
        if (isSafe(r, col, b)) {
            b[r] = col;
            solveNQueens(r + 1, l, b);
        }
    }
}
void printNqueens(int l){
    for(int i=0;i<l;i++){
      cout<<res[i]<<" ";
    }
    cout<<endl;
}

int main() {
    int l = 4; 
    vector<int> b(l, 0);
    solveNQueens(0, l, b);
    printNqueens(l);
    return 0;
}
