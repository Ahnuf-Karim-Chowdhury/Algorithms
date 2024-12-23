#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int mySqrt(int x) {
        int left = 0, right = x;

        while (left < right) {
            int mid = (left + right) / 2 + 1;
            if (mid <= x / mid) { // mid^2 <= x, ans in [mid, right]
                left = mid;
            } else { // mid^2 > x
                right = mid - 1;
            }
        }
        return left;
    }
};

int main() {
    Solution solution;
    cout << solution.mySqrt(4) << endl; // Output: 2
    cout << solution.mySqrt(8) << endl; // Output: 2
    return 0;
}
