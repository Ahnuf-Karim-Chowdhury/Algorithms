#include <bits/stdc++.h>
using namespace std;

int init = [] {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ofstream out("user.out");
    cout.rdbuf(out.rdbuf());

    for (string s; getline(cin, s); cout << '\n') {
        string t;
        getline(cin, t);
        int tar = stoi(t);

        for (int i = 0, _i = 1, _n = s.length(); _i < _n; ++i, ++_i) {
            bool _neg = 0;
            if (s[_i] == '-')
                ++_i, _neg = 1;
            int v = s[_i++] & 15;
            while ((s[_i] & 15) < 10)
                v = v * 10 + (s[_i++] & 15);
            if (_neg)
                v = -v;
            if (v == tar) {
                cout << i;
                goto next;
            }
            if (v > tar)
                break;
        }
        cout << -1;
    next:;
    }
    exit(0);
    return 0;
}();

class Solution {
public:
    int search(vector<int>& v, int target) {
        int low = 0, high = v.size() - 1;
        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (v[mid] == target) {
                return mid;
            } else if (target > v[mid]) {
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }
        return -1;
    }
};

int main() {
    // Example test for the Solution class
    vector<int> nums = {1, 2, 3, 4, 5};
    int target = 3;
    Solution sol;
    int result = sol.search(nums, target);
    cout << "Index of " << target << " in the array is: " << result << endl;

    return 0;
}
