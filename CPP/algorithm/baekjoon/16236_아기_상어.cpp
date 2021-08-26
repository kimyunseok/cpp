/*
* 백준 16236번 아기 상어
* https://www.acmicpc.net/problem/16236
* 구현 / 시뮬레이션 / 그래프 탐색 이론 - 너비 우선 탐색
*/
#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

int widthHeight;
int sea[21][21];
bool visit[21][21];
bool findFood;
int curSize = 2;
int curEat = 0;
int needEat[7] = { 0, 0, 2, 5, 9, 14, 20 };
int curY, curX;
pair<int, pair<int, int>> foodInfo; // 첫번째 거리, 두번째 Y : 더 높은 것을 먹어야함, 세번째 X : 왼쪽에 있는 더 작은것을 먹어야함.
int timeSec;

pair<int, int> direction[4] = {
    {-1, 0},
    {0, -1},
    {0, 1},
    {1, 0}
};

void bfs(int _y, int _x) {
    queue<pair<int, pair<int, int>>> q;
    q.push({ 0, { _y, _x } });
    visit[_y][_x] = true;

    while (!q.empty()) {
        int distance = q.front().first;
        int _curY = q.front().second.first;
        int _curX = q.front().second.second;
        q.pop();

        int curFoodDistance = foodInfo.first;
        int curFoodY = foodInfo.second.first;
        int curFoodX = foodInfo.second.second;

        if (distance > curFoodDistance) { return; }

        if (sea[_curY][_curX] != 0 && sea[_curY][_curX] < curSize) {

            if (_curY > curFoodY) {
                continue;
            }
            else if (_curY == curFoodY) {
                if (_curX > curFoodX) {
                    continue;
                }
            }

            foodInfo.first = distance;
            foodInfo.second.first = _curY;
            foodInfo.second.second = _curX;

            findFood = true;
        }
        else if (sea[_curY][_curX] > curSize) {
            continue;
        }

        for (pair<int, int> dir : direction) {
            int nxtDist = distance + 1;
            int nxtY = _curY + dir.first;
            int nxtX = _curX + dir.second;

            if (nxtY < 1 || nxtY > widthHeight
                || nxtX < 1 || nxtX > widthHeight
                || visit[nxtY][nxtX]) {
                continue;
            }

            q.push({ nxtDist, {nxtY, nxtX} });
            visit[nxtY][nxtX] = true;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> widthHeight;

    for (int i = 1; i <= widthHeight; i++) {
        for (int j = 1; j <= widthHeight; j++) {
            cin >> sea[i][j];
            if (sea[i][j] == 9) {
                curY = i;
                curX = j;
                sea[i][j] = 0;
            }
        }
    }

    do {
        findFood = false;
        memset(visit, false, sizeof(visit));

        foodInfo.first = 1e10;
        foodInfo.second.first = 1e10;
        foodInfo.second.second = 1e10;

        bfs(curY, curX);

        if (findFood) {
            int foodDistance = foodInfo.first;
            int foodY = foodInfo.second.first;
            int foodX = foodInfo.second.second;

            timeSec += foodDistance;
            sea[foodY][foodX] = 0;
            curEat++;
            if (curSize <= 6 && curEat == needEat[curSize]) {
                curSize++;
            }
            curY = foodY;
            curX = foodX;
        }

    } while (findFood);

    cout << timeSec;

    return 0;
}