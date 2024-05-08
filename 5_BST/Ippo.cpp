#include <iostream>
using namespace std;

struct NodoBST{
    int data;
    NodoBST* father;
    NodoBST* right;
    NodoBST* left;
    NodoBST() : data(0), right(nullptr), left(nullptr){}
    NodoBST(int _data) : data(_data), right(nullptr), left(nullptr){}
};

class Solution{
public:
    NodoBST* root = nullptr; //incializa sin nodos
    // O(nlog(n))
    void insert(NodoBST* &_ActualRoot, int _val){
        if (_ActualRoot == nullptr) _ActualRoot = new NodoBST(_val);
        else{
            if(_ActualRoot->data < _val ){ 
                insert(_ActualRoot->right, _val);
            } 
            else if (_val < _ActualRoot->data){
                insert(_ActualRoot->left, _val);
            }
        }
    }
    void insert(int val){
        insert(root, val);
    }

    // Busqueda O(log(n)) dependiendo del arbol si es completo sí 
    NodoBST* search(NodoBST* _ActualRoot, int _val){        // La vaina es que hará un return de un return:
        if (_ActualRoot == nullptr) {  
            cout << "Valr no encotrado";                 // En plan return search |    <--> esperando una respuesta del search siguiente
            return nullptr;                               //                      search | <--> esperando una respuesta del search siguiente
        }                                               //                                 ...
        else if( _ActualRoot->data == _val){            // Una vez que lo termina, todos retornan true por el else if, entonces uno retorna true
            return _ActualRoot;                                // al anterior y ese le retorna true al anterior y así.
        } 
        else {
            if(_ActualRoot->data < _val ){ 
                // cout << "derecha " << endl;
                return search(_ActualRoot->right, _val);
            } 
            else if (_val < _ActualRoot->data){
                // cout << "izquierda" << endl;
                return search(_ActualRoot->left, _val);
            }
        }
        return _ActualRoot;
    }    
    NodoBST* search(int val){
        return search(root, val);
    }
    // Find
    NodoBST* FinMin(NodoBST* _ActualRoot){
        if(_ActualRoot == nullptr) return _ActualRoot;
        else if(_ActualRoot->left == nullptr){
            return _ActualRoot;
        }
        return FinMin(_ActualRoot->left);
        
    }

    NodoBST* erase(NodoBST* &_ActualRoot, int _val){
        // Case 0: Tree doesn't exist
        if(_ActualRoot == nullptr){cout << "NO";  return nullptr;}
        // Busqueda
        else if(_val < _ActualRoot->data) _ActualRoot->left = erase(_ActualRoot->left, _val); 
        else if(_val > _ActualRoot->data) _ActualRoot->right = erase(_ActualRoot->right, _val);         
        else{ // program find it
            // Case 1: No tiene hijos
            if(_ActualRoot->left == nullptr && _ActualRoot->right == nullptr){
                delete _ActualRoot;
                _ActualRoot = nullptr;
                return _ActualRoot;
            }
            // Case 2: Tiene un hijo
            else if(_ActualRoot->left == nullptr){ // solo esta de hijo el derecho
                NodoBST* temp = _ActualRoot;
                _ActualRoot = _ActualRoot->right;
                return _ActualRoot;
            }
            else if(_ActualRoot->right == nullptr){
                NodoBST* temp = _ActualRoot;
                _ActualRoot = _ActualRoot->left;
                return _ActualRoot;
            }
            //Caso 3: Tiene 2 hijos
            else{
                // Buscar un minimo(derecha)
                _ActualRoot->data = FinMin(_ActualRoot->right)->data; // 
                _ActualRoot->right = erase(_ActualRoot->right, _ActualRoot->data); // elimina el nodo que se movio y lo reemplaza
                return _ActualRoot;
            }
        }
        return _ActualRoot;
    }
    // Delete
    void erase(int val){
        erase(root, val); 
    }   
};

int main(){
    Solution sol;
    sol.insert(10); // agrega 3
    // // cout << sol.root->data << endl; // verify
    sol.insert(50);
    sol.insert(11);
    sol.insert(60);
    sol.insert(54);
    // cout << (sol.root->right)->data << endl;
    cout << sol.root->right->data << endl;
    sol.erase(50);
    cout << sol.root->right->data << endl;
}   