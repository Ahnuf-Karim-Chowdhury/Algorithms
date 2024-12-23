#include <bits/stdc++.h>
using namespace std;

void SumofSub(vector<int>& w, vector<int>& x, int s, int k, int r, int m) {
    if (k > w.size() - 1) return; 

    x[k] = 1; 
    if (s + w[k] == m) {
        for (int i = 1; i < w.size(); i++) {
            if (x[i] == 1) {
                cout << w[i] << " ";
            }
        }
        cout << endl;
    }
    if (s + w[k] <= m) {
        SumofSub(w, x, s + w[k], k + 1, r - w[k], m);
    }

    x[k] = 0; 
    SumofSub(w, x, s, k + 1, r - w[k], m);
}

int main() {
    int n, m;
    cout << "Enter the number of elements: ";
    cin >> n;

    vector<int> w(n + 1);
    vector<int> x(n + 1, 0);
    int sum = 0;

    cout << "Enter the elements: ";
    for (int i = 1; i <= n; i++) {
        cin >> w[i];
        sum += w[i];
    }

    cout << "Enter the sum to find: ";
    cin >> m;

    cout << "Subsets with sum " << m << " are:" << endl;
    SumofSub(w, x, 0, 1, sum, m);

    return 0;
}

/* 
Enter the number of elements: 4
Enter the elements: 2 1 4 3
Enter the sum to find: 5
 */