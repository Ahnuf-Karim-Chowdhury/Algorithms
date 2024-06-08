#include <bits/stdc++.h>
using namespace std;

class doubleHeap
{
    vector<int> maxHeap;
    vector<int> minHeap;
    unordered_map<int, int> maxIndexMap; // Map element value to its index in the maxHeap
    unordered_map<int, int> minIndexMap; // Map element value to its index in the minHeap

private:
    void upShiftMaxHeap(int index)
    {
        while (index > 0)
        {
            int parent = (index - 1) / 2;
            if (maxHeap[index] > maxHeap[parent])
            {
                swap(maxHeap[index], maxHeap[parent]);
                maxIndexMap[maxHeap[index]] = index;
                maxIndexMap[maxHeap[parent]] = parent;
                index = parent;
            }
            else
            {
                break;
            }
        }
    }

    void downShiftMaxHeap(int index)
    {
        int n = maxHeap.size();
        while (2 * index + 1 < n)
        {
            int L = 2 * index + 1;
            int R = 2 * index + 2;
            int largest = index;
            if (L < n && maxHeap[L] > maxHeap[largest])
            {
                largest = L;
            }
            if (R < n && maxHeap[R] > maxHeap[largest])
            {
                largest = R;
            }

            if (largest != index)
            {
                swap(maxHeap[largest], maxHeap[index]);
                maxIndexMap[maxHeap[largest]] = largest;
                maxIndexMap[maxHeap[index]] = index;
                index = largest;
            }
            else
            {
                break;
            }
        }
    }
    void downShiftMaxHeap(int index, int size)
    {
        int n = size;
        while (2 * index + 1 < n)
        {
            int L = 2 * index + 1;
            int R = 2 * index + 2;
            int largest = index;
            if (L < n && maxHeap[L] > maxHeap[largest])
            {
                largest = L;
            }
            if (R < n && maxHeap[R] > maxHeap[largest])
            {
                largest = R;
            }

            if (largest != index)
            {
                swap(maxHeap[largest], maxHeap[index]);
                maxIndexMap[maxHeap[largest]] = largest;
                maxIndexMap[maxHeap[index]] = index;
                index = largest;
            }
            else
            {
                break;
            }
        }
    }

    void upShiftMinHeap(int index)
    {
        while (index > 0)
        {
            int parent = (index - 1) / 2;
            if (minHeap[index] < minHeap[parent])
            {
                swap(minHeap[index], minHeap[parent]);
                minIndexMap[minHeap[index]] = index;
                minIndexMap[minHeap[parent]] = parent;
                index = parent;
            }
            else
            {
                break;
            }
        }
    }

    void downShiftMinHeap(int index)
    {
        int n = minHeap.size();
        while (2 * index + 1 < n)
        {
            int L = 2 * index + 1;
            int R = 2 * index + 2;
            int smallest = index;
            if (L < n && minHeap[L] < minHeap[smallest])
            {
                smallest = L;
            }
            if (R < n && minHeap[R] < minHeap[smallest])
            {
                smallest = R;
            }

            if (smallest != index)
            {
                swap(minHeap[smallest], minHeap[index]);
                minIndexMap[minHeap[smallest]] = smallest;
                minIndexMap[minHeap[index]] = index;
                index = smallest;
            }
            else
            {
                break;
            }
        }
    }

    void shiftMaxHeap(int index)
    {
        if (index > 0 && maxHeap[index] > maxHeap[(index - 1) / 2])
        {
            upShiftMaxHeap(index);
        }
        else
        {
            downShiftMaxHeap(index);
        }
    }

    void shiftMinHeap(int index)
    {
        if (index > 0 && minHeap[index] < minHeap[(index - 1) / 2])
        {
            upShiftMinHeap(index);
        }
        else
        {
            downShiftMinHeap(index);
        }
    }

public:
    const vector<int> &getMaxHeap() const
    {
        return maxHeap;
    }
    const vector<int> &getMinHeap() const
    {
        return minHeap;
    }
    void insert(int val)
    {
        maxHeap.push_back(val);
        minHeap.push_back(val);
        maxIndexMap[val] = maxHeap.size() - 1;
        minIndexMap[val] = minHeap.size() - 1;
        shiftMaxHeap(maxHeap.size() - 1);
        shiftMinHeap(minHeap.size() - 1);
    }

    void printMaxHeap()
    {
        for (const auto &i : maxHeap)
        {
            cout << i << " ";
        }
        cout << "\n";
    }

    void printMinHeap()
    {
        for (const auto &i : minHeap)
        {
            cout << i << " ";
        }
        cout << "\n";
    }

    int find(int val) const
    {
        auto it = maxIndexMap.find(val);
        if (it != maxIndexMap.end())
        {
            return it->second;
        }
        return -1;
    }

    int findMin() const
    {
        if (minHeap.empty())
        {
            cout << "Heap is empty\n";
            return -1;
        }
        return minHeap[0];
    }

    int findMax() const
    {
        if (maxHeap.empty())
        {
            cout << "Heap is empty\n";
            return -1;
        }
        return maxHeap[0];
    }

    void extractMin()
    {
        if (minHeap.empty())
        {
            cout << "Heap is empty\n";
            return;
        }
        int minVal = minHeap[0];
        deleteByValue(minVal);
    }

