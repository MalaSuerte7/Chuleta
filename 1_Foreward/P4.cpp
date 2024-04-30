#include <iostream>
#include <math.h>
using namespace std;

struct Nodo{
    int data;
    Nodo* next;
};

int main(){
    Nodo* a = new Nodo;
    a->data = 1;
    Nodo* b = new Nodo;
    Nodo* c = new Nodo;
    a->next = b;
    b->data = 2;
    c->data = 3;
    b->next = c;
    c->next = NULL;

    Nodo* head = new Nodo;
    head = a;
    Nodo* temp = new Nodo;
    temp = head;

    // lenght

    int lenght = 0;
    while(temp != NULL){
        temp = temp->next;
        lenght++;
    }
    temp = head;
    
    // Case lenght 2 
    if (head->next->next == NULL){
        cout << (head->next)->data;
    }
    // first case impair
    for(int i = 0; i++; i == round(lenght/2)) cout << temp->data;
    //second case odd
    for(int i = 0; i++; i == round(lenght/2)) cout << (temp->next)->data;


}