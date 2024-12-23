#include <bits/stdc++.h>
using namespace std;

const int n = 5;
const int MAX = 1000000;

int dist[n + 1][n + 1] = {
    {MAX, 20, 30, 10, 11},
    {15, MAX, 16, 4, 2},
    {3, 5, MAX, 2, 4},
    {19, 6, 18, MAX, 3},
    {16, 4, 7, 16, MAX}
};

int memo[n + 1][1 << (n + 1)];

int fun(int i, int mask) {
    if (mask == ((1 << i) | 3))
        return dist[1][i];
    if (memo[i][mask] != 0)
        return memo[i][mask];

    int res = MAX;
    for (int j = 1; j <= n; j++)
        if ((mask & (1 << j)) && j != i && j != 1)
            res = min(res, fun(j, mask & (~(1 << i))) + dist[j][i]);
    return memo[i][mask] = res;
}

int main() {
    int ans = MAX;
    for (int i = 1; i <= n; i++)
        ans = min(ans, fun(i, (1 << (n + 1)) - 1) + dist[i][1]);

    printf("The cost of most efficient tour = %d", ans);
    return 0;
}
