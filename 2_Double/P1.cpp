#include <iostream>
using namespace std;

struct DoubleN{
    string page;
    DoubleN* next = nullptr;
    DoubleN* prev = nullptr;
    DoubleN() : page(" "), next(nullptr), prev(){}
    DoubleN(string _page) : page(_page), next(nullptr), prev(nullptr){}
};

class BrowserHistory {
DoubleN* head = new DoubleN;
public:
    BrowserHistory(string homepage) {
        //creado sin apuntar a nada pero este es head
        DoubleN* created = new DoubleN(homepage);
        this->head = created;
    }
    void visit(string url) {
        //crea un nuevo nodo
        DoubleN* neon = new DoubleN(url);
        // Asignar
        head->next = neon;
        neon->prev = head;
        // nuevo head 
        head = neon;
    }
    string back(int steps) {
        // mueve la cabeza al prev
        while(steps != 0){
            head = head->prev;
        }
    }
    string forward(int steps) {}
};

/**
* Your BrowserHistory object will be instantiated and called as such:
* BrowserHistory* obj = new BrowserHistory(homepage);
* obj->visit(url);
* string param_2 = obj->back(steps);
* string param_3 = obj->forward(steps);
*/

int main(){
    BrowserHistory browserHistory =  BrowserHistory("leetcode.com");
    browserHistory.visit("google.com"); // You are in ’leetcode.com’. Visit ’google.com’
    browserHistory.visit("facebook.com"); // You are in ’google.com’. Visit ’facebook.com’
    browserHistory.visit("youtube.com"); // You are in ’facebook.com’. Visit ’youtube.com’
    browserHistory.back(1); // You are in ’youtube.com’, move back to ’facebook.com’ return ’face-book.com’
    browserHistory.back(1); // You are in ’facebook.com’, move back to ’google.com’ return ’goo-gle.com’
    browserHistory.forward(1); // You are in ’google.com’, move forward to ’facebook.com’ return ’facebook.com’
    browserHistory.visit("linkedin.com"); // You are in ’facebook.com’. Visit ’linkedin.com’
    browserHistory.forward(2); // You are in ’linkedin.com’, you cannot move forward any steps.
    browserHistory.back(2); // You are in ’linkedin.com’, move back two steps to ’facebook.com’ thento ’google.com’. return ’google.com’
    browserHistory.back(7); // You are in ’google.com’, you can move back only one step to ’leetco-de.com’. return ’leetcode.com’
}