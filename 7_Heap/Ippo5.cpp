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

      // update -- heapfyup
      while(i != 0 && heapVec[parent(i)] > heapVec[i]){
        swap(heapVec[i], heapVec[parent(i)]);
        i = parent(i); // iterativamente
      }
    }

    void heapifyDown(int i){
      int l = left(i);
      int r = right(i);
      int smallest = i;

      if((l < size) && (heapVec[l] < heapVec[smallest])){
        smallest = l;
      }
      if ((r < size) && (heapVec[r] < heapVec[smallest])){
        smallest = r;
      }
      
      if(smallest != i){
        swap(heapVec[i], heapVec[smallest]);
        heapifyDown(smallest);
      }
    }

    int extracMin(){
      if(size == 0){
        cout << "Empty" << endl;
      } else if(size==1){
        size--;
        return heapVec[0];
      } else {
        int min = heapVec[0];

        heapVec[0] = heapVec[size - 1];
        size--;
        heapifyDown(0);

        return min;
      }
    }

    void printHeap(){
      int power = 0;
      int value = 1;
      for (int i = 0; i < size; i++){
        if(i == value){
          cout << endl;
          power+=1;
          value+= (1<<power);
        }
        cout << heapVec[i] << " ";
      }
    cout << endl;
    }
};

int main(){

}