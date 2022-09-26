/*
* 백준 17141번 연구소 2
* https://www.acmicpc.net/problem/17141
* 그래프 탐색 이론 / 브루트 포스 알고리즘
*/
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Point {
    int r = -1;
    int c = -1;
    int time = -1;
};

int widthHeight, virusCnt;
int originalMap[51][51];
int checkMap[51][51];
bool visit[51][51];
vector<pair<int, int>> virusPointVec;
vector<pair<int, int>> curCheckVec;
int answer = -1;

pair<int, int> directions[4] = {
    {-1, 0},
    {1, 0},
    {0, -1},
    {0, 1},
};

int bfs() {

    for (int i = 1; i <= widthHeight; i++) {
        for (int j = 1; j <= widthHeight; j++) {
            visit[i][j] = false;
            checkMap[i][j] = (originalMap[i][j] == 1) ? -1 : 0;
        }
    }

    queue<Point> q;

    for (int i = 0; i < virusCnt; i++) {
        q.push({ curCheckVec[i].first, curCheckVec[i].second, 0 });
        visit[curCheckVec[i].first][curCheckVec[i].second] = true;
    }

    while (!q.empty()) {
        int r = q.front().r;
        int c = q.front().c;
        int time = q.front().time;
        q.pop();

        for (pair<int, int> dir : directions) {
            int nxtR = r + dir.first;
            int nxtC = c + dir.second;

            if (nxtR < 1 || nxtR > widthHeight || nxtC < 1 || nxtC > widthHeight) continue;

            if (checkMap[nxtR][nxtC] != -1 && !visit[nxtR][nxtC]) {
                visit[nxtR][nxtC] = true;
                checkMap[nxtR][nxtC] = time + 1;
                q.push({ nxtR, nxtC, time + 1 });
            }
        }
    }

    int ret = 0;
    for (int i = 1; i <= widthHeight; i++) {
        for (int j = 1; j <= widthHeight; j++) {
            if (checkMap[i][j] != -1 && !visit[i][j]) return -1;
            else if(checkMap[i][j] != -1) ret = max(ret, checkMap[i][j]);
        }
    }

    return ret;
}

void go(int startIdx, int idx) {
    if (idx > virusCnt) {
        int bfsResult = bfs();
        if (bfsResult != -1) {
            if (answer == -1) answer = bfsResult;
            else answer = min(answer, bfsResult);
        }
    }
    else {
        for (int i = startIdx; i < virusPointVec.size(); i++) {
            curCheckVec.push_back(virusPointVec[i]);
            go(i + 1, idx + 1);
            curCheckVec.pop_back();
        }
    }
}

int main() {
    cin >> widthHeight >> virusCnt;

    for (int i = 1; i <= widthHeight; i++) {
        for (int j = 1; j <= widthHeight; j++) {
            cin >> originalMap[i][j];
            if (originalMap[i][j] == 2) virusPointVec.push_back({ i, j });
        }
    }

    go(0, 1);
        
    cout << answer;

    return 0;

}