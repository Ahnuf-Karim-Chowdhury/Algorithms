#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int binarySearch(const vector<int>& nums, int target) {
        if (nums.empty()) {
            return -1;
        }

        int left = 0;
        int right = nums.size() - 1;

        while (left < right) {
            int mid = left + (right - left) / 2;

            if (nums[mid] == target) {
                return mid;
            } else if (nums[mid] < target) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }

        if (nums[left] == target) {
            return left;
        }
        return -1;
    }
};

int main() {
    Solution solution;
    vector<int> nums = {1, 2, 4, 6, 7, 8, 9};
    int target = 6;

    int result = solution.binarySearch(nums, target);

    if (result != -1) {
        cout << "Target " << target << " found at index " << result << endl;
    } else {
        cout << "Target " << target << " not found in the array." << endl;
    }

    return 0;
}
