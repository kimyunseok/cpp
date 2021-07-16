/*
* 백준 1018번 체스판 다시 칠하기
* https://www.acmicpc.net/problem/1018
* 브루트포스 알고리즘
*/
#include <iostream>
using namespace std;

char board[51][51];
int n, m;
int result = 1e10;

void leftTopBlack(int i, int j, int idx, int change_num);

void leftTopWhite(int i, int j, int idx, int change_num);

int main() {
    ios_base::sync_with_stdio(false); 
    cin.tie(NULL); 
    cout.tie(NULL);

    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> board[i][j];
        }
    }

    for (int i = 1; i <= n; i++) {
        if (i + 7 > n) { break; }
        for (int j = 1; j <= m; j++) {
            if (j + 7 > m) { break; }
            leftTopBlack(i, j, 1, 0);
            leftTopWhite(i, j, 1, 0);
        }
    }

    cout << result;

    return 0;
}

void leftTopBlack(int i, int j, int idx, int change_num) {
    if (idx == 9) {
        result = result > change_num ? change_num : result;
        return;
    }
    for (int k = j; k <= j + 7; k++) {
        if ((k - j) % 2 == 0) {
            if (board[i][k] != 'B') { change_num++; }
        }
        else {
            if (board[i][k] != 'W') {change_num++; }
        }
    }
    leftTopWhite(i + 1, j, idx + 1, change_num);
}

void leftTopWhite(int i, int j, int idx, int change_num) {
    if (idx == 9) {
        result = result > change_num ? change_num : result;
        return;
    }
    for (int k = j; k <= j + 7; k++) {
        if ((k - j) % 2 == 0) {
            if (board[i][k] != 'W') {change_num++; }
        }
        else {
            if (board[i][k] != 'B') {change_num++; }
        }
    }
    leftTopBlack(i + 1, j, idx + 1, change_num);
}