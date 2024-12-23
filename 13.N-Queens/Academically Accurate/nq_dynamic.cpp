#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> res;

void solve(int n, int r, int ld, int rd, vector<int>& q) {
    if (r == (1 << n) - 1) {
        res.push_back(q);
        return;
    }
    
    int pos = ~(r | ld | rd) & ((1 << n) - 1);
    while (pos) {
        int p = pos & -pos;
        pos -= p;
        int col = __builtin_ctz(p);
        q.push_back(col + 1);
        solve(n, r | p, (ld | p) << 1, (rd | p) >> 1, q);
        q.pop_back();
    }
}

void printSolutions(int n) {
    int c = 1;
    for (const auto& i : res) {
        cout << "Solution " << c++ << " :" << endl;
        cout << "[ ";
        for (int q : i) {
            cout << q << " ";
        }
        cout << "]" << endl;
    }
}

int main() {
    int n = 4;
    vector<int> q;
    solve(n, 0, 0, 0, q);
    printSolutions(n);
    if (res.empty()) {
        cout << "No solution possible for " << n << " q." << endl;
    }
    return 0;
}
