#include <iostream> 
using namespace std;

struct Nodo{
    int data;
    Nodo* next;
};

Nodo* front(Nodo* head){
    return head;
}

Nodo* back(Nodo* te){
    while(te->next != NULL){
        te = te->next;
    }
    return te; 
}

void push_front(Nodo** _head, int n){
    Nodo* z = new Nodo;
    z->data = n;
    z->next = *_head;
    *_head = z;
}

void push_back(Nodo* temp, Nodo** _head, int n){
    Nodo* x = new Nodo;
    x->data = n;
    x->next = NULL;
    // back 
    Nodo* ba = new Nodo;
    ba = back(temp);
    ba->next = x;
}

Nodo* pop_front(Nodo** _head){
    // eliminar memoria con delete
    Nodo* save = new Nodo;
    save = (*_head)->next;
    delete *_head;
    *_head = save; 
    return *_head;
}

// verificar
Nodo* pop_back(Nodo** _head, Nodo* temp){
    while(temp->next->next != NULL){
        temp = temp->next;
    }
    delete temp->next;
    temp->next = NULL;
    return *_head;
}

class Forward_list{
    public:
    
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

    // Elemento del principio (recordar que los punteros se pierden)
    front(head);
    // Ultimo elemento
    back(temp);
    // Agregar al comienzo
    push_front(&head, 0); // (parece que se pued pasar por referencia)
        //cout << head->data << endl;
    // Agregar al final
    push_back(temp, &head, 4);
        //cout << (back(temp))->data;
    // Remueve el elemento del principio
    pop_front(&head);
        //cout << head->data;
    //Remueve el elemento del ultimo
    pop_back(&head, temp);
        //cout << (back(temp))->data;
    //Retorna el elemento en la posición indicada
    
}