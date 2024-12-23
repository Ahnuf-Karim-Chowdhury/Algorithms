#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        unsigned long int l = 0, r = nums.size() - 1,i=1;
        while (l < r) {
            cout<<"Iteration : "<<i<<endl;
            unsigned long int m = (l + r) / 2;
            cout<<"m =(l+r)/2 ="<<"("<<l<<"+"<<r<<")/2 = "<<m<<endl;
            cout<<"nums["<<m<<"] = "<<nums[m]<<"  nums["<<m+1<<"] = "<<nums[m+1]<<endl;
            if (nums[m] > nums[m + 1]) {
                cout<<"r = "<<m<<endl;
                r = m;
            } else {
                l = m + 1;
                cout<<"l = "<<m<<" + 1 = "<<l<<endl;
            }
            i++;
            cout<<endl;
        }
        return l;
    }
};

int main() {
    Solution solution;

    vector<int> nums1 = {1, 2, 3, 1};
    cout << "Peak element index: nums1 = {1, 2, 3, 1}\n" << solution.findPeakElement(nums1) << endl;

/*     vector<int> nums2 = {1, 2, 1, 3, 5, 6, 4};
    cout << "Peak element index: " << solution.findPeakElement(nums2) << endl;

    vector<int> nums3 = {5, 10, 20, 15};
    cout << "Peak element index: " << solution.findPeakElement(nums3) << endl;

    vector<int> nums4 = {10, 20, 15, 2, 23, 90, 67};
    cout << "Peak element index: " << solution.findPeakElement(nums4) << endl; */

    return 0;
}
