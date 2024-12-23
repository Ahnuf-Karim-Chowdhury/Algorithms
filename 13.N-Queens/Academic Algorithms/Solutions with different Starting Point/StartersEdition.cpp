#include <bits/stdc++.h>
using namespace std;

vector<int> res;
set<int> startingPositions; // Set to keep track of starting positions of solutions

bool Place(int k, int i) {
    for (int j = 1; j < k; j++) {
        if (res[j] == i || abs(res[j] - i) == abs(j - k)) {
            return false;
        }
    }
    return true;
}

void NQueens(int k, int n) {
    for (int i = 1; i <= n; i++) {
        if (Place(k, i)) {
            res[k] = i;
            if (k == n) {
                if (startingPositions.find(res[1]) == startingPositions.end()) {
                    startingPositions.insert(res[1]);
                    for (int l = 1; l <= n; l++) {
                        cout << res[l] << " ";
                    }
                    cout << endl;
                }
            } else {
                NQueens(k + 1, n);
            }
        }
    }
}

int main() {
    int n;
    cout << "Enter the number of queens: ";
    cin >> n;

    res.resize(n + 1);

    NQueens(1, n);

    return 0;
}
