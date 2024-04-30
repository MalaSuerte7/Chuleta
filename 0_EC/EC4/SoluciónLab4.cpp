/*
Integrantes:
    - Jimena Mamani 20202020
    - Alexis Raza 202020129
    - Francisco Calle 202210065
*/ 
// Problema 1
#include <iostream>
#include <stack>
#include <queue>
using namespace std;

// maxima profundidad de parentesis anidados
class Solution {
public:
    int maxDepth(string s) {
        stack<char> pila1;

        if (s.size()<1 || s.size()>100){
            cout << "Size not supported";
        }

        int maxvalidparenthesis = 0;
        // recorrer cada caracter de string
        for (char e: s){
            if (e == '('){
                pila1.push(e);
                int currMax = pila1.size();
                maxvalidparenthesis = max(maxvalidparenthesis, currMax);
            }else if ( e == ')' ) {
                pila1.pop();
            }
        }

        // comparar cantidad de parentesis anidados

        return maxvalidparenthesis;
    }
};

// Problema 2

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

// Problema 3

#include <iostream>
using namespace std;

struct Stack
{
    int val;
    int min{}; // guardo el mínimo valor
    Stack *next;
    Stack(int _val): val(_val), next(nullptr) {}
};

class MinStack
{
private:
    Stack *head;
    int nodes;

public:
    MinStack() : head(nullptr), nodes(0) {}

    void push(int val)
    {
        Stack *newNode = new Stack{val};

        newNode->min = (empty()) ? val : min(val, head->min); // Actualizar el mínimo hasta

        (empty()) ? newNode->next = nullptr : newNode->next = head;
        head = newNode;
        nodes++;
    }

    void pop(){
        if (empty()){ cout << endl << "Stack vacío" << endl;
        }
        else {
          auto *temp = head;
          head = head->next;
          delete temp;
          temp = nullptr;
          nodes--;
        }
    }

    int top(){
      return head->val;
    }

    int getMin(){
      return head->min; // Devuelve el mínimo valor
    }

    // para validar si está vacio o no
    bool empty(){
      return !head;
    }

    // extra
    int size(){
      return nodes;
    }
};