#include <bits/stdc++.h>
#include <algorithm>
using namespace std;

class maxHeap
{
    vector<int> heap;

private:
    void UpShift(int index)
    {
        while (index > 0)
        {
            int parent = (index - 1) / 2;
            if (heap[index] > heap[parent])
            { // Corrected the comparison for max-heap
                swap(heap[index], heap[parent]);
                index = parent;
            }
            else
            {
                break;
            }
        }
    }

    void DownShift(int index)
    {
        int n = heap.size();
        while (2 * index + 1 < n)
        {
            int L = 2 * index + 1;
            int R = 2 * index + 2;
            int largest = index;
            if (L < n && heap[L] > heap[largest])
            { // Corrected comparison
                largest = L;
            }
            if (R < n && heap[R] > heap[largest])
            { // Corrected comparison
                largest = R;
            }

            if (largest != index)
            {
                swap(heap[largest], heap[index]);
                index = largest;
            }
            else
            {
                break;
            }
        }
    }

    void shift(int index)
    {
        if (index > 0 && heap[index] > heap[(index - 1) / 2])
        {
            UpShift(index);
        }
        else
        {
            DownShift(index);
        }
    }

public:
    void insert(int val)
    {
        heap.push_back(val);
        shift(heap.size() - 1);
    }

    void PrintHeap()
    {
        for (const auto &i : heap)
        {
            cout << i << " ";
        }
        cout << "\n";
    }
    void DeleteRoot()
    {
        if (heap.size() == 0)
        {
            throw out_of_range("Heap is empty!");
        }
        else if (heap.size() == 1)
        {
            heap.pop_back();
        }
        else
        {
            heap[0] = heap.back();
            heap.pop_back();
            DownShift(0); // Added this line to restore the heap property
        }
    }
    int findIndex(int val) const
    {
        auto it = find(heap.begin(), heap.end(), val);
        if (it != heap.end())
        {
            int index = distance(heap.begin(), it);
            return index;
        }
        return -1;
    }

    void deleteAnyValue(int val)
    {
        int index = findIndex(val);
        if (index != -1)
        {
            heap[index] = heap.back();
            heap.pop_back();
            UpShift(index);   // Call UpShift to maintain the heap property
            DownShift(index); // Call DownShift to maintain the heap property
        }
        else
        {
            cout << "Value Not Found!\n";
        }
    }
};

int main()
{
    maxHeap m;
    m.insert(10);
    m.insert(20);
    m.insert(5);
    m.insert(30);
    m.insert(15);

    m.PrintHeap();
    m.deleteAnyValue(20);
    m.PrintHeap();
}
