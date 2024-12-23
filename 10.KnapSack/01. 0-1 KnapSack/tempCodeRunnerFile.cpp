#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Utility function to print the selected items
void printSelectedItems(vector<int>& selectedItems, vector<int>& wt, vector<int>& val) {
    cout << "Selected items: ";
    bool first = true;
    for (int i = 0; i < selectedItems.size(); ++i) {
        if (selectedItems[i] == 1) {
            if (!first) {
                cout << ", ";
            }
            cout << "(weight=" << wt[i] << ", profit=" << val[i] << ")";
            first = false;
        }
    }
    cout << endl;
}

int knapSack(int W, vector<int> wt, vector<int> val, int n, vector<int>& selectedItems)
{
    // Initialize a 2D vector to store the maximum profit for each item up to the given weight
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

    // Build dp table
    for (int i = 1; i <= n; ++i) {
        for (int w = 1; w <= W; ++w) {
            if (wt[i - 1] <= w) {
                dp[i][w] = max(val[i - 1] + dp[i - 1][w - wt[i - 1]], dp[i - 1][w]);
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    // Trace back to find selected items
    int maxProfit = dp[n][W];
    int remainingWeight = W;
    for (int i = n; i > 0 && maxProfit > 0; --i) {
        if (maxProfit != dp[i - 1][remainingWeight]) {
            selectedItems[i - 1] = 1;
            maxProfit -= val[i - 1];
            remainingWeight -= wt[i - 1];
        }
    }

    return dp[n][W];
}

int main()
{
    vector<int> profit = {9, 7, 10, 7};
    vector<int> weight = {2, 3, 4, 8};
    int W = 7;
    int n = profit.size();
    
    vector<int> selectedItems(n, 0); // To track selected items
    
    int maxProfit = knapSack(W, weight, profit, n, selectedItems);
    
    cout << "Maximum profit: " << maxProfit << endl;
    printSelectedItems(selectedItems, weight, profit);
    
    return 0;
}
