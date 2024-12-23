#include <bits/stdc++.h>
#include <cstring>
using namespace std;

void lcsAlgo(string S1, string S2, int m, int n)
{
    int LCS_table[m + 1][n + 1];

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
                cout<<LCS_table[i][j]<<" ";
        }
        cout<<"\n";
    }

    int index = LCS_table[m][n];
    cout << "LCS Length: " << index << '\n';

    string lcs;
    int i = m, j = n;
    while (i > 0 && j > 0)
    {
        if (S1[i - 1] == S2[j - 1])
        {   
            lcs.push_back(S1[i - 1]);
            i--;
            j--;
        }
        else if (LCS_table[i - 1][j] > LCS_table[i][j - 1])
            i--;
        else
            j--;
    }

    // Printing the subsequence
    cout << "LCS: " << string(rbegin(lcs), rend(lcs)) << "\n";
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