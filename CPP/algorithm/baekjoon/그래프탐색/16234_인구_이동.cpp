/*
* 백준 16234번 인구 이동
* https://www.acmicpc.net/problem/16234
* 구현 / 시뮬레이션 / 그래프 이론 - 너비 우선 탐색
*/
#include <iostream>
#include <vector>
#include <cstring>
#include <queue>
#include <math.h>
using namespace std;

int widthHeight, minDiff, maxDiff;
int map[51][51];
bool visit[51][51];
int unionPopulationSum, unionPopulationNum;
vector<pair<int, int>> unionPoint;
pair<int, int> direction[4] = {
    {-1, 0},
    {0, 1},
    {1, 0},
    {0, -1}
};
int ans;

void bfs(int startY, int startX) {
    unionPopulationSum = 0;
    unionPopulationNum = 0;

    queue<pair<int, int>> q;
    q.push({ startY, startX });
    visit[startY][startX] = true;

    while (!q.empty()) {
        int curY = q.front().first;
        int curX = q.front().second;
        int curPopulation = map[curY][curX];
        q.pop();

        unionPopulationNum++;
        unionPopulationSum += map[curY][curX];
        unionPoint.push_back({ curY, curX });

        for (pair<int, int> dir : direction) {
            int nxtY = curY + dir.first;
            int nxtX = curX + dir.second;
            if (nxtY < 1 || nxtY > widthHeight || nxtX < 1 || nxtX > widthHeight ||
                visit[nxtY][nxtX]) {
                continue;
            }

            int nxtPopulation = map[nxtY][nxtX];
            int diff = abs(curPopulation - nxtPopulation);

            if (minDiff <= diff && diff <= maxDiff) {
                visit[nxtY][nxtX] = true;
                q.push({ nxtY, nxtX });
            }
        }
    }
}

void populationMove() {
    int newPopulation = unionPopulationSum / unionPopulationNum;

    for (pair<int, int> p : unionPoint) {
        int y = p.first;
        int x = p.second;
        map[y][x] = newPopulation;
    }

    unionPoint.clear(); // 인구이동다하면 벡터초기화
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> widthHeight >> minDiff >> maxDiff;

    for (int i = 1; i <= widthHeight; i++) {
        for (int j = 1; j <= widthHeight; j++) {
            cin >> map[i][j];
        }
    }

    bool find = true;
    int day = 0;
    while (find) {
        day++;
        find = false;
        memset(visit, false, sizeof(visit));
        for (int i = 1; i <= widthHeight; i++) {
            for (int j = 1; j <= widthHeight; j++) {
                if (!visit[i][j]) {
                    bfs(i, j);
                }
                if (unionPopulationNum > 1) {
                    ans = day;
                    find = true;
                }
                populationMove();
            }
        }
    }

    cout << ans;

    return 0;
}