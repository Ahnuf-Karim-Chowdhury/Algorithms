#include <bits/stdc++.h>
using namespace std;

int main() {
    int n = 5, m = 6;
    vector<int> s1 = {0, 2, 1, 4, 3};
    vector<int> s2 = {0, 1, 2, 3, 4, 5};
    vector<vector<int>> c(n, vector<int>(m, 0)); 
    vector<int> res;

    for (int i = 0; i < n; i++) { 
        c[i][0] = 1;
    }

    for(int i = 1; i < n; i++){
        for(int j = 1; j < m; j++){
            if(c[i-1][j] == 1){
                c[i][j] = 1;
            }
            if(c[i][j] == 0){
                int diff = abs(s1[i] - s2[j]);
                if(diff < m && c[i-1][diff] == 1){
                    c[i][j] = 1;
                }
            }
        }
    }
    
    // Collect sums of subsets that satisfy the conditions
    for(int j = 1; j < m; j++){
        if(c[n-1][j] == 0){
            int sum = 0;
            int current_j = j;
            for(int i = n-1; i >= 0; i--){
                if(current_j >= s1[i]){
                    if(i == 0 && current_j == s1[i]){
                        sum += s1[i];
                        res.push_back(sum);
                        break;
                    }
                    if(c[i-1][current_j-s1[i]] == 1){
                        sum += s1[i];
                        current_j = current_j - s1[i];
                    }
                }
            }
        }
    }

    // Output the dynamic programming table
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cout << c[i][j] << " ";
        }
        cout << endl;
    }
    cout<< "\nThe Solution : ";
    for(int i=0;i<res.size();i++){
        cout<<res[i]<<" ";
    }

    return 0;
}
