#include <bits/stdc++.h>
using namespace std;

// Function to find all common subsequences
void findAllCommonSubsequences(vector<vector<int>>& LCS_table, string& S1, string& S2, int i, int j, string currentSubseq, set<string>& allSubseq)
{
    // Base case: If we have reached the end of either string
    if (i == 0 || j == 0)
    {
        if (!currentSubseq.empty())
        {
            reverse(currentSubseq.begin(), currentSubseq.end());
            allSubseq.insert(currentSubseq);
        }
        return;
    }

    // If characters match, add this character to the current subsequence and move diagonally up in the LCS table
    if (S1[i - 1] == S2[j - 1])
    {
        currentSubseq.push_back(S1[i - 1]);
        findAllCommonSubsequences(LCS_table, S1, S2, i - 1, j - 1, currentSubseq, allSubseq);
    }

    // Move in the direction of the greater value in the LCS table to ensure we explore all possible subsequences
    findAllCommonSubsequences(LCS_table, S1, S2, i - 1, j, currentSubseq, allSubseq);
    findAllCommonSubsequences(LCS_table, S1, S2, i, j - 1, currentSubseq, allSubseq);
}

void lcsAlgo(string S1, string S2, int m, int n)
{
    vector<vector<int>> LCS_table(m + 1, vector<int>(n + 1, 0));

    // Building the matrix in bottom-up way
    for (int i = 0; i <= m; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            if (i == 0 || j == 0)
                LCS_table[i][j] = 0;
            else if (S1[i - 1] == S2[j - 1])
                LCS_table[i][j] = LCS_table[i - 1][j - 1] + 1;
            else
                LCS_table[i][j] = max(LCS_table[i - 1][j], LCS_table[i][j - 1]);
        }
    }

    set<string> allSubseq;
    findAllCommonSubsequences(LCS_table, S1, S2, m, n, "", allSubseq);

    // Printing all common subsequences
    cout << "All common subsequences: \n";
    for (const auto& subseq : allSubseq)
    {
        cout << subseq << "\n";
    }
}

int main()
{
    string S1 = "ACADB";
    string S2 = "CBDA";
    int m = S1.size();
    int n = S2.size();

    lcsAlgo(S1, S2, m, n);
    return 0;
}
