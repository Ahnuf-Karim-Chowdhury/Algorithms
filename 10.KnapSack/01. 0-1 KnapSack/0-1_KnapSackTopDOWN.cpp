#include <bits/stdc++.h>
using namespace std;

int knapSack(int W, vector<int> wt, vector<int> val, int n)
{

    if (n == 0 || W == 0)
        return 0;

    if (wt[n - 1] > W)
        return knapSack(W, wt, val, n - 1);

    else
        return max(val[n - 1]+ knapSack(W - wt[n - 1], wt, val, n - 1),
                               knapSack(W, wt, val, n - 1));
}


int main()
{
    vector<int> profit = { 9,7,10,7};
    vector<int> weight = { 2,3,4,8};
    int W = 7;
    int n = profit.size();
    cout << knapSack(W, weight, profit, n);
    return 0;
}
