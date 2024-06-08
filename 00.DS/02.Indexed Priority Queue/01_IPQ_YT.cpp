#include<bits/stdc++.h>
using namespace std;

class IndexPriorityQueue {
private:
    vector<int> values; // stores the values associated with the keys
    vector<int> im;     // inverse map: key index to position in heap
    vector<int> pm;     // position map: position in heap to key index
    int size;                // current size of the priority queue

    void swap(int i, int j) {
        pm[im[j]] = i;
        pm[im[i]] = j;
        swap(im[i], im[j]);
    }

    bool less(int i, int j) const {
        return values[im[i]] < values[im[j]];
    }

    void swim(int i) {
        for (int p = (i - 1) / 2; i > 0 && less(i, p); i = p, p = (i - 1) / 2) {
            swap(i, p);
        }
    }

    void sink(int i) {
        while (true) {
            int left = 2 * i + 1;
            int right = 2 * i + 2;
            int smallest = left;
            if (right < size && less(right, left)) {
                smallest = right;
            }
            if (left >= size || less(i, smallest)) {
                break;
            }
            swap(i, smallest);
            i = smallest;
        }
    }

public:
    IndexPriorityQueue(int maxN) 
        : values(maxN, INT_MAX), 
          im(maxN, -1), 
          pm(maxN, -1), 
          size(0) {}

    void insert(int ki, int val) {
        if (pm[ki] != -1) {
            throw invalid_argument("Index already in priority queue");
        }
        values[ki] = val;
        pm[ki] = size;
        im[size] = ki;
        swim(size);
        size++;
    }

    void remove(int ki) {
        int i = pm[ki];
        swap(i, --size);
        sink(i);
        swim(i);
        values[ki] = INT_MAX;
        pm[ki] = -1;
        im[size] = -1;
    }

    void update(int ki, int value) {
        int i = pm[ki];
        values[ki] = value;
        sink(i);
        swim(i);
    }

    void decreaseKey(int ki, int val) {
        if (val < values[ki]) {
            values[ki] = val;
            swim(pm[ki]);
        }
    }

    void increaseKey(int ki, int val) {
        if (values[ki] < val) {
            values[ki] = val;
            sink(pm[ki]);
        }
    }

    bool isEmpty() const {
        return size == 0;
    }

    int minIndex() const {
        if (isEmpty()) {
            throw out_of_range("Priority queue is empty");
        }
        return im[0];
    }

    int minValue() const {
        if (isEmpty()) {
            throw out_of_range("Priority queue is empty");
        }
        return values[im[0]];
    }
};

int main() {
    // Example usage:
    IndexPriorityQueue ipq(10);
    ipq.insert(0, 15);
    ipq.insert(1, 10);
    ipq.insert(2, 5);

    cout << "Min index: " << ipq.minIndex() << "\n"; // Output: 2
    cout << "Min value: " << ipq.minValue() << "\n"; // Output: 5

    ipq.decreaseKey(0, 3);

    cout << "Min index after decreaseKey: " << ipq.minIndex() << "\n"; // Output: 0
    cout << "Min value after decreaseKey: " << ipq.minValue() << "\n"; // Output: 3

    return 0;
}

/* 
swap(int i, int j): O(1) - Constant time operations.
less(int i, int j): O(1) - Single comparison.
swim(int i): O(log N) - Moving up through the heap.
sink(int i): O(log N) - Moving down through the heap.
insert(int ki, int val): O(log N) - Inserting and swimming up.
remove(int ki): O(log N) - Swapping, sinking, and swimming.
update(int ki, int value): O(log N) - Updating, sinking, and swimming.
decreaseKey(int ki, int val): O(log N) - Decreasing and swimming up.
increaseKey(int ki, int val): O(log N) - Increasing and sinking down.
isEmpty() const: O(1) - Checking size.
minIndex() const: O(1) - Accessing the root index.
minValue() const: O(1) - Accessing the root value.
 */
