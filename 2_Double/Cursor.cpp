#include <iostream>
using namespace std;

struct DoubleN{
    string txt;
    int masa;
    DoubleN* next = nullptr;
    DoubleN* prev = nullptr;
    DoubleN() : next(nullptr), prev(nullptr){}
    DoubleN(string _text) : next(nullptr), prev(nullptr), txt(_text){}

};

class TextEditor {
int pos = 0; 
DoubleN* head = new DoubleN;
public:
    TextEditor() {
        DoubleN* T = new DoubleN();
        T->txt = ""; T->masa = 0;
        head = T;
    }
    
    void addText(string text) {
        // agrego texto  y actualizo al cursor de 0 + lenght()
        // 
        // agrego el nodo
        DoubleN* n = new DoubleN();
        n->txt = text;
        if (head->masa == 0){
            head = n;
        }
        else{
            n->prev = head;
            head->next = n;
        }
    }
    
    int deleteText(int k) {
        
    }
    
    string cursorLeft(int k) {
        
    }
    
    string cursorRight(int k) {
        
    }
};

/**
 * Your TextEditor object will be instantiated and called as such:
 * TextEditor* obj = new TextEditor();
 * obj->addText(text);
 * int param_2 = obj->deleteText(k);
 * string param_3 = obj->cursorLeft(k);
 * string param_4 = obj->cursorRight(k);
 */

int main(){

}