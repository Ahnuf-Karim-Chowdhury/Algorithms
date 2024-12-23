#include <bits/stdc++.h>
using namespace std;

int main() {
    int n = 5, m = 6;
    vector<int> s1 = {0, 2, 1, 4, 3};
    vector<int> s2 = {0, 1, 2, 3, 4, 5};
    vector<vector<int>> c(n, vector<int>(m, 0)); 
    vector<int> res;

    // Initialize DP table
    for (int i = 0; i < n; i++) { 
        c[i][0] = 1;
    }

    // Fill DP table
    for(int i = 1; i < n; i++){
        for(int j = 0; j < m; j++){
            if(c[i-1][j] == 1){
                c[i][j] = 1;
                if(j + s1[i] < m) {
                    c[i][j + s1[i]] = 1;
                }
            }
        }
    }

    // Forward search to find the subset whose sum is the target value
    int t = m - 1; 
    for(int i = n - 1; i >= 0 && t > 0; i--) {
        if(t >= s1[i] && c[i][t] == 1) {
            res.push_back(s1[i]);
            t -= s1[i];
        }
    }

    // Output the dynamic programming table
    cout << "DP Table:\n";
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cout << c[i][j] << " ";
        }
        cout << endl;
    }

    // Output the solution
    cout << "\nThe Solution : ";
    for(int i = 0; i < res.size(); i++) {
        cout << res[i] << " ";
    }
    cout << endl;

    return 0;
}
