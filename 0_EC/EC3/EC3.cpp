//Nombres : Francisco Calle, Jimena Mamani, Alexis Raza

// P1
#include <iostream>
using namespace std;


struct Node
{
  int val;
  Node *next;
  Node *prev;
  Node *child;
  Node(int value) : val(value), next(nullptr), prev(nullptr), child(nullptr) {}
  Node(int value, Node *_next, Node *_prev) : val(value), next(_next), prev(_prev), child(nullptr) {}
};

class ChildLinkedList
{
private:
  int nodes = 0;
  Node *head = nullptr;
  Node *tail = nullptr;

public:
  int size() { return nodes; }

  bool isEmpty() { return size() == 0; }

  // O(1)
  void push_back(int elem)
  {
    if (isEmpty())
    {
      head = tail = new Node{elem};
    }
    else
    {
      tail->next = new Node{elem, nullptr, tail};
      tail = tail->next;
    }
    nodes++;
  }

  Node *search(int key, Node *nodito)
  {
    if (nodito == nullptr || nodito->val == key)
    {
      return nodito;
    }

    Node *found = search(key, nodito->child);
    if (found != nullptr)
    {
      return found;
    }

    return search(key, nodito->next);
  }

  void push_back(int nodePrev, int nodeNext)
  {
    Node *temp = search(nodePrev, head);
    if (temp != nullptr)
    {
      Node *nuevo = new Node{nodeNext, nullptr, temp};
      temp->next = nuevo;
      // Node(T value, Node<T> *_next, Node<T> *_prev) : val(value), next(_next), prev(_prev), child(nullptr) {}
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
    Node *padre = search(p, head);
    if (padre)
    {
      Node *hijo = new Node{h};
      padre->child = hijo;
      nodes++;
      // Node(T value = T()) : val(value), next(nullptr), prev(nullptr), child(nullptr) {}
    }
    else
    {
      cout << "Parent node not found: " << p << endl;
    }
  }

  void display()
  {
    for (Node *temp = head; temp != nullptr; temp = temp->next)
    {
      cout << temp->val << " ";
    }
    cout << endl;
  }

  void display_flatten()
  {
    if (isEmpty())
    {
      cout << "Lista vacía" << endl;
      return;
    }

    flatten(head);
    cout << endl;
  }

  void flatten(Node *nodito)
  {
    if (nodito == nullptr)
      return; // Si es NULL no hay nada que hacer

    // Añadir el dato
    cout << nodito->val << " ";
    // Recorrer los hijos y llamar recursivamente
    if (nodito->child)
    {
      flatten(nodito->child);
    }
    if (nodito->next)
    {
      flatten(nodito->next);
    }
  }
};

// P2
#include <iostream>
using namespace std;

struct Node{
  int key;
  int value;
  Node *next;
  Node *prev;
  Node() : key(0), value(0), next(nullptr), prev(nullptr) {} // modif
  Node(Node *_next) : key(0), value(0), next(_next), prev(nullptr) {} // modif
  Node(int _key, int _value) : key(_key), value(_value), next(nullptr), prev(nullptr) {} // modificar
};

class LRUCache {
  int capacity;
  int size=0;
  Node *head;
  Node *tail;
  
  Node *findNode(int key){
    Node *curr = head->next;
    while (curr != tail){
      if (curr->key == key){
        return curr;
      }
      curr = curr->next;
    }
    return nullptr; // nodo no encontrado
  }
public:
    LRUCache(int capacity) : capacity(capacity){
      tail = new Node();
      head = new Node(tail);
      tail->prev = head;
    }

    int get(int key) {
      Node *node = findNode(key);
      if (node != nullptr){
        
        node->prev->next = node->next;
        node->next->prev = node->prev;

        node->next = head->next;
        node->prev = head;
        head->next->prev = node;
        head->next = node;
        return node->value;
      }else{
        return -1;
      }
    }
    
    void put(int key, int value) {

      Node *node = findNode(key);
      if (node != nullptr){
        node->value = value;
        node->prev->next = node->next;
        node->next->prev = node->prev;

        node->next = head->next;
        node->prev = head;
        head->next->prev = node;
        head->next = node;
      }else{
        if (size >= capacity){
          Node* toRemove = tail->prev;
          toRemove->prev->next = toRemove->next;
          toRemove->next->prev = toRemove->prev;

          delete toRemove;
          size--;
        }else{
          Node* newNode = new Node(key,value);
          newNode->next = head->next;
          newNode->prev = head;
          head->next->prev = newNode;
          head->next = newNode;
          size++;
        }

      }
    }
};



// P3
#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

// struct Dub{
//     int key;
//     string str;
//     Dub* next;
//     Dub* prev;
//     Dub() : key(0), str(""), prev(nullptr), next(nullptr){}
//     Dub(int _key,string _str) : key(0), str(""), prev(nullptr), next(nullptr){} 
// };

class AllOne {
    unordered_map<string, int> co; // No fue posible con mi struct

public:
    AllOne() {}

    void inc(string key) {
        co[key]++; //suma
    }

    void dec(string key) {
        if (co.find(key) != co.end()) {
            co[key]--; // resta
            if (co[key] == 0)
                co.erase(key); 
        }
    }

    string getMaxKey() {
        int maxCount = 0;
        string maxKey = "";
        for (auto i = co.begin(); i != co.end(); ++i) {
            if (i->second > maxCount) {
                maxCount = i->second;
                maxKey = i->first;
            }
        }
        return maxKey;
    }

    string getMinKey() {
        if (co.empty())
            return "";
        int minCount = INT_MAX;
        string minKey = "";
        for (auto i = co.begin(); i != co.end(); ++i) {
            if (i->second < minCount) {
                minCount = i->second;
                minKey = i->first;
            }
        }
        return minKey;
    }
};
