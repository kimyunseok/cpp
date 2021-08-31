/*
* 백준 2447번 별 찍기 - 10
* https://www.acmicpc.net/problem/2447
* 분할 정복 / 재귀
*/
#include <iostream>
using namespace std;

int widthHeight;
char board[6562][6562];

void check(int curY, int curX, int size) {
    if (size < 3) { return; }
    for (int i = curY + size / 3; i < curY + 2 * (size / 3); i++) {
        for (int j = curX + size / 3; j < curX + 2 * (size / 3); j++) {
            board[i][j] = ' ';
        }
    }
    check(curY, curX, size / 3);
    check(curY, curX + size / 3, size / 3);
    check(curY, curX + 2 * (size / 3), size / 3);

    check(curY + size / 3, curX, size / 3);
    check(curY + size / 3, curX + size / 3, size / 3);
    check(curY + size / 3, curX + 2 * (size / 3), size / 3);

    check(curY + 2 * (size / 3), curX, size / 3);
    check(curY + 2 * (size / 3), curX + size / 3, size / 3);
    check(curY + 2 * (size / 3), curX + 2 * (size / 3), size / 3);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> widthHeight;

    for (int i = 1; i <= widthHeight; i++) {
        for (int j = 1; j <= widthHeight; j++) {
            board[i][j] = '*';
        }
    }

    check(1, 1, widthHeight);

    for (int i = 1; i <= widthHeight; i++) {
        for (int j = 1; j <= widthHeight; j++) {
            cout << board[i][j];
        }
        cout << "\n";
    }

    return 0;
}