#include <iostream>
#include <vector>
using namespace std;

// Hagamos de 4 esta vez
struct B{
    // Tiene n valores 
    int maxK, actual; // maxK = Orden - 1 ; actual cuanto hay
    vector<int> values; // Un B tiene values en su nodo

    B(int orden) : maxK(orden - 1), actual(0){}
    // Metodos
    void nInsert(int num) {
        if(actual == 0) values.push_back(num);
        else if(actual >= maxK){
            split(values, num);
        }
        else{
            // esto para usar vectores y evitar que tome el valor más bajo O(log(actual)) <--> O(log n)
            auto place = lower_bound(values.begin(), values.begin()+actual, num); // incluso podría se más rapido si actual es minimo
            values.insert(place, num);
        }
        actual++;
    }

    void nInsert(vector<int> vls){
        //fill
        for(int i = 0; i < vls.size(); i++){
            nInsert(vls[i]);
        }
    }
    void split(vector<int> &_values, int num){
        // Se crea un nuevo nodo
        B* newRB = new B(maxK+1);
        B* newLB = new B(maxK+1);
        B* newFB = new B(maxK+1);

        // Dividir los valores en los nuevos nodos
        int middle_index = _values.size() / 2;
        vector<int> l(_values.begin(), _values.begin() + middle_index);
        vector<int> r(_values.begin() + middle_index, _values.end());

        newLB->nInsert(l); // Insertar valores izquierdos en el nuevo nodo izquierdo
        newFB->nInsert(num); // Insertar el nuevo valor en el nuevo nodo FB
        newRB->nInsert(r); // Insertar valores derechos en el nuevo nodo derecho

        // Limpiar _values y agregar solo los valores del nodo izquierdo
        _values = l;
        actual = _values.size(); // Actualizar el contador de elementos del nodo actual
    }

    
    void printNode(){
        for(int i = 0; i <= values.size()-1; i++){
            if(values[i] == -1){ cout << "null";}
            else{ cout << values[i] << " ";}
        }
    }
};  

int main(){
    int orden = 5;
    B goo(orden);
    goo.nInsert(10);goo.printNode(); cout << endl;
    goo.nInsert(11);goo.printNode(); cout << endl;    
    goo.nInsert(1);goo.printNode(); cout << endl;
    goo.nInsert(2);goo.printNode(); cout << endl;
    goo.nInsert(3);goo.printNode(); cout << endl;
}