#include <bits/stdc++.h>
using namespace std;

string findLCS(string S1, string S2, int m, int n, vector<vector<int>>& LCS_table) {
    int i = m, j = n;
    string lcs;
    
    while (i > 0 && j > 0) {
        if (S1[i - 1] == S2[j - 1]) {
            lcs = S1[i - 1] + lcs;
            i--;
            j--;
        } else if (LCS_table[i - 1][j] > LCS_table[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }
    
    return lcs;
}

string longestCommonSubsequence(string S1, string S2, char start, char end) {
    int m = S1.size();
    int n = S2.size();
    
    vector<vector<int>> LCS_table(m + 1, vector<int>(n + 1, 0));
    
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if(i==0||j==0){
                LCS_table[i][j]=0;
            }
            if (S1[i - 1] == S2[j - 1]) {
                LCS_table[i][j] = LCS_table[i - 1][j - 1] + 1;
            } else {
                LCS_table[i][j] = max(LCS_table[i - 1][j], LCS_table[i][j - 1]);
            }
            cout<<LCS_table[i][j]<<" ";
        }
        cout<<"\n";
    }
    
    string lcs = findLCS(S1, S2, m, n, LCS_table);
    
    // Check if LCS starts and ends with the given characters
    if (!lcs.empty() && lcs[0] == start && lcs.back() == end) {
        return lcs;
    } else {
        return "No common subsequence found.";
    }
}

int main() {
    string S1 = "ABCDGH";
    string S2 = "AEDFHR";
    char start = 'A';
    char end = 'H';
    
    string result = longestCommonSubsequence(S1, S2, start, end);
    cout << "Longest common subsequence that starts with '" << start << "' and ends with '" << end << "': " << result << endl;
    
    return 0;
}
