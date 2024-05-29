#include <iostream>
#include <vector>
using namespace std;

// ------------------------------------------------------------------------------------------
struct Node
{
  int val;
  Node* next;
};

class Queue
{
  Node* front;
  Node* rear;
  int nodes;

public:
  Queue() : nodes(0) { front = rear = nullptr; }

  int size(){return nodes;}

  int _front(){return front->val;}

  int _rear(){return rear->val;}

  bool empty(){
    return (!front && !rear) ? true : false;
  }

  void enqueue(int homework){
    Node* temp = new Node();
    temp->val = homework;
    temp->next = nullptr;

    if (empty()){front = rear = temp;}
    else{
      rear->next = temp;
      rear = temp;
    }
    nodes++;
  };

  void dequeue(){
    Node* temp;
    if (empty()){
        cout << endl << "Queue vacio." << endl;}
    else{
      temp = front;
      if (front == rear)
        rear = rear->next; // si el tamaño de la cola es 1;
      front = front->next;
      nodes--;
    }
  };
};

// Fin del Queue ---------------------------------------------------------------------

// Inicio del heap -------------------------------------------------------------------
struct MaxHeap{
    int val;
    MaxHeap* left;
    MaxHeap* right;
    MaxHeap() : val(0), left(nullptr), right(nullptr){}
    MaxHeap(int _val) : val(_val), left(nullptr), right(nullptr){}
    // real metodos
    vector<int> heapVec;
    int parent(int num){ }
    //
    void insert(int val){
        
    }
};

int main(){

}