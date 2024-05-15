#include <iostream>
#include <vector>
#include <algorithm> // Necesario para la función max
using namespace std;

struct NodoAVL{
    int data;
    NodoAVL* right;
    NodoAVL* left;
    int height; // Altura del nodo
    NodoAVL() : data(0), right(nullptr), left(nullptr), height(1) {}
    NodoAVL(int _data) : data(_data), right(nullptr), left(nullptr), height(1) {}
};

class Solution{
public:
    NodoAVL* root = nullptr;

    int getHeight(NodoAVL* node) {
        if (node == nullptr) return 0;
        return node->height;
    }

    int getBalanceFactor(NodoAVL* node) {
        if (node == nullptr) return 0;
        return getHeight(node->left) - getHeight(node->right);
    }

    NodoAVL* rightRotate(NodoAVL* y) {
        NodoAVL* x = y->left;
        NodoAVL* T2 = x->right;

        // Realiza la rotación
        x->right = y;
        y->left = T2;

        // Actualiza alturas
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

        return x;
    }

    NodoAVL* leftRotate(NodoAVL* x) {
        NodoAVL* y = x->right;
        NodoAVL* T2 = y->left;

        // Realiza la rotación
        y->left = x;
        x->right = T2;

        // Actualiza alturas
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

        return y;
    }

    NodoAVL* insert(NodoAVL* node, int key) {
        if (node == nullptr) return new NodoAVL(key);

        if (key < node->data) {
            node->left = insert(node->left, key);
        } else if (key > node->data) {
            node->right = insert(node->right, key);
        } else {
            // Claves duplicadas no están permitidas en un árbol AVL
            return node;
        }

        // Actualiza la altura de este nodo ancestro
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));

        // Obtiene el factor de balance de este nodo ancestro
        int balance = getBalanceFactor(node);

        // Si el nodo se desbalancea, hay 4 casos

        // Caso Izquierda-Izquierda
        if (balance > 1 && key < node->left->data) {
            return rightRotate(node);
        }

        // Caso Derecha-Derecha
        if (balance < -1 && key > node->right->data) {
            return leftRotate(node);
        }

        // Caso Izquierda-Derecha
        if (balance > 1 && key > node->left->data) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // Caso Derecha-Izquierda
        if (balance < -1 && key < node->right->data) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        // El nodo está balanceado
        return node;
    }

    void insert(int key) {
        root = insert(root, key);
    }

    NodoAVL* minValueNode(NodoAVL* node) {
        NodoAVL* current = node;
        while (current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    NodoAVL* erase(NodoAVL* root, int key) {
        if (root == nullptr) return root;

        if (key < root->data) {
            root->left = erase(root->left, key);
        } else if (key > root->data) {
            root->right = erase(root->right, key);
        } else {
            if (root->left == nullptr || root->right == nullptr) {
                NodoAVL* temp = root->left ? root->left : root->right;

                // No child case
                if (temp == nullptr) {
                    temp = root;
                    root = nullptr;
                } else {
                    *root = *temp; // Copy the contents of the non-empty child
                }

                delete temp;
            } else {
                // Node with two children: Get the inorder successor (smallest in the right subtree)
                NodoAVL* temp = minValueNode(root->right);

                // Copy the inorder successor's data to this node
                root->data = temp->data;

                // Delete the inorder successor
                root->right = erase(root->right, temp->data);
            }
        }

        // If the tree had only one node then return
        if (root == nullptr) return root;

        // Update height of the current node
        root->height = 1 + max(getHeight(root->left), getHeight(root->right));

        // Get the balance factor of this node (to check whether this node became unbalanced)
        int balance = getBalanceFactor(root);

        // If this node becomes unbalanced, then there are 4 cases

        // Left Left Case
        if (balance > 1 && getBalanceFactor(root->left) >= 0) {
            return rightRotate(root);
        }

        // Left Right Case
        if (balance > 1 && getBalanceFactor(root->left) < 0) {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }

        // Right Right Case
        if (balance < -1 && getBalanceFactor(root->right) <= 0) {
            return leftRotate(root);
        }

        // Right Left Case
        if (balance < -1 && getBalanceFactor(root->right) > 0) {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
    }

    void erase(int key) {
        root = erase(root, key);
    }

    void inorderTraversal(NodoAVL* root, vector<int>& inorder) {
        if (root == nullptr) return;
        inorderTraversal(root->left, inorder);
        inorder.push_back(root->data);
        inorderTraversal(root->right, inorder);
    }

    void postorderTraversal(NodoAVL* root, vector<int>& postorder) {
        if (root == nullptr) return;
        postorderTraversal(root->left, postorder);
        postorderTraversal(root->right, postorder);
        postorder.push_back(root->data);
    }

    void preorderTraversal(NodoAVL* root, vector<int>& preorder) {
        if (root == nullptr) return;
        preorder.push_back(root->data);
        preorderTraversal(root->left, preorder);
        preorderTraversal(root->right, preorder);
    }

    bool isValidBSTUtil(NodoAVL* root, int min_val, int max_val) {
        if (root == nullptr) return true;

        if (root->data < min_val || root->data > max_val) return false;

        return isValidBSTUtil(root->left, min_val, root->data - 1) && isValidBSTUtil(root->right, root->data + 1, max_val);
    }

    bool isValidBST() {
        return isValidBSTUtil(root, INT_MIN, INT_MAX);
    }
};

int main() {
    Solution sol;
    sol.insert(10);
    sol.insert(50);
    sol.insert(11);
    sol.insert(60);
    sol.insert(54);

    vector<int> inorder;
    sol.inorderTraversal(sol.root, inorder);
    for (int val : inorder) {
        cout << val << " ";
    }
    cout << endl;

    vector<int> postorder;
    sol.postorderTraversal(sol.root, postorder);
    for (int val : postorder) {
        cout << val << " ";
    }
    cout << endl;

    vector<int> preorder;
    sol.preorderTraversal(sol.root, preorder);
    for (int val : preorder) {
        cout << val << " ";
    }
    cout << endl;

    cout << (sol.isValidBST() ? "Yes" : "No") << endl;

    return 0;
}
