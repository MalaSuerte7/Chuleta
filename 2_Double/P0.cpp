#include <iostream>
using namespace std;

struct DoubleN{
    int val;
    DoubleN* next;
    DoubleN* prev;
    DoubleN() : val(0), next(nullptr), prev(nullptr) {}
    DoubleN(int x) : val(x), next(nullptr), prev(nullptr) {}
    DoubleN(int x,  DoubleN *prev,  DoubleN *next) : val(x), prev(prev), next(next) {}
};

class Solution{

};

int main(){
    DoubleN* a = new DoubleN(1);
    DoubleN* b = new DoubleN(2, a, nullptr);
    DoubleN* c = new DoubleN(3, b, nullptr);

    a->next = b;
    b->next = c;
    

    
}