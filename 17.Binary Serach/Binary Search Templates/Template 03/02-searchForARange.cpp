#include<bits/stdc++.h>
using namespace std;
/* 
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int first=-1;
        int last=-1;
        int start=0;
        int end=nums.size()-1;
        while(start<=end){
            int mid=(start+end)/2;
            if(nums[mid]==target){
                first=mid;
                end=mid-1;
            }else if(nums[mid]<target){
                start=mid+1;
            }else if(nums[mid]>target){
                end=mid-1;
            }
        }
         start=0;
         end=nums.size()-1;
         while(start<=end){
            int mid=(start+end)/2;
            if(nums[mid]==target){
                last=mid;
                start=mid+1;
            }else if(nums[mid]<target){
                start=mid+1;
            }else if(nums[mid]>target){
                end=mid-1;
            }
        }

        return {first,last};
    }
};
 */
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int left = findLeft(nums, target);
        int right = findRight(nums, target);
        return {left, right};
    }
    
private:
    int findLeft(vector<int>& nums, int target) {
        int left = 0, right = nums.size() - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] >= target) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        // Check if left is within bounds and if it is the target
        if (left < nums.size() && nums[left] == target) {
            return left;
        }
        return -1;
    }
    
    int findRight(vector<int>& nums, int target) {
        int left = 0, right = nums.size() - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] <= target) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        // Check if right is within bounds and if it is the target
        if (right >= 0 && nums[right] == target) {
            return right;
        }
        return -1;
    }
};

int main() {
    Solution solution;
    vector<int> nums1 = {5,7,7,8,8,10};
    int target1 = 8;
    vector<int> result1 = solution.searchRange(nums1, target1);
    cout << "[" << result1[0] << ", " << result1[1] << "]" << endl;

    vector<int> nums2 = {5,7,7,8,8,10};
    int target2 = 6;
    vector<int> result2 = solution.searchRange(nums2, target2);
    cout << "[" << result2[0] << ", " << result2[1] << "]" << endl;

    vector<int> nums3 = {};
    int target3 = 0;
    vector<int> result3 = solution.searchRange(nums3, target3);
    cout << "[" << result3[0] << ", " << result3[1] << "]" << endl;

    return 0;
}
