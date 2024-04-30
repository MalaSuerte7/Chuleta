#include <iostream>
using namespace std;

class Node {
public:
    int val;
    Node* prev;
    Node* next;
    Node* child;

    Node(int _val) : val(_val), next(nullptr), prev(nullptr), child(nullptr) {}
    Node(int _val, Node* _next, Node* _prev) : val(_val), next(_next), prev(_prev), child(nullptr) {}

};


class Solution {
public:
    Node* flatten(Node* head) {
        
    }
};

/*
#include <iostream>
using namespace std;
/*
template <typename T>
struct Node
{
  T data;
  Node<T> *next;
  Node<T> *prev;
  Node<T> *child;
  Node(T value = T()) : data(value), next(nullptr), prev(nullptr), child(nullptr) {}
  Node(T value, Node<T> *_next, Node<T> *_prev) : data(value), next(_next), prev(_prev), child(nullptr) {}
};

template <typename T>
class ChildLinkedList
{
private:
  int nodes = 0;
  Node<T> *head = nullptr;
  Node<T> *tail = nullptr;

public:
  int size() { return nodes; }

  bool isEmpty() { return size() == 0; }

 // O(1)
  void push_back(T elem)
  {
    if (isEmpty())
    {
      head = tail = new Node<T>{elem};
    }
    else
    {
      tail->next = new Node<T>{elem, nullptr, tail};
      tail = tail->next;
    }
    nodes++;
  }

  Node<int> *search(int key, Node<int> *nodito)
  {
    if (nodito == nullptr || nodito->data == key)
    {
      return nodito;
    }

  Node<T> *found = search(key, nodito->child);
    if (found != nullptr)
    {
      return found;
    }

    return search(key, nodito->next);
  }

  void push_back(int nodePrev, int nodeNext)
  {
    Node<int> *temp = search(nodePrev, head);
    if (temp != nullptr)
    {
      Node<int> *nuevo = new Node<int>{nodeNext, nullptr, temp};
      temp->next = nuevo;
      if (temp == tail)
      {
        tail = nuevo;
      }
      nodes++;
    }
    else
    {
      cout << "Node prev not found: " << nodePrev << endl;
    }

 }

  void insert_child(int p, int h)
  {
    Node<int> *padre = search(p, head);
    if (padre)
    {
      Node<int> *hijo = new Node<int>{h};
      padre->child = hijo;
      nodes++;
    }
    else
    {
      cout << "Parent node not found: " << p << endl;
    }
  }

  void display()
  {
    for (Node<T> *temp = head; temp != nullptr; temp = temp->next)
    {
      cout << temp->data << " ";
    }
    cout << endl;
  }

void display_aplanar()
  {
    if (isEmpty())
    {
      cout << "Lista vacía" << endl;
      return;
    }

    aplanar(head);
    cout << endl;
  }

  void aplanar(Node<int> *nodito)
  {
    if (nodito == nullptr)
      return; // Si es NULL no hay nada que hacer

    // Añadir el dato
    cout << nodito->data << " ";
    // Recorrer los hijos y llamar recursivamente
    if (nodito->child || nodito->next)
    {
      aplanar(nodito->child);
    }
    if (nodito->next)
    {
      aplanar(nodito->next);
    }
  }
};

int main()
{
  ChildLinkedList<int> c;
  c.push_back(1);
  c.push_back(2);
  c.push_back(3);
  c.push_back(4);
  c.push_back(5);
  c.push_back(6);

  // el padre - el hijo
  c.insert_child(3, 7);

  // nodo anterior - nodo siguiente
  c.push_back(7, 8);
  c.push_back(8, 9);
  c.push_back(9, 10);

  // el padre - el hijo
  c.insert_child(8, 11);

  // nodo anterior - nodo siguiente
  c.push_back(11, 12);

  c.display_aplanar();

  return 0;
}
*/