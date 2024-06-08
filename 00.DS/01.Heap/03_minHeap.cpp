#include <vector>
#include <iostream>
#include <stdexcept>

using namespace std;

class BinaryHeap
{
private:
    vector<int> heap;

    void shiftUp(int index)
    {
        while (index > 0)
        {
            int parent = (index - 1) / 2; // Calculate the parent's index
            if (heap[index] < heap[parent])
            {                                    // Change to < for min-heap
                swap(heap[index], heap[parent]); // Swap the current node with the parent
                index = parent;                  // Update the index to the parent's index
            }
            else
            {
                break; // If the heap property is satisfied, exit the loop
            }
        }
    }

    void shiftDown(int index)
    {
        int size = heap.size();
        while (2 * index + 1 < size)
        { // While there is at least one child
            int leftChild = 2 * index + 1;
            int rightChild = 2 * index + 2;
            int smallest = index;

            if (leftChild < size && heap[leftChild] < heap[smallest])
            { // Change to < for min-heap
                smallest = leftChild;
            }
            if (rightChild < size && heap[rightChild] < heap[smallest])
            { // Change to < for min-heap
                smallest = rightChild;
            }
            if (smallest != index)
            {
                swap(heap[index], heap[smallest]);
                index = smallest;
            }
            else
            {
                break;
            }
        }
    }

    void shift(int index)
    {
        if (index > 0 && heap[index] < heap[(index - 1) / 2])
        { // Change to < for min-heap
            shiftUp(index);
        }
        else
        {
            shiftDown(index);
        }
    }

public:
    void insert(int value)
    {
        heap.push_back(value);  // Insert the new value at the end of the heap
        shift(heap.size() - 1); // Restore the heap property
    }

    void deleteRoot()
    {
        if (heap.size() > 1)
        {
            heap[0] = heap.back(); // Move the last element to the root
            heap.pop_back();       // Remove the last element
            shift(0);              // Restore the heap property
        }
        else if (heap.size() == 1)
        {
            heap.pop_back(); // If there's only one element, just remove it
        }
        else
        {
            throw out_of_range("Heap is empty");
        }
    }

    void printHeap() const
    {
        for (int i : heap)
        {
            cout << i << " ";
        }
        cout << endl;
    }
    int find(int val) const
    {
        for (int i = 0; i < heap.size(); ++i)
        {
            if (heap[i] == val)
            {
                return i; // Return the index of the found value
            }
        }
        return -1; // Return -1 if the value is not found
    }

    void deleteAnyValue(int val)
    {
        int index = find(val);
        if (index != -1)
        {
            heap[index] = heap.back();
            heap.pop_back();
            shiftUp(index);   // Call UpShift to maintain the heap property
            shiftDown(index); // Call DownShift to maintain the heap property
        }
        else
        {
            cout << "Value Not Found!\n";
        }
    }
};

int main()
{
    BinaryHeap minHeap;
    minHeap.insert(10);
    minHeap.insert(20);
    minHeap.insert(5);
    minHeap.insert(30);
    minHeap.insert(15);

    minHeap.printHeap(); // Output should maintain min-heap property

    minHeap.deleteAnyValue(15); // Remove the root
    minHeap.printHeap();  // Output should maintain min-heap property

    return 0;
}
