/*
* 10773번 제로
* https://www.acmicpc.net/problem/10773
* 스택
*/
#include <iostream>
#include <stack>
using namespace std;

int k;
stack<int> s;
int result;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> k;
    int input;
    for (int i = 1; i <= k; i++) {
        cin >> input;
        if (input == 0) {
            s.pop();
        }
        else {
            s.push(input);
        }
    }
    int tmp;
    while (!s.empty()) {
        tmp = s.top();
        s.pop();
        result += tmp;
    }
    cout << result;
}