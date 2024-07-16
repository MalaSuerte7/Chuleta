
// MAL

#include <iostream>
#include <vector>
#include <algorithm>
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

    int min() {
        return heap[0];
    }
};

class KthLargest {
private:
    int kesimo;
    minHeap firstHeap;

public:
    KthLargest(int k, vector<int>& nums) : firstHeap(nums.size()) {
        kesimo = k;
        // crear minHeap
        for (int i = 0; i < nums.size(); i++) {
            firstHeap.insert(nums[i]);
        }
    }

    int add(int val) {
        firstHeap.insert(val);
        for (int i = 0; i < kesimo - 1; i++) {
            firstHeap.extractMin();
        }
        return firstHeap.extractMin();
    }
};

/**
* Your KthLargest object will be instantiated and called as such:
* KthLargest* obj = new KthLargest(k, nums);
* int param_1 = obj->add(val);
*/

// 2, *3, 4, 5, 8
// min heap -> sacatop(add -> val veces) y retornalo

/*
int main() {
    KthLargest kthLargest = KthLargest(3, {4, 5, 8, 2});
    // cout << kthLargest.add(3); // return 4
    // cout << kthLargest.add(5); // return 5
    // cout << kthLargest.add(10); // return 5
    // cout << kthLargest.add(9); // return 8
    // cout << kthLargest.add(4); // return 8

    return 0;
}
*/
