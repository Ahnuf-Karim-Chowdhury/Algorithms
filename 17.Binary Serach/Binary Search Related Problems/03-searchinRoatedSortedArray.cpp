#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int search(vector<int>& nums, int target) {
        int left = 0, right = nums.size() - 1;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            
            // Check if mid is the target
            if (nums[mid] == target) {
                return mid;
            }
            
            // Determine if the left half is sorted
            if (nums[left] <= nums[mid]) {
                // Check if target is in the left half
                if (nums[left] <= target && target < nums[mid]) {
                    right = mid - 1;
                } else {
                    left = mid + 1;
                }
            } 
            // Otherwise, the right half must be sorted
            else {
                // Check if target is in the right half
                if (nums[mid] < target && target <= nums[right]) {
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }
        }
        
        // If we exit the loop, the target was not found
        return -1;
    }
};

int main() {
    Solution solution;
    vector<int> nums1 = {4,5,6,7,0,1,2};
    int target1 = 0;
    cout << solution.search(nums1, target1) << endl; // Output: 4
    
    vector<int> nums2 = {4,5,6,7,0,1,2};
    int target2 = 3;
    cout << solution.search(nums2, target2) << endl; // Output: -1
    
    vector<int> nums3 = {1};
    int target3 = 0;
    cout << solution.search(nums3, target3) << endl; // Output: -1
    
    return 0;
}


/* 

class Solution {
public:
    int search(vector<int>& nums, int target) {
        int low = 0, high = nums.size() - 1;

        while (low <= high) {
            int mid = low + (high - low) / 2;

            if (nums[mid] == target) {
                return mid;
            }

            if (nums[low] <= nums[mid]) {
                if (nums[low] <= target && target < nums[mid]) {
                    high = mid - 1;
                } else {
                    low = mid + 1;
                }
            } else {
                if (nums[mid] < target && target <= nums[high]) {
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
            }
        }

        return -1;
    }
};
 */