#include <bits/stdc++.h>
using namespace std;

class maxHeap
{
    vector<int> heap;
    unordered_map<int, int> indexMap; // Map element value to its index in the heap

private:
    void UpShift(int index)
    {
        while (index > 0)
        {
            int parent = (index - 1) / 2;
            if (heap[index] > heap[parent])
            { // Corrected the comparison for max-heap
                swap(heap[index], heap[parent]);
                indexMap[heap[index]] = index;   // Update index in the map
                indexMap[heap[parent]] = parent; // Update parent index in the map
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
                indexMap[heap[largest]] = largest; // Update index in the map
                indexMap[heap[index]] = index;     // Update current index in the map
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
        indexMap[val] = heap.size() - 1; // Store index of newly inserted element
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

    int find(int val) const
    {
        auto it = indexMap.find(val);
        if (it != indexMap.end())
        {
            return it->second; // Return the index from the indexMap
        }
        return -1;
    }

    int findMin() const
    {
        if (heap.empty())
        {
            cout << "Heap is empty\n";
            return -1;
        }
        return *min_element(heap.begin(), heap.end()); // Find the minimum value
    }

    int findMax() const
    {
        if (heap.empty())
        {
            cout << "Heap is empty\n";
            return -1;
        }
        return heap[0]; // Max value is always at the root in max heap
    }

    void extractMin()
    {
        if (heap.empty())
        {
            cout << "Heap is empty\n";
            return;
        }

        int minVal = findMin();
        deleteByValue(minVal);
    }

    void extractMax()
    {
        if (heap.empty())
        {
            cout << "Heap is empty\n";
            return;
        }

        deleteByValue(heap[0]);
    }

    void updateByValue(int oldVal, int newVal)
    {
        int index = find(oldVal);
        if (index != -1)
        {
            heap[index] = newVal;
            indexMap.erase(oldVal);
            indexMap[newVal] = index;
            shift(index);
        }
        else
        {
            cout << "Value Not Found!\n";
        }
    }

    void UpdateByIndex(int index, int val)
    {
        int old = heap[index];
        heap[index] = val;
        indexMap.erase(old);
        indexMap[val] = index;
        if (old > val)
        {
            DownShift(index);
        }
        else
        {
            UpShift(index);
        }
    }

    void deleteByValue(int val)
    {
        int index = find(val);
        if (index != -1)
        {
            if (index != heap.size() - 1)
            {
                swap(heap[index], heap.back());
                indexMap[heap[index]] = index; // Update index of the moved element
            }
            heap.pop_back();
            indexMap.erase(val);

            if (index < heap.size())
            {
                shift(index);
            }
        }
        else
        {
            cout << "Value Not Found!\n";
        }
    }

    void deleteByIndex(int index){
          heap[index]=heap.back();
          heap.pop_back();
          UpShift(index);
          DownShift(index);
    }

    void heapify()
    {
        int n = heap.size();
        for (int i = (n / 2) - 1; i >= 0; --i)
        {
            DownShift(i);
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
    cout << "Index of 20: " << m.find(20) << endl;
    cout << "Minimum value in the heap: " << m.findMin() << endl;
    cout << "Maximum value in the heap: " << m.findMax() << endl;

    m.extractMin();
    cout << "Minimum value in the heap after extraction: " << m.findMin() << endl;

    m.extractMax();
    cout << "Maximum value in the heap after extraction: " << m.findMax() << endl;

    m.updateByValue(30, 4);
    cout << "After Update: " << endl;
    m.PrintHeap();

    vector<int> arr = {20, 30, 5, 40, 25};
    m = maxHeap();
    for (int val : arr) {
        m.insert(val);
    }
    cout << "Heap before heapify: " << endl;
    m.PrintHeap();

    m.heapify();
    cout << "Heap after heapify: " << endl;
    m.PrintHeap();

    return 0;
}