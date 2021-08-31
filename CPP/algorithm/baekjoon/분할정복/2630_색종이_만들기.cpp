/*
* 백준 2630번 색종이 만들기
* https://www.acmicpc.net/problem/2630
* 분할 정복 / 재귀
*/
#include <iostream>
using namespace std;

int widthHeight;
int board[129][129];
int whiteCnt, blueCnt;

void check(int curY, int curX, int size) {
    int currentColor = board[curY][curX];
    bool same = true;
    for (int i = curY; i < curY + size; i++) {
        for (int j = curX; j < curX + size; j++) {
            if (board[i][j] != currentColor) {
                same = false;
                break;
            }
        }
    }
    if (!same) {
        //좌측 상단
        check(curY, curX, size / 2);
        //우측 상단
        check(curY, curX + size / 2, size / 2);
        //좌측 하단
        check(curY + size / 2, curX, size / 2);
        //우측 하단
        check(curY + size / 2, curX + size / 2, size / 2);
    }
    else {
        if (currentColor == 0) { whiteCnt++; }
        else { blueCnt++; }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> widthHeight;

    for (int i = 1; i <= widthHeight; i++) {
        for (int j = 1; j <= widthHeight; j++) {
            cin >> board[i][j];
        }
    }

    check(1, 1, widthHeight);

    cout << whiteCnt << "\n";
    cout << blueCnt;

    return 0;
}