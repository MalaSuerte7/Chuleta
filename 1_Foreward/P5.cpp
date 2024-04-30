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

    a->data = 1;
    b->data = 0;
    d->data = 1;

    a->next = b;
    b->next = d;
    d->next = NULL;

    Nodo* temp = new Nodo;
    Nodo* head = new Nodo;
    head = a;
    temp = head;
    // Code
    // 1. lenght
    int lenght = 0;
    while(temp != NULL){
        temp = temp->next;
        lenght++;
    }
    temp = head;

    // Multiplicar 
    int num = 0;
    int c = lenght-1;

    while(temp != NULL){
        num += pow(2, c) * temp->data;
        c--;
        temp=temp->next;
    }
    cout << num;
}