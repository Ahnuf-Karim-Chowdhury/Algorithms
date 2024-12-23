#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        unsigned long int l=0, r = nums.size()-1;
        while(l < r){
            unsigned long int m = (l + r)/2;
            if (nums[m] > nums[m + 1]){
               r = m; 
            } else {
                l = m + 1; 
            }
        }
        return l;
    }
};

// Main function to test the solution
int main() {
    vector<int> nums = {1, 2, 3, 1};  // Example input
    Solution sol;
    cout << "Peak element index: " << sol.findPeakElement(nums) << endl;
    return 0;
}
