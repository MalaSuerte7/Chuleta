#include <iostream>
using namespace std;

class AllOne {
public:
    AllOne() {}
    void inc(string key) {}
    void dec(string key) {}
    string getMaxKey() {}
    string getMinKey() {}
};

/* Example 1:
Input
["AllOne", "inc", "inc", "getMaxKey", "getMinKey", "inc", "getMaxKey", "getMinKey"]
[[], ["hello"], ["hello"], [], [], ["leet"], [], []]
Output
[null, null, null, "hello", "hello", null, "hello", "leet"]
*/

int main(){
    AllOne allOne = AllOne();
    allOne.inc("hello");
    allOne.inc("hello");
    allOne.getMaxKey(); // return "hello"
    allOne.getMinKey(); // return "hello"
    allOne.inc("leet");
    allOne.getMaxKey(); // return "hello"
}