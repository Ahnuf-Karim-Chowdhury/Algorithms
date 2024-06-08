#include <bits/stdc++.h>
using namespace std;

class maxHeap
{
    vector<int> heap;
    unordered_map<int, int> indexMap; // Map element value to its index in the heap
    int minVal = INT_MAX;             // Variable to store the minimum value in the heap
    int maxVal = INT_MIN;             // Variable to store the maximum value in the heap

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

        // Update minVal and maxVal if necessary
        if (val < minVal)
        {
            minVal = val;
        }
        if (val > maxVal)
        {
            maxVal = val;
        }
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
        return minVal; // Return the minimum value
    }

    int findMax() const
    {
        if (heap.empty())
        {
            cout << "Heap is empty\n";
            return -1;
        }
        return maxVal; // Return the maximum value
    }

    void extractMin()
    {
        if (heap.empty())
        {
            cout << "Heap is empty\n";
            return;
        }

        deleteAnyValue(minVal);
    }

    void extractMax()
    {
        if (heap.empty())
        {
            cout << "Heap is empty\n";
            return;
        }

        deleteAnyValue(maxVal);
    }

    void deleteAnyValue(int val)
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

            // Update minVal if the deleted value was the minimum value
            if (val == minVal)
            {
                if (!heap.empty())
                {
                    minVal = *min_element(heap.begin(), heap.end());
                }
                else
                {
                    minVal = numeric_limits<int>::max(); // Reset minVal if the heap becomes empty
                }
            }

            // Update maxVal if the deleted value was the maximum value
            if (val == maxVal)
            {
                if (!heap.empty())
                {
                    maxVal = heap[0]; // Max value is always at the root in max heap
                }
                else
                {
                    maxVal = numeric_limits<int>::min(); // Reset maxVal if the heap becomes empty
                }
            }
        }
        else
        {
            cout << "Value Not Found!\n";
        }
    }

    void update(int oldVal, int newVal)
    {
        int index = find(oldVal);
        if (index != -1)
        {
            heap[index] = newVal;
            indexMap.erase(oldVal);
            indexMap[newVal] = index;
            shift(index);

            // Update minVal and maxVal if necessary
            if (newVal < minVal)
            {
                minVal = newVal;
            }
            if (newVal > maxVal)
            {
                maxVal = newVal;
            }
            if (oldVal == minVal || oldVal == maxVal)
            {
                if (!heap.empty())
                {
                    minVal = *min_element(heap.begin(), heap.end());
                    maxVal = *max_element(heap.begin(), heap.end());
                }
                else
                {
                    minVal = numeric_limits<int>::max();
                    maxVal = numeric_limits<int>::min();
                }
            }
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
    cout << "Index of 20: " << m.find(20) << endl;
    cout << "Minimum value in the heap: " << m.findMin() << endl;
    cout << "Maximum value in the heap: " << m.findMax() << endl;

    m.update(20, 25);
    m.PrintHeap();
    cout << "Minimum value in the heap after update: " << m.findMin() << endl;
    cout << "Maximum value in the heap after update: " << m.findMax() << endl;

    m.extractMin();
    cout << "Minimum value in the heap after extraction: " << m.findMin() << endl;

    m.extractMax();
    cout << "Maximum value in the heap after extraction: " << m.findMax() << endl;

    return 0;
}
/* 
insert: O(log n)
find: O(1) average case, O(n) worst case
findMin and findMax: O(1)
extractMin and extractMax: O(log n)
deleteAnyValue: O(n) average case (including finding), O(log n) if already found
update: O(n) average case (including finding), O(log n) if already found
 */