#include <bits/stdc++.h>
using namespace std;

void buildLCSTable(string S1, string S2, int m, int n, int LCS_table[][100]) {
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0)
                LCS_table[i][j] = 0;
            else if (S1[i - 1] == S2[j - 1])
                LCS_table[i][j] = LCS_table[i - 1][j - 1] + 1;
            else
                LCS_table[i][j] = max(LCS_table[i - 1][j], LCS_table[i][j - 1]);
                cout<<LCS_table[i][j]<<" ";
        }
        cout<<"\n";
    }
}

void findLCS(string S1, string S2, int i, int j, int LCS_table[][100], int k, string currentLCS, set<string>& validLCS) {
    if (i == 0 || j == 0) {
        if (currentLCS.length() >= k) {
            validLCS.insert(currentLCS);
        }
        return;
    }

    if (S1[i - 1] == S2[j - 1]) {
        findLCS(S1, S2, i - 1, j - 1, LCS_table, k, S1[i - 1] + currentLCS, validLCS);
    } else if (LCS_table[i - 1][j] > LCS_table[i][j - 1]) {
        findLCS(S1, S2, i - 1, j, LCS_table, k, currentLCS, validLCS);
    } else if (LCS_table[i][j - 1] > LCS_table[i - 1][j]) {
        findLCS(S1, S2, i, j - 1, LCS_table, k, currentLCS, validLCS);
    } else {
        findLCS(S1, S2, i - 1, j, LCS_table, k, currentLCS, validLCS);
        findLCS(S1, S2, i, j - 1, LCS_table, k, currentLCS, validLCS);
    }
}

void lcsAlgo(string S1, string S2, int m, int n, int k) {
    int LCS_table[100][100];
    buildLCSTable(S1, S2, m, n, LCS_table);
    int lcsLength = LCS_table[m][n];
    
    // Set to store valid LCS of length >= k
    set<string> validLCS;
    
    // Find all LCS of length >= k
    findLCS(S1, S2, m, n, LCS_table, k, "", validLCS);
    
    if (validLCS.empty()) {
        cout << "No subsequences found with length at least " << k << ".\n";
    } else {
        cout << "Length of LCS with length at least " << k << ": " << lcsLength << '\n';
        cout << "Subsequences with length at least " << k << ":\n";
        for (const auto& lcs : validLCS) {
            cout << lcs << '\n';
        }
    }
}

int main() {
    string S1 = "AGGTAB";
    string S2 = "GXTXAYB";
    int m = S1.size();
    int n = S2.size();
    int k = 4; // Minimum length of LCS required
    
    lcsAlgo(S1, S2, m, n, k);
    
    return 0;
}
