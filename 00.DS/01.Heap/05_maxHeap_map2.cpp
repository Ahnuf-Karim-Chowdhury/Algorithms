#include<bits/stdc++.h>
using namespace std;

class maxHeap
{
    vector<int> heap;
    unordered_map<int, int> indexMap;      // Map element value to its index in the heap
    unordered_map<int, int> valueIndexMap; // Map element value to its index in the heap
    int minVal = INT_MAX;                  // Variable to store the minimum value in the heap
    int maxVal = -INT_MAX;

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
    // maxHeap() : minVal(numeric_limits<int>::max()) {} // Initialize minVal with maximum integer value

    void insert(int val)
    {
        heap.push_back(val);
        indexMap[val] = heap.size() - 1;      // Store index of newly inserted element
        valueIndexMap[val] = heap.size() - 1; // Store index of newly inserted element in valueIndexMap
        shift(heap.size() - 1);

        // Update minVal if the inserted value is smaller
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
        auto it = valueIndexMap.find(val);
        if (it != valueIndexMap.end())
        {
            return it->second; // Return the index from the valueIndexMap
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
        return maxVal; // Return the minimum value
    }

    void deleteAnyValue(int val)
    {
        int index = find(val);
        if (index != -1)
        {
            heap[index] = heap.back();
            indexMap[heap[index]] = index; // Update index of the moved element
            heap.pop_back();
            UpShift(index);   // Call UpShift to maintain the heap property
            DownShift(index); // Call DownShift to maintain the heap property

            if (val == minVal)
            {
                if (heap.empty())
                {
                    minVal = numeric_limits<int>::max(); // Reset minVal if the heap becomes empty
                }
                else
                {
                    minVal = *min_element(heap.begin(), heap.end()); // Find the new minimum value
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


    return 0;
}

/* 
UpShift: O(log n)
DownShift: O(log n)
shift: O(log n)
insert: O(log n)
PrintHeap: O(n)
find: O(1)
findMin: O(1)
findMax: O(1)
deleteAnyValue: O(n)
 */