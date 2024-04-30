#include <iostream>
using namespace std;

// struct Stack{
//     int val;
//     Stack* prev; 
//     Stack() : val(0), prev(nullptr){}
//     Stack(int _val) : val(_val), prev(nullptr){}
// };

class Stack{
public:
    int val;
    Stack* prev;
    Stack() : val(0), prev(nullptr){}
    Stack(int _val) : val(_val), prev(nullptr){}
};

class Solution{
Stack* head = nullptr;
public:
    Solution(int val){
        Stack* nw = new Stack(val);
        this->head = nw; 
    }
    
    void insert(int val){
        Stack* new_nodo = new Stack(val);
        new_nodo->prev = this->head;
        this->head = new_nodo;
    }
    
    void pop(){
        Stack* save = nullptr;
        save = this->head;
        this->head = (this->head)->prev;
        delete save;
    }

    friend ostream& operator << (ostream& os, Solution& pr){
        os << pr.head->val;
        return os;
    }
};


int main(){
    Solution sol = Solution(3);
    sol.insert(1); // inserto 1
    sol.insert(2); // inserto 2
    sol.pop(); // elimino 2
    cout << sol;

    // cout << 

}