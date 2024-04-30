#include <iostream>
using namespace std;

struct Stack{
    int val;
    Stack* prev;
    Stack() : val(0), prev(nullptr){}
    Stack(int _val) : val(_val), prev(nullptr){}
};

class MyStack {
Stack* head;
public:
    MyStack() {
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
    int pop() {
        if(head == nullptr) return 0;
        Stack* save = nullptr;
        //
        save = head;
        this->head = this->head->prev;
        // Delete
        int temps = save->val;
        delete save;
        return temps;
    }
    // top ---------------------------------
    int top() {
        return this->head->val;
    }
    // empty -------------------------------
    bool empty() {
        if (head == nullptr){
            return true;
        }
        return false;
    }
};

int main(){
    MyStack myStack = MyStack();
    myStack.push(1);
    myStack.push(2);
    cout << myStack.top(); // return 2
    cout << myStack.pop(); // return 2
    cout << myStack.empty(); // return False   
}