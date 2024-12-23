#include <bits/stdc++.h>
using namespace std;

bool SumofSub(vector<int>& w, vector<int>& x, int s, int k, int m) {
    if (s == m) {
        for (int i = 1; i < w.size(); i++) {
            if (x[i] == 1) {
                cout << w[i] << " ";
            }
        }
        cout << endl;
        return true;
    }

    if (k <= 0 || s > m) {
        return false;
    }

    x[k] = 1;
    if (SumofSub(w, x, s + w[k], k - 1, m)) {
        return true;
    }

    x[k] = 0;
    if (SumofSub(w, x, s, k - 1, m)) {
        return true;
    }

    return false;
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
    SumofSub(w, x, 0, n, m);

    return 0;
}

/* 
Enter the number of elements: 4
Enter the elements: 2 1 4 3
Enter the sum to find: 5
 */