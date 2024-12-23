#include <bits/stdc++.h>
#include <cstring>
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
            cout << LCS_table[i][j] << " ";
        }
        cout << "\n";
    }
}

void findAllLCSHelper(string S1, string S2, int i, int j, int LCS_table[][100], string lcs, set<string>& allLCS) {
    if (i == 0 || j == 0) {
        reverse(lcs.begin(), lcs.end());
        allLCS.insert(lcs);
        return;
    }

    if (S1[i - 1] == S2[j - 1]) {
        findAllLCSHelper(S1, S2, i - 1, j - 1, LCS_table, lcs + S1[i - 1], allLCS);
    } else {
        if (LCS_table[i - 1][j] >= LCS_table[i][j - 1]) {
            findAllLCSHelper(S1, S2, i - 1, j, LCS_table, lcs, allLCS);
        }
        if (LCS_table[i][j - 1] >= LCS_table[i - 1][j]) {
            findAllLCSHelper(S1, S2, i, j - 1, LCS_table, lcs, allLCS);
        }
    }
}

void lcsAlgo(string S1, string S2, int m, int n) {
    int LCS_table[100][100];
    buildLCSTable(S1, S2, m, n, LCS_table);
    int index = LCS_table[m][n];
    cout << "LCS Length: " << index << '\n';

    set<string> allLCS;
    findAllLCSHelper(S1, S2, m, n, LCS_table, "", allLCS);

    for (const auto& lcs : allLCS) {
        cout << "LCS: " << lcs << "\n";
    }
}

int main() {
    string S1 = "ACADB";
    string S2 = "CBDA";
    int m = S1.size();
    int n = S2.size();
    lcsAlgo(S1, S2, m, n);
    return 0;
}
