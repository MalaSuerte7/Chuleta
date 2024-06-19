#include <iostream>
using namespace std;

class BTreeNode{
int *keys; // array of keys(values like [1 13 65 23])
int t; // the less amount of keys that keys can have
BTreeNode** C; // pointer to an array of childs like vectors
int n; //actual numbers of keys in int keys
bool leaf; // is a leaf??
public:
    BTreeNode(int _t, bool _leaf){
        this->t = _t;
        this->leaf = _leaf;
        //allocate memory
        this->keys = new int[2*t-1]; // maximun of keys
        this->C = new BTreeNode*[2*t]; // maximun of Nodes
        n = 0; // n is 0 at start, so many times
    }
    // Insertion
    // Split
    // Traverse
    // Search
};