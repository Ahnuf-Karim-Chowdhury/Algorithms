#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool cmp(const pair<int, int> &a, const pair<int, int> &b) {
    double r1 = (double)a.first / a.second;
    double r2 = (double)b.first / b.second;
    return r1 > r2;
}

double fractionalKnapsack(int W, vector<pair<int, int>> &arr, int idx) {
    if (idx >= arr.size() || W <= 0)
        return 0.0;
    
    if (arr[idx].second <= W) {
        return arr[idx].first + fractionalKnapsack(W - arr[idx].second, arr, idx + 1);
    } else {
        double fraction = (double)W / arr[idx].second;
        return arr[idx].first * fraction;
    }
}

int main() {
    int W = 50;
    vector<pair<int, int>> arr = { {60, 10}, {100, 20}, {120, 30} };
    
    sort(arr.begin(), arr.end(), cmp);
    
    double maxValue = fractionalKnapsack(W, arr, 0);
    cout << "Maximum value obtained = " << maxValue << endl;
    
    return 0;
}
