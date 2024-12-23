#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Item {
    int profit, weight;
    Item(int profit, int weight) : profit(profit), weight(weight) {}
};

bool cmp(const Item &a, const Item &b) {
    double r1 = (double)a.profit / a.weight;
    double r2 = (double)b.profit / b.weight;
    return r1 > r2;
}

double fractionalKnapsack(int W, vector<Item> &arr, int idx) {
    if (idx >= arr.size() || W <= 0)
        return 0.0;
    
    if (arr[idx].weight <= W) {
        // Take the whole item
        return arr[idx].profit + fractionalKnapsack(W - arr[idx].weight, arr, idx + 1);
    } else {
        // Take a fraction of the item
        double fraction = (double)W / arr[idx].weight;
        return arr[idx].profit * fraction;
    }
}

int main() {
    int W = 20;
    vector<Item> arr = { {25,18}, {24,15}, {15,10} };
    
    // Sort items based on profit/weight ratio
    sort(arr.begin(), arr.end(), cmp);
    
    double maxValue = fractionalKnapsack(W, arr, 0);
    cout << "Maximum value obtained = " << maxValue << endl;
    
    return 0;
}
