/*
* 백준 1541번 잃어버린 괄호
* https://www.acmicpc.net/problem/1541
* 수학, 문자열, 파싱
*/
#include <iostream>
#include <queue>
using namespace std;

queue<int> q_num;
queue<char> q_oper;
string input;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    cin >> input;
    int tmp = 0;
    for (int i = 0; i < input.length(); i++) {
        if (input[i] != '+' && input[i] != '-') {
            if (i == input.length() - 1) {
                tmp *= 10;
                tmp = tmp + (input[i] - '0');
                q_num.push(tmp);
            }
            else if (tmp == 0) {
                tmp = input[i] - '0';
            }
            else {
                tmp *= 10;
                tmp = tmp + (input[i] - '0');
            }
        }
        else {
            q_num.push(tmp);
            tmp = 0;
            q_oper.push(input[i]);
        }
    }
    int cur_num = q_num.front();
    int result = cur_num;
    q_num.pop();
    while (!q_num.empty()) {
        char cur_oper = q_oper.front();
        cur_num = q_num.front();
        q_oper.pop();
        q_num.pop();
        if (cur_oper == '+') {
            result += cur_num;
        }
        else if (cur_oper == '-') {
            while (!q_oper.empty() && q_oper.front() == '+') {
                int top_num = q_num.front();
                cur_num += top_num;
                q_oper.pop();
                q_num.pop();
            }
            result -= cur_num;
        }
    }

    cout << result;
    return 0;
}