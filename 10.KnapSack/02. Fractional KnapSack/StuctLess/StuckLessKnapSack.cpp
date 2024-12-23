#include <bits/stdc++.h>
using namespace std;

bool cmp(const pair<int, int> &a, const pair<int, int> &b) {
    double r1 = (double)a.first / a.second;
    double r2 = (double)b.first / b.second;
    return r1 > r2;
}

double fractionalKnapsack(int W, vector<pair<int, int>> &arr) {
    sort(arr.begin(), arr.end(), cmp);
    double finalvalue = 0.0;
    vector<double> selected(arr.size(), 0.0);
    
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i].second <= W) {
            W -= arr[i].second;
            finalvalue += arr[i].first;
            selected[i] = 1.0;
        } else {
            selected[i] = (double)W / arr[i].second;
            finalvalue += arr[i].first * selected[i];
            break;
        }
    }
    
    for (int i = 0; i < arr.size(); i++) {
        if (selected[i] > 0.0) {
            if (selected[i] == 1.0) {
                cout << "Selected item " << i + 1 << ": Weight = " << arr[i].second << ", Profit = " << arr[i].first << " completely." << endl;
            } else {
                cout << "Selected item " << i + 1 << ": Weight = " << arr[i].second << ", Profit = " << arr[i].first << ", Percentage taken = " << selected[i] * 100 << "%" << endl;
            }
        }
    }
    
    return finalvalue;
}

int main() {
    int W = 50;
    vector<pair<int, int>> arr = { {60, 10}, {100, 20}, {120, 30} };
    
    double maxValue = fractionalKnapsack(W, arr);
    cout << "Maximum value obtained = " << maxValue << endl;
    
    return 0;
}
