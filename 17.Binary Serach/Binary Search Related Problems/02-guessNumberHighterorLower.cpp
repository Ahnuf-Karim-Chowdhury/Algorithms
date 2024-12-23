#include <bits/stdc++.h>
using namespace std;

// Forward declaration of guess API.
int guess(int num);

class Solution {
public:
    int guessNumber(int n) {
        int left = 1, right = n;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            int result = guess(mid);
            if (result == 0) {
                return mid; // Found the correct number
            } else if (result == -1) {
                right = mid - 1; // Picked number is lower
            } else {
                left = mid + 1; // Picked number is higher
            }
        }
        return -1; // This line is theoretically unreachable
    }
};

int main() {
    // Example usage:
    Solution solution;
    int n = 10;
    int pick = 6; // The number to guess (this would be set internally by the system in an actual game)
    cout << solution.guessNumber(n) << endl; // Expected output: 6
    return 0;
}
