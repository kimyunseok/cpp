/*
* 백준 21609번 상어 중학교
* https://www.acmicpc.net/problem/21609
* 구현 / 시뮬레이션
*/
#include <iostream>
#include <vector>
#include <queue>
#include <math.h>

using namespace std;

int widthHeight, colorCnt;
int board[21][21];
int boardCopy[21][21];
bool visit[21][21];
vector<pair<int, int>> curLargestBlockGroup;
pair<int, int> curLargestLeaderBlockPoint;
int curLargestGroupRainbowCnt;
int score;
pair<int, int> directions[4] = {
    {0, 1},
    {0, -1},
    {1, 0},
    {-1, 0}
};

void initState() {
    curLargestBlockGroup.clear();
    curLargestLeaderBlockPoint = { 0, 0 };
    curLargestGroupRainbowCnt = 0;

    for (int r = 1; r <= widthHeight; r++) {
        for (int c = 1; c <= widthHeight; c++) {
            visit[r][c] = false;
        }
    }
}

void makeRainbowNotVisited() {
    for (int r = 1; r <= widthHeight; r++) {
        for (int c = 1; c <= widthHeight; c++) {
            if (board[r][c] == 0) visit[r][c] = false;
        }
    }
}

void checkGroup(int startR, int startC) {
    makeRainbowNotVisited();

    vector<pair<int, int>> curCheckBlockGroup;
    pair<int, int> curCheckLeaderPoint = { startR, startC };
    int rainbowCnt = 0;
    queue<pair<int, int>> bfsQ;

    curCheckBlockGroup.push_back({ startR, startC });
    bfsQ.push({ startR, startC });
    visit[startR][startC] = true;

    while (!bfsQ.empty()) {
        int curR = bfsQ.front().first;
        int curC = bfsQ.front().second;
        bfsQ.pop();

        if (board[curR][curC] != 0 &&
            (curR < curCheckLeaderPoint.first ||
                (curR == curCheckLeaderPoint.first && curC < curCheckLeaderPoint.second))) {
            curCheckLeaderPoint = { curR, curC };
        }

        for (pair<int, int> dir : directions) {
            int nxtR = curR + dir.first;
            int nxtC = curC + dir.second;

            if (nxtR < 1 
                || nxtR > widthHeight 
                || nxtC < 1 
                || nxtC > widthHeight 
                || visit[nxtR][nxtC] || board[nxtR][nxtC] < 0 || (board[nxtR][nxtC] != 0 && board[nxtR][nxtC] != board[startR][startC])) continue;

            if (board[nxtR][nxtC] == 0) rainbowCnt++;

            curCheckBlockGroup.push_back({ nxtR, nxtC });
            bfsQ.push({ nxtR, nxtC });
            visit[nxtR][nxtC] = true;
        }
    }

    if (curCheckBlockGroup.size() > curLargestBlockGroup.size()) {
        curLargestBlockGroup = curCheckBlockGroup;
        curLargestLeaderBlockPoint = curCheckLeaderPoint;
        curLargestGroupRainbowCnt = rainbowCnt;
    }
    else if (curCheckBlockGroup.size() == curLargestBlockGroup.size()) {
        if (curLargestGroupRainbowCnt < rainbowCnt) {
            curLargestBlockGroup = curCheckBlockGroup;
            curLargestGroupRainbowCnt = rainbowCnt;
            curLargestLeaderBlockPoint = curCheckLeaderPoint;
        }
        else if (curLargestGroupRainbowCnt == rainbowCnt) {
            if (curLargestLeaderBlockPoint.first < curCheckLeaderPoint.first ||
                (curLargestLeaderBlockPoint.first == curCheckLeaderPoint.first &&
                    curLargestLeaderBlockPoint.second < curCheckLeaderPoint.second)) {

                curLargestBlockGroup = curCheckBlockGroup;
                curLargestGroupRainbowCnt = rainbowCnt;
                curLargestLeaderBlockPoint = curCheckLeaderPoint;

            }
        }

    }

}

void findLargestBlockGroup() {
    for (int r = 1; r <= widthHeight; r++) {
        for (int c = 1; c <= widthHeight; c++) {
            if (board[r][c] > 0 && !visit[r][c]) checkGroup(r, c);
        }
    }
}

void eraseBlockGroupAndGetScore() {
    score += pow(curLargestBlockGroup.size(), 2);

    for (pair<int, int> point : curLargestBlockGroup) {
        board[point.first][point.second] = -2;
    }
}

void setGravity() {
    for (int c = 1; c <= widthHeight; c++) {
        for (int r = widthHeight - 1; r >= 1; r--) {
            if (board[r][c] < 0) continue;
            int curNum = board[r][c];
            int curR = r;
            int nxtR = r + 1;
            while (nxtR <= widthHeight && board[nxtR][c] == -2) {
                board[curR++][c] = -2;
                board[nxtR++][c] = curNum;
            }
        }
    }
}

void copyBoardForTurn() {
    for (int r = 1; r <= widthHeight; r++) {
        for (int c = 1; c <= widthHeight; c++) {
            boardCopy[r][c] = board[r][c];
        }
    }
}

void turn90degreeReverseClock(int startR, int startC, int length) {
    if (length < 2) return;

    int maxR = startR + length - 1;
    int maxC = startC + length - 1;

    //1. 위에서 왼쪽으로
    int curR = maxR;
    for (int c = startC; c <= maxC; c++) {
        board[curR--][startR] = boardCopy[startR][c];
    }
    
    //2. 왼쪽에서 아래로
    int curC = startC;
    for (int r = startR; r <= maxR; r++) {
        board[maxR][curC++] = boardCopy[r][startC];
    }

    //3. 아래에서 오른쪽으로
    curR = maxR;
    for (int c = startC; c <= maxC; c++) {
        board[curR--][maxR] = boardCopy[maxR][c];
    }

    //4. 오른쪽에서 위로
    curC = startC;
    for (int r = startR; r <= maxR; r++) {
        board[startR][curC++] = boardCopy[r][maxC];
    }

    turn90degreeReverseClock(startR + 1, startC + 1, length - 2);
}

void go() {

    // 1. 제일 큰 그룹 찾기
    initState();
    findLargestBlockGroup();

    // 2. 블록 그룹 모든 블록 제거 / 블록 그룹 수 만큼 점수 획득
    if (curLargestBlockGroup.size() > 1) eraseBlockGroupAndGetScore();
    else return;

    // 3. 중력 작용
    setGravity();

    // 4. 격자 90도 반시계 방향 회전
    copyBoardForTurn();
    turn90degreeReverseClock(1, 1, widthHeight);

    // 5. 중력 작용
    setGravity();

    go();

}

int main() {

    cin >> widthHeight >> colorCnt;

    for (int r = 1; r <= widthHeight; r++) {
        for (int c = 1; c <= widthHeight; c++) {
            cin >> board[r][c];
        }
    }

    go();
    
    cout << score;

    return 0;

}