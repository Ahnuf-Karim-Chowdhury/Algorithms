#include <bits/stdc++.h>
using namespace std;

int n = 5;
int p[10] = {3, 3, 2, 5, 1};
int w[10] = {10, 15, 10, 12, 8};
int W = 10;

int main() {
    int cur_w;
    float tot_v = 0.0;
    int i, maxi;
    int used[10];
    for (i = 0; i < n; ++i)
        used[i] = 0;
    cur_w = W;
    while (cur_w > 0) {
        maxi = -1;
        for (i = 0; i < n; ++i)
            if ((used[i] == 0) &&
                ((maxi == -1) || ((float)w[i] / p[i] > (float)w[maxi] / p[maxi])))
                maxi = i;
        used[maxi] = 1;
        cur_w -= p[maxi];
        tot_v += w[maxi];
        if (cur_w >= 0)
            cout << "Added object " << maxi + 1 << " (" << w[maxi] << ", " << p[maxi] << ") completely in the bag. Space left: " << cur_w << "." << endl;
        else {
            cout << "Added " << (int)((1 + (float)cur_w / p[maxi]) * 100) << "% (" << w[maxi] << ", " << p[maxi] << ") of object " << maxi + 1 << " in the bag." << endl;
            tot_v -= w[maxi];
            tot_v += (1 + (float)cur_w / p[maxi]) * w[maxi];
        }
    }
    cout << "Filled the bag with objects worth " << fixed << setprecision(2) << tot_v << "." << endl;
    return 0;
}
