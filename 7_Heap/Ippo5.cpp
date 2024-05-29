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


/*
    int val;
    MaxHeap* left;
    MaxHeap* right;
    MaxHeap() : val(0), left(nullptr), right(nullptr){}
    MaxHeap(int _val) : val(_val), left(nullptr), right(nullptr){}
*/
// Inicio del heap -------------------------------------------------------------------
struct minHeap{
    int size;
    int capacity;
    vector<int> heapVec;
    // metodos preliminares
    int parent(int nNum){return (nNum-1)/2; }
    int left(int nNum){return 2*nNum + 1;}
    int right(int nNum){ return 2*nNum + 2;}
    // Preliminares para el insert

    //Crear minHeap constructor
    minHeap(int _capacity){
      size = 0;
      capacity = _capacity;
      heapVec.resize(_capacity);
    }
    //  
    void insert(int inon){
      if(size==capacity){
        cout << "Max Capacity" << endl;
        return;
      }
      size++;
      int i = size - 1;
      heapVec[i] = inon;

      // update
      while(i != 0 && heapVec[parent(i)] > heapVec[i]){
        swap(heapVec[i], heapVec[parent(i)]);
        i = parent(i); // iterativamente
      }
    }
    
};

int main(){

}