#include <vector>
#include <iostream>
using namespace std;

template <typename T>
class MinHeap {
private:
    vector<T> heap;

    void heapifyUp(int index) {
        if (index == 0) return;
        int parentIndex = (index - 1) / 2;
        if (heap[index] < heap[parentIndex]) {
            swap(heap[index], heap[parentIndex]);
            heapifyUp(parentIndex);
        }
    }

    void heapifyDown(int index) {
        int smallest = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;

        if (left < heap.size() && heap[left] < heap[smallest]) smallest = left;
        if (right < heap.size() && heap[right] < heap[smallest]) smallest = right;

        if (smallest != index) {
            swap(heap[index], heap[smallest]);
            heapifyDown(smallest);
        }
    }

public:
    MinHeap() {}

    void insert(T data) {
        heap.push_back(data);
        heapifyUp(heap.size() - 1);
    }

    T extractMin() {
        if (heap.empty()) {
            throw "Heap vacío";
        }

        T minData = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        heapifyDown(0);

        return minData;
    }

    bool isEmpty() const {
        return heap.empty();
    }
};

class Solution {

    struct Node {
        int _sum{};
        int _index{};
        Node(int sum, int index) : _sum(sum), _index(index) {}

        bool operator<(const Node &other) const {
            if (_sum != other._sum) return _sum < other._sum;
            return _index < other._index;
        }
    };

    int sum(vector<int> &a) {
        int res = 0;
        for (auto e : a) res += e;
        return res;
    }

public:
    vector<int> kWeakestRows(vector<vector<int>> &mat, int k) {
        MinHeap<Node> heap;
        for (int i = 0; i < mat.size(); ++i) {
            int val = sum(mat[i]);
            Node n(val, i);
            heap.insert(n);
        }

        vector<int> kWeakest;
        for (int i = 0; i < k; ++i) kWeakest.push_back(heap.extractMin()._index);

        return kWeakest;
    }
};

// Tests

int main()
{
    // Test 1
    vector<vector<int>> mat1 = {
        {1, 1, 0, 0, 0},
        {1, 1, 1, 1, 0},
        {1, 0, 0, 0, 0},
        {1, 1, 0, 0, 0},
        {1, 1, 1, 1, 1}
    };

    auto res = Solution().kWeakestRows(mat1, 3);
    for (auto e : res) cout << e << " ";
    cout << endl;   // [2,0,3]

    // Test 2
    vector<vector<int>> mat2 = {
        {1, 0, 0, 0},
        {1, 1, 1, 1},
        {1, 0, 0, 0},
        {1, 0, 0, 0}
    };

    res = Solution().kWeakestRows(mat2, 2);
    for (auto e : res) cout << e << " ";
    cout << endl; // [0,2]

    return 0;
}
