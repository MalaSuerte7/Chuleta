#include <iostream>
#include <vector>
using namespace std;

struct BPlusTreeNode {
    vector<int> keys;
    vector<BPlusTreeNode*> children;
    BPlusTreeNode* next;
    bool leaf;
    int t;

    BPlusTreeNode(int _t, bool _leaf) : t(_t), leaf(_leaf), next(nullptr) {}

    void traverse() {
        int i;
        for (i = 0; i < keys.size(); i++) {
            if (!leaf) {
                children[i]->traverse();
            }
            cout << " " << keys[i];
        }
        if (!leaf) {
            children[i]->traverse();
        }
    }

    BPlusTreeNode* search(int k) {
        int i = 0;
        while (i < keys.size() && k > keys[i]) {
            i++;
        }

        if (i < keys.size() && keys[i] == k) {
            return this;
        }

        if (leaf) {
            return nullptr;
        }

        return children[i]->search(k);
    }

    void insertNonFull(int k) {
        int i = keys.size() - 1;

        if (leaf) {
            keys.push_back(0);
            while (i >= 0 && keys[i] > k) {
                keys[i + 1] = keys[i];
                i--;
            }
            keys[i + 1] = k;
        } else {
            while (i >= 0 && keys[i] > k) {
                i--;
            }

            if (children[i + 1]->keys.size() == 2 * t - 1) {
                splitChild(i + 1, children[i + 1]);
                if (keys[i + 1] < k) {
                    i++;
                }
            }
            children[i + 1]->insertNonFull(k);
        }
    }

    void splitChild(int i, BPlusTreeNode *y) {
        BPlusTreeNode *z = new BPlusTreeNode(y->t, y->leaf);
        z->keys.assign(y->keys.begin() + t, y->keys.end());

        if (!y->leaf) {
            z->children.assign(y->children.begin() + t, y->children.end());
        }

        y->keys.resize(t - 1);

        if (y->leaf) {
            z->next = y->next;
            y->next = z;
        }

        children.insert(children.begin() + i + 1, z);
        keys.insert(keys.begin() + i, y->keys[t - 1]);
    }
};

struct BPlusTree {
    BPlusTreeNode *root;
    int t;

    BPlusTree(int _t) : root(nullptr), t(_t) {}

    void traverse() {
        if (root != nullptr) {
            root->traverse();
        }
    }

    BPlusTreeNode* search(int k) {
        return (root == nullptr) ? nullptr : root->search(k);
    }

    void insert(int k) {
        if (root == nullptr) {
            root = new BPlusTreeNode(t, true);
            root->keys.push_back(k);
        } else {
            if (root->keys.size() == 2 * t - 1) {
                BPlusTreeNode *s = new BPlusTreeNode(t, false);
                s->children.push_back(root);
                s->splitChild(0, root);

                int i = 0;
                if (s->keys[0] < k) {
                    i++;
                }
                s->children[i]->insertNonFull(k);
                root = s;
            } else {
                root->insertNonFull(k);
            }
        }
    }
};

int main() {
    BPlusTree t(3); // Un B+ Tree con grado mínimo 3

    t.insert(10);
    t.insert(20);
    t.insert(5);
    t.insert(6);
    t.insert(12);
    t.insert(30);
    t.insert(7);
    t.insert(17);

    cout << "Traversal of the constructed tree is ";
    t.traverse();
    cout << endl;

    int k = 6;
    (t.search(k) != nullptr) ? cout << k << " is found\n" : cout << k << " is not found\n";

    k = 15;
    (t.search(k) != nullptr) ? cout << k << " is found\n" : cout << k << " is not found\n";

    return 0;
}
