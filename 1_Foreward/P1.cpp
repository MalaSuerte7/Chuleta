#include <iostream>
using namespace std;

struct Nodo {
    int data;
    Nodo* right;
};

Nodo* push_front(Nodo* head, int n){
    Nodo* d = new Nodo;
    d->data = n;
    d->right = head;
    head = d;
    return head;
}


int main(){
    //Creación de nodos
    Nodo* a = new Nodo;
    a->data = 5;
    Nodo* b = new Nodo;
    b->data = 6;
    Nodo* c = new Nodo;
    c->data = 7;

    // Lista
    a->right = b;   
    b->right = c;
    c->right = NULL;
    // Head
    Nodo* head = new Nodo;
    head = a;
    // current head solution
    Nodo* temp = new Nodo;

    head = push_front(head, 8);
    
    temp = head;
    while(temp != NULL){
        cout << temp->data << " ";
        temp = temp->right;
    }

    cout << endl;

    head = push_front(head, 9);
    temp = head;
    while(temp != NULL){
        cout << temp->data << " ";
        temp = temp->right;
    }
}

