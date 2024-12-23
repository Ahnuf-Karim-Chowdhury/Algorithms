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

void findAllLCSHelper(string S1, string S2, int i, int j, int LCS_table[][100], string lcs, vector<string>& steps, set<string>& allLCS) {
    if (i == 0 || j == 0) {
        reverse(lcs.begin(), lcs.end());
        allLCS.insert(lcs);
        for (const auto& step : steps) {
            cout << step << "\n";
        }
        cout << "LCS: " << lcs << "\n";
        return;
    }

    if (S1[i - 1] == S2[j - 1]) {
        steps.push_back("D (" + string(1, S1[i - 1]) + ") {LCS Table Index: (" + to_string(i) + ", " + to_string(j) + "), LCS: " + lcs + S1[i - 1] + "}");
        findAllLCSHelper(S1, S2, i - 1, j - 1, LCS_table, lcs + S1[i - 1], steps, allLCS);
        steps.pop_back();
    } else {
        if (LCS_table[i - 1][j] >= LCS_table[i][j - 1]) {
            steps.push_back("Up {LCS Table Index: (" + to_string(i) + ", " + to_string(j) + "), LCS: " + lcs + "}");
            findAllLCSHelper(S1, S2, i - 1, j, LCS_table, lcs, steps, allLCS);
            steps.pop_back();
        }
        if (LCS_table[i][j - 1] >= LCS_table[i - 1][j]) {
            steps.push_back("L {LCS Table Index: (" + to_string(i) + ", " + to_string(j) + "), LCS: " + lcs + "}");
            findAllLCSHelper(S1, S2, i, j - 1, LCS_table, lcs, steps, allLCS);
            steps.pop_back();
        }
    }
}

void lcsAlgo(string S1, string S2, int m, int n) {
    int LCS_table[100][100];
    buildLCSTable(S1, S2, m, n, LCS_table);
    int index = LCS_table[m][n];
    cout << "LCS Length: " << index << '\n';

    set<string> allLCS;
    vector<string> steps;
    findAllLCSHelper(S1, S2, m, n, LCS_table, "", steps, allLCS);
}

int main() {
    string S1 = "ACADB";
    string S2 = "CBDA";
    int m = S1.size();
    int n = S2.size();
    lcsAlgo(S1, S2, m, n);
    return 0;
}
