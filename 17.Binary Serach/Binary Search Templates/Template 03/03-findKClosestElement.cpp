#include<bits/stdc++.h>
using namespace std;

int desperate_optimization(int precision){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cout.setf(ios::fixed);
    cout.setf(ios::showpoint);
    cout.precision(precision);
    return 0;
}

class Solution {
public:
    Solution(){
        desperate_optimization(10);
    }

    int lowerBound(vector<int>& arr, int x) {
        int start = 0;
        int end = arr.size() - 1;
        int ans = end;

        while (start <= end) {
            int mid = start + (end - start) / 2;
            if (arr[mid] >= x) {
                ans = mid;
                end = mid - 1;
            } else {
                start = mid + 1;
            }
        }
        return ans;
    }

    vector<int> twoPtrMethod(vector<int>& arr, int k, int x) {
        int low = 0;
        int high = arr.size() - 1;

        while (high - low >= k) {
            if (x - arr[low] > arr[high] - x) 
                low++;
            else
                high--;
        }

        vector<int> ans;
        for (int i = low; i <= high; i++)
            ans.push_back(arr[i]);

        return ans;
    }

    vector<int> binarySearchMethod(vector<int>& arr, int k, int x) {
        // Find the lower bound
        int high = lowerBound(arr, x);
        int low = high - 1;

        while (k--) {
            if (low < 0)
                high++;
            else if (high >= arr.size())
                low--;
            else if (x - arr[low] > arr[high] - x)
                high++;
            else
                low--;
        }
        return vector<int>(arr.begin() + low + 1, arr.begin() + high);
    }

    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        return binarySearchMethod(arr, k, x);
    }
};

int main() {
    Solution solution;
    vector<int> arr1 = {1, 2, 3, 4, 5};
    int k1 = 4, x1 = 3;
    vector<int> result1 = solution.findClosestElements(arr1, k1, x1);
    cout << "Closest elements: ";
    for (int num : result1) {
        cout << num << " ";
    }
    cout << endl;

    vector<int> arr2 = {1, 2, 3, 4, 5};
    int k2 = 4, x2 = -1;
    vector<int> result2 = solution.findClosestElements(arr2, k2, x2);
    cout << "Closest elements: ";
    for (int num : result2) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
