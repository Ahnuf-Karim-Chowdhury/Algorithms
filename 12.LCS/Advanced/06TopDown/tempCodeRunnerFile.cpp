#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

// Memoization table
vector<vector<int>> memo;

// Function to recursively find LCS length
int lcsMemo(string& S1, string& S2, int m, int n) {
    // Base case: if either string is empty, LCS is 0
    if (m == 0 || n == 0)
        return 0;
    
    // If result for current state is already computed, return it
    if (memo[m][n] != -1)
        return memo[m][n];
    
    // If characters match, include in LCS
    if (S1[m - 1] == S2[n - 1])
        return memo[m][n] = 1 + lcsMemo(S1, S2, m - 1, n - 1);
    
    // If characters do not match, take maximum of excluding either character
    return memo[m][n] = max(lcsMemo(S1, S2, m - 1, n), lcsMemo(S1, S2, m, n - 1));
}

// Function to find and print LCS length and LCS itself using memoization
void findLCS(string S1, string S2) {
    int m = S1.length();
    int n = S2.length();
    
    // Initialize memoization table with -1 (indicating states are not computed yet)
    memo.assign(m + 1, vector<int>(n + 1, -1));
    
    // Compute LCS length using recursive function with memoization
    int length = lcsMemo(S1, S2, m, n);
    
    // Initialize string to store LCS sequence
    string lcs;
    
    // Build LCS sequence using memoization table
    int i = m, j = n;
    while (i > 0 && j > 0) {
        if (S1[i - 1] == S2[j - 1]) {
            lcs.push_back(S1[i - 1]);
            i--;
            j--;
        } else if (memo[i - 1][j] >= memo[i][j - 1]) { // Use >= instead of > for correct comparison
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
    
    // Print memoization table for visualization (optional)
    cout << "\nMemoization Table:\n";
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            cout << memo[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    string S1 = "10101";
    string S2 = "1001";
    
    // Call function to find LCS and print it
    findLCS(S1, S2);
    
    return 0;
}
