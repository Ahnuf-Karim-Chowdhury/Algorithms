#include <vector>
#include <iostream>
#include <stdexcept>

using namespace std;

class BinaryHeap {
private:
    vector<int> heap;

    void shiftUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2; // Calculate the parent's index
            if (heap[index] > heap[parent]) { // If the current node is greater than the parent (for max-heap)
                swap(heap[index], heap[parent]); // Swap the current node with the parent
                index = parent; // Update the index to the parent's index
            } else {
                break; // If the heap property is satisfied, exit the loop
            }
        }
    }

    void shiftDown(int index) {
        int size = heap.size();
        while (2 * index + 1 < size) { // While there is at least one child
            int leftChild = 2 * index + 1;
            int rightChild = 2 * index + 2;
            int largest = index;

            if (leftChild < size && heap[leftChild] > heap[largest]) {
                largest = leftChild;
            }
            if (rightChild < size && heap[rightChild] > heap[largest]) {
                largest = rightChild;
            }
            if (largest != index) {
                swap(heap[index], heap[largest]);
                index = largest;
            } else {
                break;
            }
        }
    }

    void shift(int index) {
        if (index > 0 && heap[index] > heap[(index - 1) / 2]) {
            shiftUp(index);
        } else {
            shiftDown(index);
        }
    }

public:
    void insert(int value) {
        heap.push_back(value); // Insert the new value at the end of the heap
        shift(heap.size() - 1); // Restore the heap property
    }

    void deleteRoot() {
        if (heap.size() > 1) {
            heap[0] = heap.back(); // Move the last element to the root
            heap.pop_back(); // Remove the last element
            shift(0); // Restore the heap property
        } else if (heap.size() == 1) {
            heap.pop_back(); // If there's only one element, just remove it
        } else {
            throw out_of_range("Heap is empty");
        }
    }

    void printHeap() const {
        for (int i : heap) {
            cout << i << " ";
        }
        cout << endl;
    }
};

int main() {
    BinaryHeap maxHeap;
    maxHeap.insert(10);
    maxHeap.insert(20);
    maxHeap.insert(5);
    maxHeap.insert(30);
    maxHeap.insert(15);

    maxHeap.printHeap(); // Output should maintain max-heap property

    maxHeap.deleteRoot(); // Remove the root
    maxHeap.printHeap(); // Output should maintain max-heap property

    return 0;
}
