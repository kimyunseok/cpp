/*
* 백준 7562번 나이트의 이동
* https://www.acmicpc.net/problem/7562
* 그래프 탐색 이론 - 너비 우선 탐색
*/
#include <iostream>
#include <queue>
using namespace std;

int testCase;
int widthHeight;
int board[301][301];
pair<int, int> curPoint, destPoint;
int result;
pair<int, int> movePoint[8] = {
    {-1, -2},
    {-2, -1},
    {-2, 1},
    {-1, 2},
    {1, 2},
    {2, 1},
    {2, -1},
    {1, -2},
};

void clearBoard() {
    for (int i = 0; i <= 300; i++) {
        for (int j = 0; j <= 300; j++) {
            board[i][j] = 0;
        }
    }
}

void bfs(int _y, int _x) {
    queue<pair<int, pair<int, int>>> q;
    q.push({ 0, { _y, _x } });
    board[_y][_x] = 1;
    while (!q.empty()) {
        int curCnt = q.front().first;
        int yPoint = q.front().second.first;
        int xPoint = q.front().second.second;
        q.pop();
        if (yPoint == destPoint.first && xPoint == destPoint.second) {
            result = curCnt;
            break;
        }

        int nxtCnt = curCnt + 1;
        for (pair<int, int> p : movePoint) {
            int nxtY = yPoint + p.first;
            int nxtX = xPoint + p.second;
            if (nxtY < 0 || nxtY >= widthHeight || nxtX < 0 || nxtX >= widthHeight) { continue; }
            else if (board[nxtY][nxtX] == 1) { continue; }
            else {
                board[nxtY][nxtX] = 1;
                q.push({ nxtCnt, {nxtY, nxtX} });
            }
        }
    }
    return;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> testCase;

    int y, x;
    while (testCase--) {
        clearBoard();
        result = 0;

        cin >> widthHeight;

        cin >> y >> x;
        curPoint = { y, x };

        cin >> y >> x;
        destPoint = { y, x };

        bfs(curPoint.first, curPoint.second);

        cout << result << "\n";
    }

    return 0;
}
