#include <bits/stdc++.h>
using namespace std;

struct Item {
    int profit, weight;
    Item(int profit, int weight) {
        this->profit = profit;
        this->weight = weight;
    }
};

static bool cmp(struct Item a, struct Item b) {
    double r1 = (double)a.profit / (double)a.weight;
    double r2 = (double)b.profit / (double)b.weight;
    return r1 > r2;
}

double fractionalKnapsack(int W, vector<Item> &arr, int N) {
    sort(arr.begin(), arr.end(), cmp);
    double finalvalue = 0.0;
    vector<double> selected(N, 0.0);
    for (int i = 0; i < N; i++) {
        if (arr[i].weight <= W) {
            W -= arr[i].weight;
            finalvalue += arr[i].profit;
            selected[i] = 1.0;
        } else {
            selected[i] = (double)W / (double)arr[i].weight;
            finalvalue += arr[i].profit * selected[i];
            break;
        }
    }
    for (int i = 0; i < N; i++) {
        if (selected[i] > 0.0) {
            if (selected[i] == 1.0) {
                cout << "Selected item " << i + 1 << ": Weight = " << arr[i].weight << ", Profit = " << arr[i].profit << " completely." << endl;
            } else {
                cout << "Selected item " << i + 1 << ": Weight = " << arr[i].weight << ", Profit = " << arr[i].profit << ", Percentage taken = " << selected[i] * 100 << "%" << endl;
            }
        }
    }
    return finalvalue;
}

int main() {
    int W = 50;
    vector<Item> arr = { {60, 10}, {100, 20}, {120, 30} };
    int N = arr.size();
    double maxValue = fractionalKnapsack(W, arr, N);
    cout << "Maximum value obtained = " << maxValue << endl;
    return 0;
}
