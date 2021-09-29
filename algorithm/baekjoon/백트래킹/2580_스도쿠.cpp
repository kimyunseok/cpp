/*
* 백준 2580번 스도쿠
* https://www.acmicpc.net/problem/2580
* 백트래킹
*/
#include <iostream>
#include <vector>
using namespace std;

int board[10][10];
vector<pair<int, int>> emptyPoint;

bool checkSquare(int y, int x, int prevY, int prevX, int addNum) {
    for (int i = y; i < y + 3; i++) {
        for (int j = x; j < x + 3; j++) {
            if (i == prevY && j == prevX) { continue; }
            if (board[i][j] == addNum) {
                return false;
            }
        }
    }
    return true;
}

void go(int idx, int prevYPoint, int prevXPoint) {

    int addNum = board[prevYPoint][prevXPoint];

    for (int i = 1; i <= 9; i++) {
        if (i != prevXPoint && board[prevYPoint][i] == addNum) { return; }
        if (i != prevYPoint && board[i][prevXPoint] == addNum) { return; }
    }
    int checkY = prevYPoint < 4 ? 1 : prevYPoint < 7 ? 4 : 7;
    int checkX = prevXPoint < 4 ? 1 : prevXPoint < 7 ? 4 : 7;

    if (!checkSquare(checkY, checkX, prevYPoint, prevXPoint, addNum)) { return; }

    if (idx > emptyPoint.size()) {
        for (int i = 1; i <= 9; i++) {
            for (int j = 1; j <= 9; j++) {
                cout << board[i][j] << " ";
            }
            cout << "\n";
        }
        exit(0);
    }
    else {
        for (int i = 1; i <= 9; i++) {
            int yPoint = emptyPoint[idx - 1].first;
            int xPoint = emptyPoint[idx - 1].second;
            board[yPoint][xPoint] = i;
            go(idx + 1, yPoint, xPoint);
            board[yPoint][xPoint] = 0;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    for (int i = 1; i <= 9; i++) {
        for (int j = 1; j <= 9; j++) {
            cin >> board[i][j];
            if (board[i][j] == 0) {
                emptyPoint.push_back({ i, j });
            }
        }
    }

    for (int i = 1; i <= 9; i++) {
        int firstY = emptyPoint[0].first;
        int firstX = emptyPoint[0].second;
        board[firstY][firstX] = i;
        go(2, firstY, firstX);
        board[firstY][firstX] = 0;
    }

    return 0;
}