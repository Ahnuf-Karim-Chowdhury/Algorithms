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

string findLCS(string S1, string S2, int m, int n, int LCS_table[][100]) {
    string lcs = "";
    vector<string> steps;
    int i = m, j = n;

    while (i > 0 && j > 0) {
        if (S1[i - 1] == S2[j - 1]) {
            lcs = S1[i - 1] + lcs;
            steps.push_back("D (" + string(1, S1[i - 1]) + ")      {LCS Table Index: (" + to_string(i) + ", " + to_string(j) + "), LCS: " + lcs + "}");
            i--;
            j--;
        } else if (LCS_table[i - 1][j] > LCS_table[i][j - 1]) {
            steps.push_back("Up      {LCS Table Index: (" + to_string(i) + ", " + to_string(j) + "), LCS: " + lcs + "}");
            i--;
        } else {
            steps.push_back("L      {LCS Table Index: (" + to_string(i) + ", " + to_string(j) + "), LCS: " + lcs + "}");
            j--;
        }
    }

    reverse(steps.begin(), steps.end());
    for (const auto& step : steps) {
        cout << step << "\n";
    }

    return lcs;
}

void lcsAlgo(string S1, string S2, int m, int n) {
    int LCS_table[100][100];
    buildLCSTable(S1, S2, m, n, LCS_table);
    int index = LCS_table[m][n];
    cout << "LCS Length: " << index << '\n';
    string lcs = findLCS(S1, S2, m, n, LCS_table);
    cout << "LCS: " << lcs << "\n";
}

int main() {
    string S1 = "ACADB";
    string S2 = "CBDA";
    int m = S1.size();
    int n = S2.size();
    lcsAlgo(S1, S2, m, n);
    return 0;
}