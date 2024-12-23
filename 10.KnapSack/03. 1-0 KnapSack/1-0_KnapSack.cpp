#include <bits/stdc++.h>
using namespace std;

int knapSack(int W, vector<int> wt, vector<int> val, int n){
   vector<int> K(W + 1, 0);
   for(int i = 0; i < n; i++) {
      for(int w = wt[i]; w <= W; w++) {
         K[w] = max(K[w], K[w - wt[i]] + val[i]);
      }
   }
   return K[W];
}

int main(){
   vector<int> val = { 70, 20, 50 };
   vector<int> wt = { 11, 12, 13 };
   int W = 30;
   int n = val.size();
   cout << "Maximum Profit achieved with this knapsack: " << knapSack(W, wt, val, n);
   return 0;
}
