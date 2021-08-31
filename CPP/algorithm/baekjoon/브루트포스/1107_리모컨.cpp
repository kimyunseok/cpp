/*
* 백준 1107번 리모컨
* https://www.acmicpc.net/problem/1107
* 브루트 포스
*/
#include <iostream>
#include <string>
#include <math.h>
using namespace std;

string wantChannel;
int breakBtnCnt;
int input;
bool btnBreak[10];
int result;

void checkAvailable(int num);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> wantChannel;
    cin >> breakBtnCnt;

    for (int i = 0; i < breakBtnCnt; i++) {
        cin >> input;
        btnBreak[input] = true;
    }

    result = abs(stoi(wantChannel) - 100);

    for (int i = 0; i <= 1000000; i++) {
        checkAvailable(i);
    }

    cout << result;

    return 0;
}

void checkAvailable(int num) {
    string str = to_string(num);
    bool canUse = true;
    for (int i = 0; i < str.length(); i++) {
        int num = str[i] - '0';
        if (btnBreak[num]) {
            canUse = false;
            break;
        }
    }

    if (canUse) {
        int res = abs(num - stoi(wantChannel)) + str.length();
        result = min(result, res);
    }
    else {
        return;
    }
}