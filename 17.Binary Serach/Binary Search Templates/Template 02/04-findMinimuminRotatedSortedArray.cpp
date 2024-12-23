#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findMin(vector<int>& nums) {
        unsigned long int l = 0, r = nums.size() - 1;
        while (l < r) {
            unsigned long int m = l + (r - l) / 2;
            if (nums[m] > nums[r]) {
                l = m + 1;
            }
            else {
                r = m;
            }
        }
        return nums[l]; 
    }
};

int main() {
    Solution solution;
    vector<int> nums1 = {3, 4, 5, 1, 2};
    vector<int> nums2 = {4, 5, 6, 7, 0, 1, 2};
    vector<int> nums3 = {11, 13, 15, 17};
    
    cout << "Minimum element in nums1: " << solution.findMin(nums1) << endl;
    cout << "Minimum element in nums2: " << solution.findMin(nums2) << endl;
    cout << "Minimum element in nums3: " << solution.findMin(nums3) << endl;
    
    return 0;
}
