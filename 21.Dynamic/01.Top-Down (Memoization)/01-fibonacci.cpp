#include<bits/stdc++.h>
using namespace std;

vector<int> memo;

int fibonacci(int n) {
    if (n <= 1) return n;
    
    if (memo[n] != -1) return memo[n];
    
    memo[n] = fibonacci(n - 1) + fibonacci(n - 2);
    
    return memo[n];
}

int main() {
    int n;
    cout << "Enter the value of n: ";
    cin >> n;
    
    memo.assign(n + 1, -1);
    
    int result = fibonacci(n);
    cout << "Fibonacci number at position " << n << " is: " << result << endl;
    
    return 0;
}
