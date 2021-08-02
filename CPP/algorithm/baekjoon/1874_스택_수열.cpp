/*
* 백준 1874번 스택 수열
* https://www.acmicpc.net/problem/1874
* 자료 구조, 스택
*/
#include <iostream>
#include <stack>
#include <queue>
using namespace std;

int n;
queue<char> result_queue;
queue<int> q;
stack<int> st;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> n;
    int tmp;
    for (int i = 1; i <= n; i++) {
        cin >> tmp;
        q.push(tmp);
    }
    for (int i = 1; i <= n; i++) {
        result_queue.push('+');
        st.push(i);
        while (!st.empty() && !q.empty() && st.top() == q.front()) {
            result_queue.push('-');
            st.pop();
            q.pop();
        }
    }

    if (!q.empty()) {
        cout << "NO";
    }
    else {
        while (!result_queue.empty()) {
            cout << result_queue.front() << "\n";
            result_queue.pop();
        }
    }

    return 0;
}