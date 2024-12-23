#include <bits/stdc++.h>
using namespace std;

void buildLCSTable(string S1, string S2, int m, int n, vector<vector<int>>& LCS_table) {
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0)
                LCS_table[i][j] = 0;
            else if (S1[i - 1] == S2[j - 1])
                LCS_table[i][j] = LCS_table[i - 1][j - 1] + 1;
            else
                LCS_table[i][j] = max(LCS_table[i - 1][j], LCS_table[i][j - 1]);
        }
    }
}

string findLCS(string S1, string S2, int i, int j, vector<vector<int>>& LCS_table) {
    if (i == 0 || j == 0)
        return "";

    if (S1[i - 1] == S2[j - 1]) {
        return findLCS(S1, S2, i - 1, j - 1, LCS_table) + S1[i - 1];
    } else if (LCS_table[i - 1][j] > LCS_table[i][j - 1]) {
        return findLCS(S1, S2, i - 1, j, LCS_table);
    } else {
        return findLCS(S1, S2, i, j - 1, LCS_table);
    }
}

pair<int, string> longestPalindromicSubsequence(string S) {
    string reverseS = S;
    reverse(reverseS.begin(), reverseS.end());
    int m = S.size();
    int n = reverseS.size();

    vector<vector<int>> LCS_table(m + 1, vector<int>(n + 1));
    buildLCSTable(S, reverseS, m, n, LCS_table);

    // The length of the longest palindromic subsequence is the LCS of S and reverseS
    int lpsLength = LCS_table[m][n];
    string lps = findLCS(S, reverseS, m, n, LCS_table);
    return {lpsLength, lps};
}

int main() {
    string S = "BBABCBCAB";
    auto result = longestPalindromicSubsequence(S);
    cout << "Length of the longest palindromic subsequence: " << result.first << '\n';
    cout << "Longest palindromic subsequence: " << result.second << '\n';
    
    return 0;
}
