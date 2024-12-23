#include <bits/stdc++.h>
using namespace std;

int main() {
    int n = 4, m = 4;
    vector<int> s1 = {0, 1,2,1};
    vector<int> s2 = {0, 1, 2, 3};
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

    int t = m - 1; 
    for(int i = 1; i < n && t > 0; i++) {
        if(t >= s1[i] &&  c[i][i] == 1) {
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
