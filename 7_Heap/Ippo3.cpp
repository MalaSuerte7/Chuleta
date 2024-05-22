/*
Conceptos:
- Heap
- Como un array, donde su hijos:
    - Left(i) = 2*i + 1
    - Right(i) = 2*i + 2
    - Parent(i) = (i-1)/2

- If left recursion bota un número mayor al lenght de array entonces no existe y si on existe para
*/

#include <iostream>
#include <vector>
using namespace std;

struct MaxHeap{
    int val;
    MaxHeap* left = nullptr;
    MaxHeap* right = nullptr;
    MaxHeap() : val(0),  left(nullptr), right(nullptr) {}
    MaxHeap(int _val) : val(_val),  left(nullptr), right(nullptr) {}

};

struct queue{
    int front, rear, size;
    unsigned capacity;
    int* array;

    queue(unsigned _capacity){
        capacity = _capacity;
        front = size = 0;
        rear = capacity - 1;
        array = new int[capacity];
    }

    bool isFull(queue* q){
        return (q->size == q->capacity);
    }

    bool isEmpty(queue* q){
        return (q->size == 0);
    }

    void enqueue(int item){
        if(isFull(this)){
            return;
        }
        rear = (rear + 1) % capacity;
        array[rear] = item;
        size = size + 1;
    }

    int dequeue(){
        if(isEmpty(this)){
            return INT_MIN;
        }
        int item = array[front];
        front = (front + 1) % capacity;
        size = size - 1;
        return item;
    }

    int front(){
        if(isEmpty(this)){
            return INT_MIN;
        }
        return array[front];
    }

    int rear(){
        if(isEmpty(this)){
            return INT_MIN;
        }
        return array[rear];
    }
};



class Solution{
    public:
        MaxHeap* insert(MaxHeap* root, int val){
            if(root == nullptr){
                return new MaxHeap(val);
            }
            if(val > root->val){
                swap(val, root->val);
            }
            if(val % 2 == 0){
                root->left = insert(root->left, val);
            }else{
                root->right = insert(root->right, val);
            }
            return root;
        }

        void print(MaxHeap* root){
            if(root == nullptr){
                return;
            }
            cout << root->val << " ";
            print(root->left);
            print(root->right);
        }

        // heapify up
        void heapifyUp(vector<int>& arr, int i){
            if(i == 0){
                return;
            }
            int parent = (i-1)/2;
            if(arr[parent] < arr[i]){
                swap(arr[parent], arr[i]);
                heapifyUp(arr, parent);
            }
        }

        // heapify down
        void heapifyDown(vector<int>& arr, int i, int n){
            int left = 2*i + 1;
            int right = 2*i + 2;
            int maxIndex = i;
            if(left < n && arr[left] > arr[maxIndex]){
                maxIndex = left;
            }
            if(right < n && arr[right] > arr[maxIndex]){
                maxIndex = right;
            }
            if(maxIndex != i){
                swap(arr[i], arr[maxIndex]);
                heapifyDown(arr, maxIndex, n);
            }
        }

        // build heap
        void buildHeap(vector<int>& arr){
            for(int i = 1; i < arr.size(); i++){
                heapifyUp(arr, i);
            }
        }

        // delete
        void deleteMax(vector<int>& arr){
            swap(arr[0], arr[arr.size()-1]);
            arr.pop_back();
            heapifyDown(arr, 0, arr.size());
        }

        // extract max
        int extractMax(vector<int>& arr){
            int max = arr[0];
            deleteMax(arr);
            return max;
        }

        // get max
        int getMax(vector<int>& arr){
            return arr[0];
        }
};


int main(){
    vector<int> arr = {3, 2, 1, 7, 8, 4, 10, 16, 12};
    Solution* obj = new Solution();
    obj->buildHeap(arr);
    cout << obj->getMax(arr) << endl;
    cout << obj->extractMax(arr) << endl;
    cout << obj->getMax(arr) << endl;
    return 0;
}
