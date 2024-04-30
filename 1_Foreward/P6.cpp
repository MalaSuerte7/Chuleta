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
    b->data = 0;
    d->data = 2;
    f->data = 3;
    t->data = 4;

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

    // 
    if(lenght % 2 != 0){
        int i = 0;
        while (i != round(lenght/2)){
            temp = temp->next;
            i++;
        }
        // cout << temp->data;
    }
    else{
        int i = 0;
        while (i != lenght/2){
            temp = temp->next;
            i++;
        }
        // cout << temp->data;
    }

    while(temp != NULL){
        cout << temp->data << " ";
        temp = temp->next;
    }
}