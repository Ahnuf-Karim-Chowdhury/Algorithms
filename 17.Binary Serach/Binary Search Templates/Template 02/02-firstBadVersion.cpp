#include<bits/stdc++.h>
using namespace std;

// The API isBadVersion is defined for you.
bool isBadVersion(int version);

class Solution {
public:
    int firstBadVersion(int n) {
        unsigned long int l = 1;  
        unsigned long int r = n;
        
        while (l < r) {  
            unsigned long int m = l + (r - l) / 2;
            if (isBadVersion(m)) {
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
    int n = 5; // Number of versions
    Solution sol;
    cout << "First bad version: " << sol.firstBadVersion(n) << endl;
    return 0;
}
