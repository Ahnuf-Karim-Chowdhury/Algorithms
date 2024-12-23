#include <bits/stdc++.h>
using namespace std;

void findAllLCS(vector<vector<vector<int>>>& LCS_table, string& S1, string& S2, string& S3, int i, int j, int k, string currentLCS, set<string>& allLCS)
{
    // Base case: If we have reached the end of any string
    if (i == 0 || j == 0 || k == 0)
    {
        if (!currentLCS.empty() && currentLCS.length() == LCS_table[S1.size()][S2.size()][S3.size()])
        {
            reverse(currentLCS.begin(), currentLCS.end());
            allLCS.insert(currentLCS);
        }
        return;
    }

    // If characters match, add this character to the current LCS and move diagonally up in the LCS table
    if (S1[i - 1] == S2[j - 1] && S1[i - 1] == S3[k - 1])
    {
        currentLCS.push_back(S1[i - 1]);
        findAllLCS(LCS_table, S1, S2, S3, i - 1, j - 1, k - 1, currentLCS, allLCS);
        currentLCS.pop_back(); // Backtrack to explore other paths
    }
}

void lcsAlgo(string S1, string S2, string S3, int m, int n, int o)
{
    vector<vector<vector<int>>> LCS_table(m + 1, vector<vector<int>>(n + 1, vector<int>(o + 1, 0)));

    // Building the 3D matrix in bottom-up way
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            for (int k = 1; k <= o; k++)
            {
                if (S1[i - 1] == S2[j - 1] && S1[i - 1] == S3[k - 1])
                    LCS_table[i][j][k] = LCS_table[i - 1][j - 1][k - 1] + 1;
                else
                    LCS_table[i][j][k] = max({LCS_table[i - 1][j][k], LCS_table[i][j - 1][k], LCS_table[i][j][k - 1]});
            }
        }
    }

    int maxLength = LCS_table[m][n][o];

    set<string> allLCS;
    // Find all common substrings of maximum length
    for (int i = m; i > 0; i--)
    {
        for (int j = n; j > 0; j--)
        {
            for (int k = o; k > 0; k--)
            {
                if (LCS_table[i][j][k] == maxLength && S1[i - 1] == S2[j - 1] && S1[i - 1] == S3[k - 1])
                {
                    string lcs;
                    int x = i, y = j, z = k;
                    while (x > 0 && y > 0 && z > 0 && LCS_table[x][y][z] > 0)
                    {
                        lcs.push_back(S1[x - 1]);
                        x--;
                        y--;
                        z--;
                    }
                    reverse(lcs.begin(), lcs.end());
                    allLCS.insert(lcs);
                }
            }
        }
    }

    // Printing all longest common substrings
    cout << "Maximum Length of Common Substring: " << maxLength << '\n';
    cout << "All longest common substrings of max length: \n";
    for (const auto& lcs : allLCS)
    {
        cout << lcs << "\n";
    }
}

int main()
{
    string S1 = "ACADB";
    string S2 = "CBDAD";
    string S3 = "BDABD";
    int m = S1.size();
    int n = S2.size();
    int o = S3.size();

    lcsAlgo(S1, S2, S3, m, n, o);
    return 0;
}
