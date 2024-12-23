#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        unsigned long int l = 0, r = nums.size() - 1;
        
        while (l < r) {
            unsigned long int m = (l + r) / 2;
            
            if (nums[m] > nums[m + 1]) {
                // If the middle element is greater than the next element,
                // then the peak lies in the left half, including the middle element.
                r = m;
            } else {
                // If the middle element is less than or equal to the next element,
                // then the peak lies in the right half, excluding the middle element.
                l = m + 1;
            }
        }
        
        // The loop ends when l == r, and this index l (or r) will be the peak element.
        return l;
    }
};

int main() {
    Solution solution;

    vector<int> nums1 = {1, 2, 3, 1};
    cout << "Peak element index: " << solution.findPeakElement(nums1) << endl;

    vector<int> nums2 = {1, 2, 1, 3, 5, 6, 4};
    cout << "Peak element index: " << solution.findPeakElement(nums2) << endl;

    vector<int> nums3 = {5, 10, 20, 15};
    cout << "Peak element index: " << solution.findPeakElement(nums3) << endl;

    vector<int> nums4 = {10, 20, 15, 2, 23, 90, 67};
    cout << "Peak element index: " << solution.findPeakElement(nums4) << endl;

    return 0;
}
