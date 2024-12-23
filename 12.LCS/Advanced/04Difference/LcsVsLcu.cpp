#include <iostream>
#include <vector>
using namespace std;

pair<string, string> findLCSandLCSu(string S1, string S2, int m, int n, vector<vector<int>>& LCS_table) {
    // Variables to store LCS and LCSu
    string lcs;
    string lcsu;
    int max_length = 0;
    int end_index = 0;

    // Build LCS table
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (S1[i - 1] == S2[j - 1]) {
                LCS_table[i][j] = LCS_table[i - 1][j - 1] + 1;
                if (LCS_table[i][j] > max_length) {
                    max_length = LCS_table[i][j];
                    end_index = i - 1;
                }
            } else {
                LCS_table[i][j] = max(LCS_table[i - 1][j], LCS_table[i][j - 1]);
            }
        }
    }

    // Extract LCSu using the end index found
    if (max_length > 0) {
        lcsu = S1.substr(end_index - max_length + 1, max_length);
    }

    // Find LCS by tracing back the LCS table
    int i = m, j = n;
    while (i > 0 && j > 0) {
        if (S1[i - 1] == S2[j - 1]) {
            lcs = S1[i - 1] + lcs;
            i--;
            j--;
        } else if (LCS_table[i - 1][j] >= LCS_table[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }

    return {lcs, lcsu};
}

int main() {
    string S1 = "ABCDGH ABCDGH";
    string S2 = "AEDFHR ABCDGH";
    int m = S1.size();
    int n = S2.size();

    // Create LCS table
    vector<vector<int>> LCS_table(m + 1, vector<int>(n + 1, 0));

    // Find LCS and LCSu
    auto result = findLCSandLCSu(S1, S2, m, n, LCS_table);
    string lcs = result.first;
    string lcsu = result.second;

    // Output results
    cout << "Longest Common Subsequence (LCS): " << lcs << ", Length: " << lcs.size() << endl;
    cout << "Longest Common Substring (LCSu): " << lcsu << ", Length: " << lcsu.size() << endl;

    return 0;
}
