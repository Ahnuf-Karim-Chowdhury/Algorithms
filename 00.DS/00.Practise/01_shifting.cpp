#include <bits/stdc++.h>
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
            {
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
            int curr = index;

            if (L < n && heap[L] > heap[curr])
            {
                curr = L;
            }
            if (R < n && heap[R] > heap[curr])
            {
                curr = R;
            }

            if (curr != index)
            {
                swap(heap[curr], heap[index]);
                index = curr;
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
    m.DeleteRoot();
    m.PrintHeap();

    return 0;
}
