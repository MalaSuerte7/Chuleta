#include <iostream>
#include <math.h>
using namespace std;

struct Nodo{
    int data;
    Nodo* next;
};

int main(){
    Nodo* a = new Nodo;
    Nodo* b = new Nodo;
    Nodo* d = new Nodo;
    Nodo* f = new Nodo;
    Nodo* t = new Nodo;


    a->data = 1;
    b->data = 2;
    d->data = 3;
    f->data = 4;
    t->data = 5;

    a->next = b;
    b->next = d;
    d->next = f;
    f->next = t;
    t->next = NULL;

    Nodo* temp = new Nodo;
    Nodo* head = new Nodo;
    head = a;
    temp = head;

    // 1. lenght
    int lenght = 0;
    while(temp != NULL){
        temp = temp->next;
        lenght++;
    }
    temp = head;

    // invertir
    Nodo* prev = NULL;
    Nodo* curr = head;
    Nodo* temp = NULL;

    while(temp != NULL){
        temp = curr->next; // Almacena el siguiente nodo
        curr->next = prev; // Invierte el puntero next
        prev = curr;       // Avanza el puntero previo
        curr = temp;       // Avanza el puntero actual
    }
    
}