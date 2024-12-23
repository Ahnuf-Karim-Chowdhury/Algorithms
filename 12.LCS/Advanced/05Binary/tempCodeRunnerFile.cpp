#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

// Function to find and print LCS length and LCS itself
void findLCS(string S1, string S2) {
    int m = S1.length();
    int n = S2.length();
    
    // Create a 2D array to store lengths of LCS
    int LCS_table[m + 1][n + 1];
    
    // Build LCS_table in bottom up fashion
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0)
                LCS_table[i][j] = 0;
            else if (S1[i - 1] == S2[j - 1])
                LCS_table[i][j] = LCS_table[i - 1][j - 1] + 1;
            else
                LCS_table[i][j] = max(LCS_table[i - 1][j], LCS_table[i][j - 1]);
        }
    }
    
    // LCS length is the value in the bottom-right corner of LCS_table
    int length = LCS_table[m][n];
    
    // Initialize string to store LCS sequence
    string lcs;
    
    // Traverse LCS_table to find LCS sequence
    int i = m, j = n;
    while (i > 0 && j > 0) {
        if (S1[i - 1] == S2[j - 1]) {
            lcs.push_back(S1[i - 1]);
            i--;
            j--;
        } else if (LCS_table[i - 1][j] > LCS_table[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }
    
    // Reverse the string to get the actual LCS sequence
    reverse(lcs.begin(), lcs.end());
    
    // Print LCS length and LCS sequence
    cout << "Length of Longest Common Subsequence: " << length << endl;
    cout << "Longest Common Subsequence: " << lcs << endl;
}

int main() {
    string S1 = "10101";
    string S2 = "1001";
    
    // Call function to find LCS and print it
    findLCS(S1, S2);
    
    return 0;
}
