#include <bits/stdc++.h>
using namespace std;

void lcsAlgo(string S1, string S2, string S3, int m, int n, int o)
{
    int LCS_table[m + 1][n + 1][o + 1];

    // Building the 3D matrix in bottom-up way
    for (int i = 0; i <= m; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            for (int k = 0; k <= o; k++)
            {
                if (i == 0 || j == 0 || k == 0)
                    LCS_table[i][j][k] = 0;
                else if (S1[i - 1] == S2[j - 1] && S1[i - 1] == S3[k - 1])
                    LCS_table[i][j][k] = LCS_table[i - 1][j - 1][k - 1] + 1;
                else
                    LCS_table[i][j][k] = max({LCS_table[i - 1][j][k], LCS_table[i][j - 1][k], LCS_table[i][j][k - 1]});
            }
        }
    }

    int index = LCS_table[m][n][o];
    cout << "LCS Length: " << index << '\n';

    string lcs;
    int i = m, j = n, k = o;
    while (i > 0 && j > 0 && k > 0)
    {
        if (S1[i - 1] == S2[j - 1] && S1[i - 1] == S3[k - 1])
        {   
            lcs.push_back(S1[i - 1]);
            i--;
            j--;
            k--;
        }
        else if (LCS_table[i - 1][j][k] >= LCS_table[i][j - 1][k] && LCS_table[i - 1][j][k] >= LCS_table[i][j][k - 1])
            i--;
        else if (LCS_table[i][j - 1][k] >= LCS_table[i - 1][j][k] && LCS_table[i][j - 1][k] >= LCS_table[i][j][k - 1])
            j--;
        else
            k--;
    }

    // Printing the subsequence
    cout << "LCS: " << string(rbegin(lcs), rend(lcs)) << "\n";
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
