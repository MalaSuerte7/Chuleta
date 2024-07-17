// Solución sin queue
#include <vector>
#include <iostream>

using namespace std;

class minHeap {
private:
    int size;
    int capacity;
    vector<int> heap;

    int parent(int i) { return (i - 1) / 2; }
    int left(int i) { return 2 * i + 1; }
    int right(int i) { return 2 * i + 2; }

public:
    minHeap(int capacity) {
        size = 0;
        this->capacity = capacity;
        heap.resize(capacity);
    }

    void insert(int k) {
        if (size == capacity) {
            cout << "MIN HEAP LLENO" << endl;
            return;
        }
        size++;
        int i = size - 1;
        heap[i] = k;

        // update minHeap
        while (i != 0 && heap[parent(i)] > heap[i]) {
            swap(heap[i], heap[parent(i)]);
            i = parent(i);
        }
    }

    void heapify(int i) {
        int l = left(i);
        int r = right(i);
        int smallest = i;

        if ((l < size) && (heap[l] < heap[smallest])) smallest = l;
        if ((r < size) && (heap[r] < heap[smallest])) smallest = r;

        if (smallest != i) {
            swap(heap[i], heap[smallest]);
            heapify(smallest);
        }
    }

    int extractMin() {
        if (size == 0) {
            cout << "EMPTY" << endl;
            return -1;
        } else if (size == 1) {
            size--;
            return heap[0];
        } else {
            int min = heap[0];
            heap[0] = heap[size - 1];
            size--;
            heapify(0);
            return min;
        }
    }

    int getMin() {
        return heap[0];
    }

    int getSize() {
        return size;
    }
};

class KthLargest {
public:
    KthLargest(int k, vector<int>& nums) : k(k), firstHeap(k) {
        for (int num : nums) {
            add(num);
        }
    }

    int add(int val) {
        if (firstHeap.getSize() < k) {
            firstHeap.insert(val);
        } else if (val > firstHeap.getMin()) {
            firstHeap.extractMin();
            firstHeap.insert(val);
        }
        return firstHeap.getMin();
    }

private:
    int k;
    minHeap firstHeap;
};

// Ejemplo de uso
int main() {
    vector<int> nums = {4, 5, 8, 2};
    KthLargest kthLargest(3, nums);
    cout << kthLargest.add(3) << endl;  // return 4
    cout << kthLargest.add(5) << endl;  // return 5
    cout << kthLargest.add(10) << endl; // return 5
    cout << kthLargest.add(9) << endl;  // return 8
    cout << kthLargest.add(4) << endl;  // return 8
    return 0;
}
