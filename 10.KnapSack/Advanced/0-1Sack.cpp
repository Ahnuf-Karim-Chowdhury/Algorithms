#include <bits/stdc++.h>
using namespace std;

pair<int, vector<int>> knapSack(int W, vector<int> wt, vector<int> val, int n) {
   vector<vector<int>> K(n + 1, vector<int>(W + 1));
   for (int i = 0; i <= n; i++) {
      for (int w = 0; w <= W; w++) {
         if (i == 0 || w == 0)
            K[i][w] = 0;
         else if (wt[i - 1] <= w)
            K[i][w] = max(val[i - 1] + K[i - 1][w - wt[i - 1]], K[i - 1][w]);
         else
            K[i][w] = K[i - 1][w];
      }
   }

   // Now we need to find out which items are included in the optimal solution
   int res = K[n][W];
   int w = W;
   vector<int> items;
   
   for (int i = n; i > 0 && res > 0; i--) {
      if (res == K[i - 1][w])
         continue;         
      else {
         items.push_back(i - 1);
         res -= val[i - 1];
         w -= wt[i - 1];
      }
   }

   return {K[n][W], items};
}

int main() {
   vector<int> val = {70, 20, 50};
   vector<int> wt = {11, 12, 13};
   int W = 30;
   int n = val.size();
   
   pair<int, vector<int>> result = knapSack(W, wt, val, n);
   int maxProfit = result.first;
   vector<int> items = result.second;

   cout << "Maximum Profit achieved with this knapsack: " << maxProfit << endl;
   cout << "Selected: ";
   for (size_t i = 0; i < items.size(); i++) {
      cout << val[items[i]] << "(" <<wt[items[i]] << ")";
      if (i < items.size() - 1) cout << ", ";
   }
   cout << endl;

   return 0;
}
