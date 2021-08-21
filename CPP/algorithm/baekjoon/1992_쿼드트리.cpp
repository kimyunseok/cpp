/*
* 백준 1992번 쿼드트리
* https://www.acmicpc.net/problem/1992
* 분할 정복 / 재귀
*/
#include <iostream>
using namespace std;

int widthHeight;
int board[65][65];

void check(int curY, int curX, int size) {
    int currentNum = board[curY][curX];
    bool same = true;
    for (int i = curY; i < curY + size; i++) {
        for (int j = curX; j < curX + size; j++) {
            if (board[i][j] != currentNum) {
                same = false;
                break;
            }
        }
    }

    if (!same) {
        cout << "(";
        check(curY, curX, size / 2);
        check(curY, curX + size / 2, size / 2);
        check(curY + size / 2, curX, size / 2);
        check(curY + size / 2, curX + size / 2, size / 2);
        cout << ")";
    }
    else {
        cout << currentNum;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> widthHeight;

    string input;
    for (int i = 1; i <= widthHeight; i++) {
        cin >> input;
        for (int k = 0; k < widthHeight; k++) {
            board[i][k + 1] = input[k] - '0';
        }
    }
    check(1, 1, widthHeight);

    return 0;
}