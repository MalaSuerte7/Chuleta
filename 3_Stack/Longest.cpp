#include <iostream>
using namespace std;

//stack
struct Stack{
    int val;
    Stack* prev;
    Stack() : val(0), prev(nullptr){}
    Stack(int _val) : val(_val), prev(nullptr){}
};


class Solution {
// no vector, no libraries, just stack

public:
    int longestValidParentheses(string s) {
        Stack* head = nullptr;
        int max = 0;
        int count = 0;
        for (int i = 0; i < s.size(); i++){
            if (s[i] == '('){
                Stack* new_nodo = new Stack(i);
                new_nodo->prev = head;
                head = new_nodo;
            }
            else{
                if (head != nullptr){
                    Stack* save = head;
                    head = head->prev;
                    if (head == nullptr){
                        count = i - save->val + 1;
                    }
                    else{
                        count = i - head->val;
                    }
                    if (count > max){
                        max = count;
                    }
                }
            }
        }
        return max;
    }
};

int main(){
    // test
    Solution sol = Solution();
    cout << sol.longestValidParentheses("(()") << endl; // 2
    cout << sol.longestValidParentheses(")()())") << endl; // 4
    cout << sol.longestValidParentheses("") << endl; // 0
    cout << sol.longestValidParentheses("()") << endl; // 2
    cout << sol.longestValidParentheses("()(()") << endl; // 2
    cout << sol.longestValidParentheses("(()()") << endl; // 4
}