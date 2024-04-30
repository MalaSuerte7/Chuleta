#include <iostream>
using namespace std;

struct Deque{
    int val;
    Deque* rRight;
    Deque* rLeft;
    Deque() : val(-1), rLeft(nullptr), rRight(nullptr){}
    Deque(int _val) : val(_val), rLeft(nullptr), rRight(nullptr){}
};

class MyCircularDeque {
Deque* front = nullptr;
Deque* rear = nullptr;
int max_polution = 0;
int polution = 0;
public:
    MyCircularDeque(int k) {
        this->max_polution = k;
    }
    bool insertFront(int value) {
        // check pollution
        if (this->polution == this->max_polution) return false;
        // create new node
        Deque* new_nodo = new Deque(value);
        //1.Vacio
        if(front == nullptr){
            this->front = new_nodo;
            this->rear = new_nodo;
        }
        //2. Si ya tiene
        else{
            new_nodo->rLeft = this->front;
            this->front->rRight = new_nodo;
            this->front = new_nodo;
        }
        polution++;
        return true; 
    }
    bool insertLast(int value) {
        // check polution
        if (this->polution == this->max_polution) return false;
        // create new node
        Deque* new_node = new Deque(value);
        //1. Vacio
        if (front == nullptr){
            this->front = new_node;
            this->rear = new_node;
        }
        //2. Si ya tiene
        else{
            new_node->rRight = this->rear;
            this->rear->rLeft = new_node;
            this->rear = new_node;
        }
        polution++;
        return true;
    }
    bool deleteFront() {
        if(front == nullptr) return false;
        // delete
        Deque* save = nullptr;
        save = this->front;
        this->front = this->front->rLeft;
        delete save;
        //Porseaca
        this->front->rRight = nullptr;
        polution--;
        return true;
    }
    bool deleteLast() {
        if(rear == nullptr) return false;
        // delete
        Deque* save = nullptr;
        save = this->rear;
        this->rear = this->rear->rRight;
        delete save;
        //Porseaca
        this->rear->rLeft = nullptr;
        polution--;
        return true;
    }
    int getFront() {
        return this->front->val;
    }
    int getRear() {
        return this->rear->val;
    }
    bool isEmpty() {
        if(this->front == nullptr || this->rear == nullptr){
            return true;
        }
        return false;
    }
    bool isFull() {
        if(this->polution >= this->max_polution){
            return true;
        }
        return false;
    }
};

int main(){
    MyCircularDeque myCircularDeque =  MyCircularDeque(3);
    cout << myCircularDeque.insertLast(1) << ": 1" << endl; // return True
    cout << myCircularDeque.insertLast(2) << ": 1" << endl; // return True
    cout << myCircularDeque.insertFront(3) << ": 1" << endl; // return True
    cout << myCircularDeque.insertFront(4) << ": 0" << endl; // return False, the queue is full.
    cout << myCircularDeque.getRear() << ": 2" << endl; // return 2
    cout << myCircularDeque.isFull() << ": 1" << endl; // return True
    cout << myCircularDeque.deleteLast() << ": 1" << endl; // return True
    cout << myCircularDeque.insertFront(4) << ": 1" << endl; // return True
    cout << myCircularDeque.getFront() << ": 4" << endl; // return 4
}