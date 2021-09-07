/*
* 백준 15685번 드래곤 커브
* https://www.acmicpc.net/problem/15685
* 구현 / 시뮬레이션
*/
#include <iostream>
#include <vector>
using namespace std;

int dragonCurveCnt;
int curX, curY, startDirection, generation;
int board[101][101];
pair<int, int> direction[4] = {
    {0, 1},
    {-1, 0},
    {0, -1},
    {1, 0}
};
vector<int> dragonCurveVec;
int ans;

void makeDragonCurve(int idx) {
    if (idx > generation) { return; }
    if (idx == 0) {
        board[curY][curX] = 1;
        curY = curY + direction[startDirection].first;
        curX = curX + direction[startDirection].second;
        board[curY][curX] = 1;
        dragonCurveVec.push_back(startDirection);
        makeDragonCurve(1);
    }
    else {
        for (int i = dragonCurveVec.size() - 1; i >= 0; i--) {
            int prevDirection = dragonCurveVec[i];
            int curDirection = (prevDirection + 1) % 4;
            curY = curY + direction[curDirection].first;
            curX = curX + direction[curDirection].second;
            board[curY][curX] = 1;
            dragonCurveVec.push_back(curDirection);
        }
        makeDragonCurve(idx + 1);
    }
}

bool findSquareCnt(int y, int x) {
    if (board[y][x] != 1) { return false; }
    if (board[y + 1][x] != 1) { return false; }
    if (board[y][x + 1] != 1) { return false; }
    if (board[y + 1][x + 1] != 1) { return false; }
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> dragonCurveCnt;

    while (dragonCurveCnt--) {
        dragonCurveVec.clear();
        cin >> curX >> curY >> startDirection >> generation;
        makeDragonCurve(0);
    }

    for (int i = 0; i <= 100; i++) {
        for (int j = 0; j <= 100; j++) {
            if (i + 1 <= 100 && j + 1 <= 100 && findSquareCnt(i, j)) {
                ans++;
            }
        }
    }

    cout << ans;

    return 0;
}