/*
(6 pts) Una cadena es una cadena entre paréntesis válida (denominada VPS) si cumple uno de los
siguientes:
Es una cadena vacía ”, o un solo carácter no igual a ’(’ o ’)’,
Puede escribirse como AB (A concatenada con B), donde A y B son VPS, o
Puede escribirse como (A), donde A es un VPS.
De manera similar, podemos definir la profundidad de anidamiento depth(S) de cualquier VPS S de
la siguiente manera:
depth(”) = 0
depth(C) = 0, donde C es un string con un único caracter no igual a ’(’ o ’)’.
depth(A+B) = max(depth(A), depth(B)), donde A y B son VPS’s.
depth(’(’+ A + ’)’) = 1 + depth(A), donde (A) es un VPS.
Por ejemplo, ”, ’()()’ y ’()(()())’ son VPS’s (con una profundidad anidada de 0, 1 y 2) y ’)(’
y ’(()’ no son VPS’s.
Dado un VPS representado como un string s, devuelve la profundidad de anidación de s.
Ejemplo 1:
Input: s = "(1+(2*3)+((8)/4))+1"
Output: 3
Explicación:
El dígito 8 está dentro de 3 paréntesis anidados en la cadena.
Ejemplo 2:
Input: s = "(1)+((2))+(((3)))"
Output: 3
*/
#include <iostream>
using namespace std;

struct Stack
{
    int val;
    int min = 0; 
    Stack *prev;
    Stack() : val(0), prev(nullptr){}
    Stack(int _val): val(_val), prev(nullptr) {}
};

class Solution {
Stack *head;
int nodes;
public:
    Solution() {
        // constructor
        this->head = nullptr;
    }
    void push(int x) {
        Stack* new_nodo =  new Stack(x);
        //1. esta vacio 
        if (head == nullptr){
            this->head = new_nodo;}
        //2. Tiene almenos un elemento
        else{
            new_nodo->prev = this->head;
            this->head = new_nodo;
        }
    }
    int top() {
        return this->head->val;
    }
    bool empty() {
        if (head == nullptr){
            return true;
        }
        return false;
    }

    int pop() {
        if(head == nullptr) return 0;
        Stack* save = nullptr;
        //
        save = head;
        this->head = this->head->prev;
        // Delete
        int temps = save->val;
        delete save;
        return temps;
    }

    int maxDepth(string s) {
        int max_depth = 0;
        int current_depth = 0;
        for (char c : s){
            if (c == '('){
                current_depth++;
                max_depth = max(max_depth, current_depth);
            }
            else if (c == ')'){
                current_depth--;
            }
        }
        return max_depth;
    }
};

int main(){
    Solution sol;
    cout << sol.maxDepth("(1+(2*3)+((8)/4))+1") << endl; // 3
    cout << sol.maxDepth("(1)+((2))+(((3)))") << endl; // 3
    return 0;
}