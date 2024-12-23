#include <bits/stdc++.h>
using namespace std;

int main() {
    int n = 4, m = 5;
    vector<int> s1 = {2, 1, 4, 3};  
    vector<int> s2 = {1, 2, 3, 4, 5};  
    vector<vector<bool>> c(n + 1, vector<bool>(m + 1, false)); 

    for (int i = 0; i <= n; i++) {
        c[i][0] = true;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            c[i][j] = c[i-1][j];

            if (j - s1[i-1] >= 0 && c[i-1][j - s1[i-1]]) {
                c[i][j] = true;
            }
        }
    }

    for(int i = 0; i <= n; i++){
        for(int j = 0; j <= m; j++){
            cout << c[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
