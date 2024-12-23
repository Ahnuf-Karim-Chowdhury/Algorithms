#include <bits/stdc++.h>
using namespace std;

vector<int> generate_sequence(int seq_length) {
    vector<int> sequence;
    int value = 1;
    for (int n = 0; n < seq_length; ++n) {
        int x = (n ^ (n - 1));
        int bit_length = 0;
        while (x > 0) {
            ++bit_length;
            x >>= 1;
        }
        bit_length += 1;
        if (bit_length % 2 == 0) {
            // Bit index is even, so toggle value
            value = 1 - value;
        }
        sequence.push_back(value);
    }
    return sequence;
}

int main() {
    int seq_length = 10; // Example length of the sequence
    vector<int> sequence = generate_sequence(seq_length);
    
    for (int val : sequence) {
        cout << val << " ";
    }
    cout << endl;
    
    return 0;
}
