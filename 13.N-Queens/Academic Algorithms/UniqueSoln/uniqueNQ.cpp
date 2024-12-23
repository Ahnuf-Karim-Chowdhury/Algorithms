#include <bits/stdc++.h>
using namespace std;

vector<int> res;
set<vector<int>> uniqueSolutions; // Set to store unique solutions

bool Place(int k, int i) {
    for (int j = 1; j < k; j++) {
        if (res[j] == i || abs(res[j] - i) == abs(j - k)) {
            return false;
        }
    }
    return true;
}

vector<int> rotate90(vector<int> board) {
    int n = board.size();
    vector<int> rotated(n);
    for (int i = 0; i < n; i++) {
        rotated[board[i] - 1] = n - i;
    }
    return rotated;
}

vector<int> reflect(vector<int> board) {
    int n = board.size();
    vector<int> reflected(n);
    for (int i = 0; i < n; i++) {
        reflected[i] = n + 1 - board[i];
    }
    return reflected;
}

bool isUnique(vector<int> board) {
    vector<int> rotated90 = rotate90(board);
    vector<int> rotated180 = rotate90(rotated90);
    vector<int> rotated270 = rotate90(rotated180);
    vector<int> reflected = reflect(board);
    vector<int> reflectedRotated90 = rotate90(reflected);
    vector<int> reflectedRotated180 = rotate90(reflectedRotated90);
    vector<int> reflectedRotated270 = rotate90(reflectedRotated180);

    return uniqueSolutions.find(rotated90) == uniqueSolutions.end() &&
           uniqueSolutions.find(rotated180) == uniqueSolutions.end() &&
           uniqueSolutions.find(rotated270) == uniqueSolutions.end() &&
           uniqueSolutions.find(reflected) == uniqueSolutions.end() &&
           uniqueSolutions.find(reflectedRotated90) == uniqueSolutions.end() &&
           uniqueSolutions.find(reflectedRotated180) == uniqueSolutions.end() &&
           uniqueSolutions.find(reflectedRotated270) == uniqueSolutions.end();
}

void NQueens(int k, int n) {
    for (int i = 1; i <= n; i++) {
        if (Place(k, i)) {
            res[k] = i;
            if (k == n) {
                vector<int> solution(res.begin() + 1, res.end());
                if (isUnique(solution)) {
                    uniqueSolutions.insert(solution);
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
