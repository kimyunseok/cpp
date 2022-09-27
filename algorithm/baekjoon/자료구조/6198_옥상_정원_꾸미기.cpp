/*
* 백준 6198번 옥상 정원 꾸미기
* https://www.acmicpc.net/problem/6198
* - 자료구조 : 스택
*/
#include <iostream>
#include <stack>
#include <queue>

using namespace std;

int buildingCnt;
long long result;
queue<int> q;
stack<int> st;

int main() {
    cin >> buildingCnt;

    int input;
    for (int i = 1; i <= buildingCnt; i++) {
        cin >> input;
        q.push(input);
    }

    while (!q.empty()) {
        int curNum = q.front();
        q.pop();
        while (!st.empty() && st.top() <= curNum) st.pop();

        result += st.size();
        st.push(curNum);
    }

    cout << result;

    return 0;

}