#include <iostream> 
using namespace std;

struct Nodo{
    int data;
    Nodo* next;
};

class Forward_list{
private:
    Nodo* head = new Nodo;
public:
    Forward_list() : head(nullptr){}

    Nodo* front(){
        return head;
    }
};


int main(){
    // Making memory
    Nodo* a = new Nodo;
    a->data = 1;
    Nodo* b = new Nodo;
    b->data = 2;
    Nodo* c = new Nodo;
    c->data = 3;

    a->next = b;
    b->next = c;
    c->next = NULL;

    Nodo* head = new Nodo;
    head = a;
    Nodo* temp = new Nodo;
    temp = head;
}