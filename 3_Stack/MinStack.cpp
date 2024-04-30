#include <iostream>
using namespace std;

struct Stack{
    int val;
    Stack* prev;
    Stack() : val(0), prev(nullptr){}
    Stack(int _val) : val(_val), prev(nullptr){}
};

class MinStack {
Stack* head;
public:
    MinStack() {
        // inica con un head a la nada
        this->head = nullptr;
    }
    //push --------------------------------
    void push(int x) {
        Stack* new_nodo =  new Stack(x);
        //1. esta vacio 
        if (head == nullptr){
            this->head = new_nodo;}
        //2. Tiene almenos un elemento
        else{
            new_nodo->prev = this->head;
            this->head = new_nodo;
        }
    }
    //pop ----------------------------------
    void pop() {
        if(head == nullptr) return;
        Stack* save = nullptr;
        //
        save = head;
        this->head = this->head->prev;
        // Delete
        delete save;
    }
    int top() {
        return this->head->val;
    }
    int getMin() {
        // O(1) time complexity
        Stack* temp = this->head;
        int min = temp->val;
        while(temp != nullptr){
            if(temp->val < min){
                min = temp->val;
            }
            temp = temp->prev;
        }
        return min;
    }
};

int main(){
    MinStack minStack = MinStack();
    minStack.push(-2);
    minStack.push(0);
    minStack.push(-3);
    cout << minStack.getMin()<< endl; // return -3
    minStack.pop();
    cout << minStack.top()<< endl; // return 0
    cout << minStack.getMin(); // return -2
}