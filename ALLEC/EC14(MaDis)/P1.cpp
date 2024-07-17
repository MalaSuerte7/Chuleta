// Integrantes: Alexis Raza - Francisco Calle
// P1
#include <iostream>
#include <tuple>
using namespace std;

// Nodo principal
class Node {
public:
    int row;
    int col;
    int value;
    Node* next;
    Node(int r, int c, int v) : row(r), col(c), value(v), next(nullptr) {}
};

// Estructura LinkedList (Lista simplemente enlazada)
class LinkedList {
private:
    Node* head;

public:    
    LinkedList() : head(nullptr) {}

    bool empty() { return !head; }

    void insert(int row, int col, int value) {
        auto* newNode = new Node{row, col, value};
        if (empty()) {
            head = newNode;
        } else {
            auto* current = head;
            while (current->next) {
                current = current->next;
            }
            current->next = newNode;
        }
    }

    // imprime cada tupla de valores (i, j, value)
    void print() {
        auto* current = head;
        while (current) {
            cout << "(" << current->row + 1 << ", " << current->col << ", " << current->value << ") "; // +1 (cantidad de filas contadas desde 1)
            current = current->next;
        }
    }
};

// Función que transforma la matriz de coordenadas (i, j, value) en su representación enlazada
LinkedList** transformToLinkedList(int rows, int cols, int numElements, int matrix[][3]) {
    // creo la matriz dinámica
    auto* linkedMatrix = new LinkedList*[rows];
    
    // reservo espacio de memoria
    for (int i = 0; i < rows; ++i) {
        linkedMatrix[i] = new LinkedList();
    }
    
    for (int i = 0; i < numElements; ++i) {
        int row = matrix[i][0] - 1; // cuento desde la fila 0 según la estructura ya que en la realidad se cuenta desde 1 uwu
        int col = matrix[i][1];
        int value = matrix[i][2];
        linkedMatrix[row]->insert(row, col, value);
    }
    
    return linkedMatrix;
}

// Test
int main() {
    int rows = 9, cols = 9, numElements = 10;
    // matriz de tupla de valores = {fila, columna, valor}
    int matrix[10][3] = {{2, 1, 3}, {2, 2, 5}, {2, 7, 9}, {3, 7, 5}, {4, 5, 5}, {4, 9, 22},
                          {6, 5, 5}, {7, 2, 5}, {7, 8, 5}, {9, 9, 5}};
    
    auto* linkedMatrix = transformToLinkedList(rows, cols, numElements, matrix);
    
    for (int i = 0; i < rows; ++i) {
        cout << "Row " << i + 1 << ": ";
        linkedMatrix[i]->print(); // (fila, columna, valor)
        cout << endl;
    }
    
    return 0;
}
