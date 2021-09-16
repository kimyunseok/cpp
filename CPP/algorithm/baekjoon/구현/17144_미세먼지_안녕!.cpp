/*
* 백준 17144번 미세먼지 안녕!
* https://www.acmicpc.net/problem/17144
* 구현 / 시뮬레이션
*/
#include <iostream>
#include <queue>
#include <vector>
#include <cstring>
using namespace std;

int height, width, checkTime;
queue<pair<int, pair<int, int>>> q;
vector<pair<int, int>> airCleanerPoint;
pair<int, int> direction[4] = {
    {-1, 0},
    {0, 1},
    {1, 0},
    {0, -1}
};
int board[51][51];
int minusBoard[51][51];
int ans;

void getDustMovingInfo() {
    int topAirCleanerR = airCleanerPoint[0].first;
    int topAirCleanerC = airCleanerPoint[0].second;
    int bottomAirCleanerR = airCleanerPoint[1].first;
    int bottomAirCleanerC = airCleanerPoint[1].second;

    for (int i = 1; i <= height; i++) {
        for (int j = 1; j <= width; j++) {
            if (board[i][j] >= 5) { // 5보다 작으면 확산안됨.
                for (pair<int, int> point : direction) {
                    int nxtR = i + point.first;
                    int nxtC = j + point.second;
                    if (nxtR < 1 || nxtR > height || nxtC < 1 || nxtC > width ||
                        (nxtR == topAirCleanerR && nxtC == topAirCleanerC) ||
                        (nxtR == bottomAirCleanerR && nxtC == bottomAirCleanerC)) {
                        continue;
                    }
                    int spreadValue = (board[i][j] / 5);
                    q.push({ spreadValue, {nxtR, nxtC} });
                    minusBoard[i][j] += spreadValue;
                }
            }
        }
    }
}

void spread() {
    while (!q.empty()) {
        int spreadValue = q.front().first;
        int r = q.front().second.first;
        int c = q.front().second.second;
        q.pop();
        board[r][c] += spreadValue;
    }
}

void minusAfterSpread() {
    for (int i = 1; i <= height; i++) {
        for (int j = 1; j <= width; j++) {
            board[i][j] -= minusBoard[i][j];
        }
    }
}

void moveAirCleanerTop() {
    int topAirCleanerR = airCleanerPoint[0].first;
    int topAirCleanerC = airCleanerPoint[0].second;
    int curR = topAirCleanerR;
    int curC = topAirCleanerC + 2;

    int prevData = board[curR][curC - 1];
    board[curR][curC - 1] = 0; // 공기청정기 바로 오른쪽은 0으로 만들어준다.
    while (curC <= width) { // 맨 아래줄 이동
        int tmp = board[curR][curC];
        board[curR][curC] = prevData;
        prevData = tmp;
        curC++;
    }

    curC--; // curC를 width값으로 맞춰놓음.
    curR--;
    while (curR >= 1) { // 맨 오른쪽줄 이동
        int tmp = board[curR][curC];
        board[curR][curC] = prevData;
        prevData = tmp;
        curR--;
    }

    curR++; // curR를 1로 만들어줌.
    curC--;
    while (curC >= 1) { // 맨 왼쪽줄 이동
        int tmp = board[curR][curC];
        board[curR][curC] = prevData;
        prevData = tmp;
        curC--;
    }

    curC++; // curC를 1로 만들어줌
    curR++;
    while (curR != topAirCleanerR) {
        int tmp = board[curR][curC];
        board[curR][curC] = prevData;
        prevData = tmp;
        curR++;
    }
}

void moveAirCleanerBottom() {
    int bottomAirCleanerR = airCleanerPoint[1].first;
    int bottomAirCleanerC = airCleanerPoint[1].second;
    int curR = bottomAirCleanerR;
    int curC = bottomAirCleanerC + 2;

    int prevData = board[curR][curC - 1];
    board[curR][curC - 1] = 0; // 공기청정기 바로 오른쪽은 0으로 만들어준다.

    while (curC <= width) { // 맨 위쪽줄 이동
        int tmp = board[curR][curC];
        board[curR][curC] = prevData;
        prevData = tmp;
        curC++;
    }

    curC--; // curC를 width값으로 맞춰놓음.
    curR++;
    while (curR <= height) { // 맨 오른쪽줄 이동
        int tmp = board[curR][curC];
        board[curR][curC] = prevData;
        prevData = tmp;
        curR++;
    }

    curR--; // curR를 height로 만들어줌.
    curC--;
    while (curC >= 1) { // 맨 아래줄 이동
        int tmp = board[curR][curC];
        board[curR][curC] = prevData;
        prevData = tmp;
        curC--;
    }

    curC++; // curC를 1로 만들어줌
    curR--;
    while (curR != bottomAirCleanerR) {
        int tmp = board[curR][curC];
        board[curR][curC] = prevData;
        prevData = tmp;
        curR--;
    }
}

void go(int curTime) {
    if (curTime > checkTime) { return; }
    memset(minusBoard, 0, sizeof(minusBoard));

    getDustMovingInfo(); // 확산 가능한 미세먼지 목록 가져옴
    spread(); // 미세먼지 확산
    minusAfterSpread(); // 미세먼지 확산 후 확산값만큼빼줌

    moveAirCleanerTop();
    moveAirCleanerBottom();
    go(curTime + 1);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> height >> width >> checkTime;

    for (int i = 1; i <= height; i++) {
        for (int j = 1; j <= width; j++) {
            cin >> board[i][j];
            if (board[i][j] == -1) {
                airCleanerPoint.push_back({ i, j });
            }
        }
    }

    go(1);

    for (int i = 1; i <= height; i++) {
        for (int j = 1; j <= width; j++) {
            if (board[i][j] > 0) {
                ans += board[i][j];
            }
        }
    }

    cout << ans;

    return 0;
}