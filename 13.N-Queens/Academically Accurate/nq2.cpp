#include<bits/stdc++.h>
using namespace std;

int n;
vector<int> x(100);
int cnt = 0;

bool Place(int k, int i) {
    for (int j = 1; j <= k - 1; j++) {
        if ((x[j] == i) || (abs(x[j] - i) == abs(j - k)))
            return false;
    }
    return true;
}

void N_Queens(int k, int n) {
    for (int i = 1; i <= n; i++) {
        if (Place(k, i) == true) {
            x[k] = i;
            if (k == n) {
                cnt++;
                cout << "Way no  " << cnt << "  is :" << endl;
                for (int q = 1; q <= n; q++)
                    cout << "Queen [" << q << "]  sits in Row " << q << " , column " << x[q] << "  " << endl;
                cout << endl;
            } else {
                N_Queens(k + 1, n);
            }
        }
    }
}

int main() {
    cout << "Enter the Number of Queens : " << endl;
    cin >> n;
    N_Queens(1, n);
    return 0;
}
