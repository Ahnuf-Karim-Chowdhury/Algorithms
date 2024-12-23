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

void findAllLCS(string S1, string S2, int m, int n, int LCS_table[][100], set<string>& allLCS) {
    queue<tuple<int, int, string>> q;
    q.push(make_tuple(m, n, ""));
    
    while (!q.empty()) {
        auto [i, j, lcs] = q.front();
        q.pop();

        if (i == 0 || j == 0) {
            reverse(lcs.begin(), lcs.end());
            allLCS.insert(lcs);
            continue;
        }

        if (S1[i - 1] == S2[j - 1]) {
            q.push(make_tuple(i - 1, j - 1, lcs + S1[i - 1]));
        } else {
            if (LCS_table[i - 1][j] >= LCS_table[i][j - 1]) {
                q.push(make_tuple(i - 1, j, lcs));
            }
            if (LCS_table[i][j - 1] >= LCS_table[i - 1][j]) {
                q.push(make_tuple(i, j - 1, lcs));
            }
        }
    }
}

void lcsAlgo(string S1, string S2, int m, int n) {
    int LCS_table[100][100];
    buildLCSTable(S1, S2, m, n, LCS_table);
    int index = LCS_table[m][n];
    cout << "LCS Length: " << index << '\n';

    set<string> allLCS;
    findAllLCS(S1, S2, m, n, LCS_table, allLCS);

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
