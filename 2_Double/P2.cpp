#include <iostream>
using namespace std;


struct DoubleN{
    int numb;
    DoubleN* next;
    DoubleN* prev;
    DoubleN* child;
    DoubleN() : numb(0), next(nullptr), prev(nullptr),child(nullptr){}
    DoubleN(int _numb) : numb(_numb), next(nullptr), prev(nullptr), child(nullptr){}
};

class Solution{    
public:
    DoubleN* plane(DoubleN* h){
        DoubleN* temp = h;
        DoubleN* temp2;
        DoubleN* save;
        
        while(temp->next != nullptr){
            if(temp->child != nullptr){
                save = temp->next;              // puente
                temp2 = temp->child;            // nuevo iterador
                while(temp2->next != nullptr){  // 
                    temp2 = temp2->next;
                }
                temp2->next = save;
                save->prev = temp2;
            }
            temp = temp->next;
        }
        // imprimir la lista enlazada

        return h;
    }
};

int main(){
    DoubleN* a = new DoubleN(1); 
    DoubleN* b = new DoubleN(2);
    DoubleN* c = new DoubleN(3);
    a->next = b; b->prev = a; b->next = c; c->prev = b;

    DoubleN* d = new DoubleN(3);
    DoubleN* e = new DoubleN(3);
    d->next = e; e->prev = d;

    DoubleN* f = new DoubleN(9);
    DoubleN* g = new DoubleN(9);
    f->next = g; g->prev = f;

    b->child = d;
    d->child = f;


    DoubleN* head = a;
    Solution sol;
    head = sol.plane(head);

    // imprimir la lista enlazada
    while(head != nullptr){
        cout << head->numb << " ";
        head = head->next;
    }
}