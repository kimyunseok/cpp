/*
* 백준 2589번 보물섬
* https://www.acmicpc.net/problem/2589
* 그래프 탐색 이론 - 너비 우선 탐색, 브루트 포스
*/
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int height, width;
char board[51][51];
bool visit[51][51];
vector<pair<int, int>> visitVec;
vector<pair<int, int>> landVec;
pair<int, int> directions[4] = {
    {-1, 0},
    {0, 1},
    {1, 0},
    {0, -1}
};
int ans;

void bfs(int r, int c) {
    queue<pair<int, pair<int, int>>> q;
    q.push({ 0, {r, c} });
    visit[r][c] = true;
    visitVec.push_back({ r, c });
    while (!q.empty()) {
        int curR = q.front().second.first;
        int curC = q.front().second.second;
        int curCost = q.front().first;
        q.pop();
        ans = max(ans, curCost);

        for (pair<int, int> p : directions) {
            int nxtR = curR + p.first;
            int nxtC = curC + p.second;
            int nxtCost = curCost + 1;

            if (nxtR < 1 || nxtR > height || nxtC < 1 || nxtC > width || board[nxtR][nxtC] != 'L' ||
                visit[nxtR][nxtC]) {
                continue;
            }
            visit[nxtR][nxtC] = true;
            visitVec.push_back({ nxtR, nxtC });
            q.push({ nxtCost, {nxtR, nxtC} });
        }
    }

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> height >> width;

    for (int i = 1; i <= height; i++) {
        for (int j = 1; j <= width; j++) {
            cin >> board[i][j];
            if (board[i][j] == 'L') {
                landVec.push_back({ i, j });
            }
        }
    }

    for (pair<int, int> p : landVec) {
        visitVec.clear();

        bfs(p.first, p.second);

        for (pair<int, int> p : visitVec) {
            visit[p.first][p.second] = false;
        }
    }

    cout << ans;

    return 0;
}