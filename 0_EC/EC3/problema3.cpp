

/*
Diseñe una estructura de datos para almacenar el recuento de cadenas con la capacidad de devolver
las cadenas con recuentos mínimo y máximo.
Implementar la clase AllOne:
AllOne() Inicializa el objeto de la estructura de datos.
inc(String key) Incrementa el recuento de la clave de cadena en 1. Si la clave no existe en la
estructura de datos, insértela con el recuento 1.
dec(String key) Disminuye el recuento de la clave de cadena en 1. Si el recuento de la clave es
0 después de la disminución, elimínelo de la estructura de datos. Se garantiza que la clave existe
en la estructura de datos antes del decremento.
getMaxKey() Devuelve una de las claves con el recuento máximo. Si no existe ningún elemento,
devuelve una cadena vacía .
getMinKey() Devuelve una de las claves con el recuento mínimo. Si no existe ningún elemento,
devuelve una cadena vacía .
Tenga en cuenta que cada función debe ejecutarse en una complejidad de tiempo promedio O(1).
class AllOne {
public:
AllOne() {
}
void inc(string key) {
}
void dec(string key) {
}
string getMaxKey() {
}
string getMinKey() {
}
};
Example 1:
Input
["AllOne", "inc", "inc", "getMaxKey", "getMinKey", "inc", "getMaxKey", "getMinKey"]
[[], ["hello"], ["hello"], [], [], ["leet"], [], []]
Output
[null, null, null, "hello", "hello", null, "hello", "leet"]
Explanation
AllOne allOne = new AllOne();
allOne.inc("hello");
allOne.inc("hello");
allOne.getMaxKey(); // return "hello"
allOne.getMinKey(); // return "hello"
allOne.inc("leet");
allOne.getMaxKey(); // return "hello"
*/
#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

// struct Dub{
//     int key;
//     string str;
//     Dub* next;
//     Dub* prev;
//     Dub() : key(0), str(""), prev(nullptr), next(nullptr){}
//     Dub(int _key,string _str) : key(0), str(""), prev(nullptr), next(nullptr){} 
// };

class AllOne {
    unordered_map<string, int> co; // No fue posible con mi struct

public:
    AllOne() {}

    void inc(string key) {
        co[key]++; //suma
    }

    void dec(string key) {
        if (co.find(key) != co.end()) {
            co[key]--; // resta
            if (co[key] == 0)
                co.erase(key); 
        }
    }

    string getMaxKey() {
        int maxCount = 0;
        string maxKey = "";
        for (auto i = co.begin(); i != co.end(); ++i) {
            if (i->second > maxCount) {
                maxCount = i->second;
                maxKey = i->first;
            }
        }
        return maxKey;
    }

    string getMinKey() {
        if (co.empty())
            return "";
        int minCount = INT_MAX;
        string minKey = "";
        for (auto i = co.begin(); i != co.end(); ++i) {
            if (i->second < minCount) {
                minCount = i->second;
                minKey = i->first;
            }
        }
        return minKey;
    }
};

int main() {
    AllOne allOne;
    allOne.inc("hello");
    allOne.inc("hello");
    cout << allOne.getMaxKey() << endl; // return "hello"
    cout << allOne.getMinKey() << endl; // return "hello"
    allOne.inc("leet");
    cout << allOne.getMaxKey() << endl; // return "hello"
    return 0;
}

/*
#include <iostream>
#include <string>
using namespace std;

struct Dub{
    int key;
    string str;
    Dub* next;
    Dub* prev;
    Dub() : key(0), str(""), prev(nullptr), next(nullptr){}
    Dub(int _key,string _str) : key(0), str(""), prev(nullptr), next(nullptr){} 
};

class AllOne {
    Dub* head = nullptr;
    Dub* tail = nullptr;
    Dub* temp;

public:
    AllOne() {}

    void inc(string key) {
        Dub* ne = new Dub(key.length(), key);
        if(head == nullptr){ 
            head = ne; 
            tail = ne;
        }
        temp = head;
        while(temp->str != key){
            if(temp->next == nullptr){
                temp->next = ne;
                ne->prev = temp;
                tail = ne;
            }
            temp = temp->next;
        }
        if(temp->str == key){ 
            (temp->key)++; 
        }
    }

    void dec(string key) {
        temp = head;
        while(temp->str != key){
            temp = temp->next;
        }
        (temp->key)--;
        if(temp->key == 0){
            if(temp->prev != nullptr && temp->next != nullptr){
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
            }
            else if(temp->prev == nullptr && temp->next != nullptr){
                head = temp->next;
                temp->next->prev = nullptr;
            }
            else if(temp->prev != nullptr && temp->next == nullptr){
                tail = temp->prev;
                temp->prev->next = nullptr;
            }
            else{
                head = nullptr;
                tail = nullptr;
            }
            delete temp;
        }
    }

    string getMaxKey() {
        temp = head;
        int maxKey = 0;
        string maxStr = "";
        while(temp != nullptr){
            if(temp->key > maxKey){
                maxKey = temp->key;
                maxStr = temp->str;
            }
            temp = temp->next;
        }
        return maxStr;
    }

    string getMinKey() {
        temp = head;
        int minKey = INT_MAX;
        string minStr = "";
        while(temp != nullptr){
            if(temp->key < minKey){
                minKey = temp->key;
                minStr = temp->str;
            }
            temp = temp->next;
        }
        return minStr;
    }
};

int main() {
    AllOne allOne;
    allOne.inc("hello");
    allOne.inc("hello");
    cout << allOne.getMaxKey() << endl; // return "hello"
    cout << allOne.getMinKey() << endl; // return "hello"
    allOne.inc("leet");
    cout << allOne.getMaxKey() << endl; // return "hello"
    return 0;
}

*/