// Problema 3
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
};

class Solution {
public:
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        int N = matrix.size() * matrix[0].size();
        minHeap heap(N);

        for (int i = 0; i < matrix.size(); i++) {
            for (int j = 0; j < matrix[0].size(); j++) {
                heap.insert(matrix[i][j]);
            }
        }

        for (int i = 0; i < k - 1; i++) {
            heap.extractMin();
        }

        return heap.extractMin();
    }
};

// Tests

int main() {
    Solution s;

    // matriz 1
    vector<vector<int>> matrix = {{1, 5, 9}, {10, 11, 13}, {12, 13, 15}};
    cout << s.kthSmallest(matrix, 8) << endl; // 13 

    // matriz 2
    vector<vector<int>> matrix2 = {{-5}};
    cout << s.kthSmallest(matrix2, 1) << endl; // -5

    return 0;
}

