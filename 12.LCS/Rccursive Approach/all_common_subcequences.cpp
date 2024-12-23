#include <bits/stdc++.h>
using namespace std;

// Function to find all LCS
void findAllLCS(vector<vector<int>>& LCS_table, string& S1, string& S2, int i, int j, string currentLCS, set<string>& allLCS)
{
    // Base case: If we have reached the end of either string
    if (i == 0 || j == 0)
    {
        reverse(currentLCS.begin(), currentLCS.end());
        allLCS.insert(currentLCS);
        return;
    }

    // If characters match, add this character to the current LCS and move diagonally up in the LCS table
    if (S1[i - 1] == S2[j - 1])
    {
        currentLCS.push_back(S1[i - 1]);
        findAllLCS(LCS_table, S1, S2, i - 1, j - 1, currentLCS, allLCS);
    }
    else
    {
        // Move in the direction of the greater value in the LCS table to ensure we explore all possible LCS
        if (LCS_table[i - 1][j] >= LCS_table[i][j - 1])
        {
            findAllLCS(LCS_table, S1, S2, i - 1, j, currentLCS, allLCS);
        }

        if (LCS_table[i][j - 1] >= LCS_table[i - 1][j])
        {
            findAllLCS(LCS_table, S1, S2, i, j - 1, currentLCS, allLCS);
        }
    }
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

    int index = LCS_table[m][n];
    cout << "LCS Length: " << index << '\n';

    set<string> allLCS;
    findAllLCS(LCS_table, S1, S2, m, n, "", allLCS);

    // Printing all common subsequences
    cout << "All LCS: \n";
    for (const auto& lcs : allLCS)
    {
        cout << lcs << "\n";
    }

    cout << "Number of distinct LCS: " << allLCS.size() << "\n";
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
