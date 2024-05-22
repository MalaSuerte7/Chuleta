#include <iostream>

using namespace std;

struct MinHeapNode {
    int val;
    MinHeapNode* left;
    MinHeapNode* right;

    MinHeapNode(int _val) : val(_val), left(nullptr), right(nullptr) {}
};

struct Queue {
    int front, rear, size;
    unsigned capacity;
    MinHeapNode** array;

    Queue(unsigned _capacity) {
        capacity = _capacity;
        front = size = 0;
        rear = capacity - 1;
        array = new MinHeapNode*[capacity];
    }

    ~Queue() {
        delete[] array;
    }

    bool isFull() const {
        return (size == capacity);
    }

    bool isEmpty() const {
        return (size == 0);
    }

    void enqueue(MinHeapNode* item) {
        if (isFull()) return;
        rear = (rear + 1) % capacity;
        array[rear] = item;
        size++;
    }

    MinHeapNode* dequeue() {
        if (isEmpty()) return nullptr;
        MinHeapNode* item = array[front];
        front = (front + 1) % capacity;
        size--;
        return item;
    }

    MinHeapNode* frontItem() const {
        if (isEmpty()) return nullptr;
        return array[front];
    }
};

class MinHeap {
public:
    MinHeapNode* root;
    Queue* q;

    MinHeap() {
        root = nullptr;
        q = new Queue(100);
    }

    ~MinHeap() {
        delete q;
        deleteTree(root);
    }

    void insert(int val) {
        MinHeapNode* newNode = new MinHeapNode(val);
        if (root == nullptr) {
            root = newNode;
        } else {
            MinHeapNode* temp = q->frontItem();
            if (temp->left == nullptr) {
                temp->left = newNode;
            } else if (temp->right == nullptr) {
                temp->right = newNode;
                q->dequeue();
            }
        }
        q->enqueue(newNode);
        heapifyUp(newNode);
    }

    int getMin() const {
        return root ? root->val : -1;
    }

    int extractMin() {
        if (!root) return -1;

        int minVal = root->val;

        MinHeapNode* lastNode = q->array[q->rear];
        q->array[q->rear] = nullptr;
        q->rear = (q->rear - 1 + q->capacity) % q->capacity;
        q->size--;

        if (lastNode == root) {
            delete root;
            root = nullptr;
        } else {
            swap(root->val, lastNode->val);
            MinHeapNode* parent = getParent(lastNode);
            if (parent->left == lastNode) {
                parent->left = nullptr;
            } else {
                parent->right = nullptr;
            }
            delete lastNode;
            heapifyDown(root);
        }

        return minVal;
    }

    void print() const {
        if (!root) return;

        Queue printQueue(100);
        printQueue.enqueue(root);

        while (!printQueue.isEmpty()) {
            MinHeapNode* temp = printQueue.dequeue();
            cout << temp->val << " ";
            if (temp->left) {
                printQueue.enqueue(temp->left);
            }
            if (temp->right) {
                printQueue.enqueue(temp->right);
            }
        }
        cout << endl;
    }

    void heapifyUp(MinHeapNode* node) {
        if (!node || !root) return;

        while (node != root && getParent(node)->val > node->val) {
            swap(getParent(node)->val, node->val);
            node = getParent(node);
        }
    }

    void heapifyDown(MinHeapNode* node) {
        while (node && (node->left || node->right)) {
            MinHeapNode* smallerChild = node->left;
            if (node->right && node->right->val < node->left->val) {
                smallerChild = node->right;
            }

            if (smallerChild && smallerChild->val < node->val) {
                swap(node->val, smallerChild->val);
                node = smallerChild;
            } else {
                break;
            }
        }
    }

    MinHeapNode* getParent(MinHeapNode* node) const {
        if (node == root) return nullptr;

        Queue tempQueue(100);
        tempQueue.enqueue(root);

        while (!tempQueue.isEmpty()) {
            MinHeapNode* parent = tempQueue.dequeue();
            if (parent->left == node || parent->right == node) {
                return parent;
            }
            if (parent->left) {
                tempQueue.enqueue(parent->left);
            }
            if (parent->right) {
                tempQueue.enqueue(parent->right);
            }
        }
        return nullptr;
    }

    void deleteTree(MinHeapNode* node) {
        if (node) {
            deleteTree(node->left);
            deleteTree(node->right);
            delete node;
        }
    }
};

int main() {
    MinHeap heap;
    heap.insert(3);
    heap.insert(2);
    heap.insert(15);
    heap.insert(5);
    heap.insert(4);
    heap.insert(45);

    cout << "Heap elements: ";
    heap.print();

    cout << "Extracted Min: " << heap.extractMin() << endl;
    cout << "Current Min: " << heap.getMin() << endl;

    heap.insert(1);
    cout << "Heap elements after inserting 1: ";
    heap.print();

    return 0;
}