    void extractMax()
    {
        if (maxHeap.empty())
        {
            cout << "Heap is empty\n";
            return;
        }
        int maxVal = maxHeap[0];
        deleteByValue(maxVal);
    }

    void updateByValue(int oldVal, int newVal)
    {
        // Find the indices of the old value in both heaps
        int maxIndex = find(oldVal);
        int minIndex = minIndexMap[oldVal];

        if (maxIndex == -1 || minIndexMap.find(oldVal) == minIndexMap.end())
        {
            cout << "Value Not Found!\n";
            return;
        }

        // Update the values in the heaps
        maxHeap[maxIndex] = newVal;
        minHeap[minIndex] = newVal;

        // Remove the old value from the index maps
        maxIndexMap.erase(oldVal);
        minIndexMap.erase(oldVal);

        // Insert the new value into the index maps
        maxIndexMap[newVal] = maxIndex;
        minIndexMap[newVal] = minIndex;

        // Fix the heaps
        shiftMaxHeap(maxIndex);
        shiftMinHeap(minIndex);
    }

    void updateByIndex(int index, int val)
    {
        int old = maxHeap[index];
        int minIndex = minIndexMap[old];
        maxHeap[index] = val;
        minHeap[minIndex] = val;
        maxIndexMap.erase(old);
        minIndexMap.erase(old);
        maxIndexMap[val] = index;
        minIndexMap[val] = minIndex;
        if (old > val)
        {
            downShiftMaxHeap(index);
            downShiftMinHeap(minIndex);
        }
        else
        {
            upShiftMaxHeap(index);
            upShiftMinHeap(minIndex);
        }
    }

    void deleteByValue(int val)
    {
        int maxIndex = find(val);
        int minIndex = minIndexMap[val];
        if (maxIndex != -1)
        {
            if (maxIndex != maxHeap.size() - 1)
            {
                swap(maxHeap[maxIndex], maxHeap.back());
                maxIndexMap[maxHeap[maxIndex]] = maxIndex;
            }
            if (minIndex != minHeap.size() - 1)
            {
                swap(minHeap[minIndex], minHeap.back());
                minIndexMap[minHeap[minIndex]] = minIndex;
            }
            maxHeap.pop_back();
            minHeap.pop_back();
            maxIndexMap.erase(val);
            minIndexMap.erase(val);

            if (maxIndex < maxHeap.size())
            {
                shiftMaxHeap(maxIndex);
            }
            if (minIndex < minHeap.size())
            {
                shiftMinHeap(minIndex);
            }
        }
        else
        {
            cout << "Value Not Found!\n";
        }
    }

    void deleteByIndex(int index)
    {
        int val = maxHeap[index];
        int minIndex = minIndexMap[val];
        maxHeap[index] = maxHeap.back();
        minHeap[minIndex] = minHeap.back();
        maxHeap.pop_back();
        minHeap.pop_back();
        upShiftMaxHeap(index);
        downShiftMaxHeap(index);
        upShiftMinHeap(minIndex);
        downShiftMinHeap(minIndex);
    }

    void heapify()
    {
        for (int i = maxHeap.size() / 2 - 1; i >= 0; --i)
        {
            downShiftMaxHeap(i);
            downShiftMinHeap(i);
        }
    }

    vector<int> copy;

    void heapSort()
    {
        copy = maxHeap;         // Make a copy of the input array
        int n = maxHeap.size(); // Get the size of the heap

        // Build max heap in O(n) time
        for (int i = n / 2 - 1; i >= 0; --i)
        {
            downShiftMaxHeap(i);
        }

        // Extract elements one by one from the heap
        for (int i = n - 1; i >= 0; i--)
        {
            // Move current root to end
            swap(maxHeap[0], maxHeap[i]);
            // Reduce the size of the heap
            n--;
            // Heapify the root element to get the largest element at the root again
            downShiftMaxHeap(0, n); // Pass the reduced size 'n'
        }

        // Now, maxHeap contains the sorted array in ascending order
        // Copy the sorted elements back to 'copy'
        copy = maxHeap;
    }
    void PrintHeapSort(){
        for(const auto& i : copy){
            cout<<i<<" ";
        }
        cout<<'\n';
    }
};

int main()
{
    doubleHeap dh;
    dh.insert(10);
    dh.insert(20);
    dh.insert(5);
    dh.insert(30);
    dh.insert(15);

    cout << "Max Heap: ";
    dh.printMaxHeap();
    cout << "Min Heap: ";
    dh.printMinHeap();

    cout << "Index of 20 in maxHeap: " << dh.find(20) << endl;
    cout << "Minimum value in the heap: " << dh.findMin() << endl;
    cout << "Maximum value in the heap: " << dh.findMax() << endl;

/*     dh.extractMin();
    cout << "Min Heap after extracting min: ";
    dh.printMinHeap();

    dh.extractMax();
    cout << "Max Heap after extracting max: ";
    dh.printMaxHeap();

    dh.updateByValue(15, 4);
    cout << "After updating 30 to 4: " << endl;
    cout << "Max Heap: ";
    dh.printMaxHeap();
    cout << "Min Heap: ";
    dh.printMinHeap(); */

    cout << "sorted array : \n";
    dh.heapSort();
    dh.PrintHeapSort();

    return 0;
}

/*
Insertion, extraction, deletion, update: O(logn)
Finding the min/max and index: O(1)
Printing heaps: O(n)
Heapify: O(n)
Heap sort: O(nlogn)

 */