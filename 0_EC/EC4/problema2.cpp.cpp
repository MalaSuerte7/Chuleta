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
        // case front->rLeft == nullptr and front->rRight == nullptr
        Deque* save = nullptr;
        if(front->rLeft == nullptr && front->rRight == nullptr){
            save = this->front;
            this->front = nullptr;
            this->rear = nullptr;
            delete save;
            polution--;
            return true;   
        } 
        // delete
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
        // case front->rLeft == nullptr and front->rRight == nullptr
        Deque* save = nullptr;
        if(front->rLeft == nullptr && front->rRight == nullptr){
            save = this->front;
            this->front = nullptr;
            this->rear = nullptr;
            delete save;
            polution--;
            return true;
        } 
        // delete
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
    // MyCircularDeque myCircularDeque = MyCircularDeque(8);
    // cout << myCircularDeque.insertFront(5) << endl; // return True
    // cout << myCircularDeque.getFront() << endl; // return 5
    // cout << myCircularDeque.isEmpty() << endl; // return False
    // cout << myCircularDeque.deleteFront() << endl; // return True
    // cout << myCircularDeque.insertLast(3) << endl; // return True
    // cout << myCircularDeque.getRear() << endl; // return 3
    // cout << myCircularDeque.insertLast(7) << endl; // return True
    // cout << myCircularDeque.insertFront(7) << endl; // return True
    // cout << myCircularDeque.deleteLast() << endl; // return True
    // cout << myCircularDeque.insertLast(4) << endl; // return True
    // cout << myCircularDeque.isEmpty() << endl; // return False


    // cout << myCircularDeque.insertLast(5) << endl; // return True
    // cout << myCircularDeque.insertLast(2) << endl; // return True
    // cout << myCircularDeque.insertFront(3) << endl; // return True
    // cout << myCircularDeque.insertFront(4) << endl; // return False, the queue is full.
    // cout << myCircularDeque.getRear() << endl; // return 2
    // cout << myCircularDeque.isFull() << endl; // return True
    // cout << myCircularDeque.deleteLast() << endl; // return True
    // cout << myCircularDeque.insertFront(4) << endl; // return True
    // cout << myCircularDeque.getFront() << endl; // return 4
}

/*
["MyCircularDeque","insertFront","getFront","isEmpty","deleteFront","insertLast","getRear","insertLast","insertFront","deleteLast","insertLast","isEmpty"]
*/
/*
[[8],[5],[],[],[],[3],[],[7],[7],[],[4],[]]
*/