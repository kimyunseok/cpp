/*
* 백준 2468번 안전 영역
* https://www.acmicpc.net/problem/2468
* 그래프 탐색 이론 / 브루트 포스 알고리즘
*/
#include <iostream>
#include <cstring>
using namespace std;

int widthHeight;
int maxHeight;
int region[101][101];
int visit[101][101];
int connectedComponents;
int result = 1;

void dfs(int rainHeight, int y, int x) {
    if (y > widthHeight || y < 1 || x > widthHeight || x < 1) { return; }
    if (region[y][x] <= rainHeight) { return; }
    if (visit[y][x]) { return; }
    visit[y][x] = 1;
    dfs(rainHeight, y - 1, x);
    dfs(rainHeight, y + 1, x);
    dfs(rainHeight, y, x - 1);
    dfs(rainHeight, y, x + 1);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> widthHeight;
    for (int i = 1; i <= widthHeight; i++) {
        for (int j = 1; j <= widthHeight; j++) {
            cin >> region[i][j];
            maxHeight = maxHeight < region[i][j] ? region[i][j] : maxHeight;
        }
    }

    for (int rainHeight = 0; rainHeight < maxHeight; rainHeight++) {
        connectedComponents = 0;
        memset(visit, 0, sizeof(visit));
        for (int i = 1; i <= widthHeight; i++) {
            for (int j = 1; j <= widthHeight; j++) {
                if (region[i][j] > rainHeight && !visit[i][j]) {
                    dfs(rainHeight, i, j);
                    connectedComponents++;
                }
            }
        }
        result = result < connectedComponents ? connectedComponents : result;
    }

    cout << result;

    return 0;
}