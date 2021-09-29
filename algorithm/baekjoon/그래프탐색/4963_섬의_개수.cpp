/*
* 백준 4963번 섬의 개수
* https://www.acmicpc.net/problem/4963
* 그래프 탐색
*/
#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

int w, h;
int world[51][51]; // 0:바다, 1:땅, 2: 이미 방문한 곳
int result;

void dfs(int _h, int _w) {
    if (_h < 1 || _h > h || _w < 1 || _w > w) { return; }
    if (world[_h][_w] != 1) { return; }
    world[_h][_w] = 2;
    dfs(_h - 1, _w - 1);
    dfs(_h - 1, _w);
    dfs(_h - 1, _w + 1);
    dfs(_h, _w + 1);
    dfs(_h + 1, _w + 1);
    dfs(_h + 1, _w);
    dfs(_h + 1, _w - 1);
    dfs(_h, _w - 1);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    while (true) {
        result = 0;
        cin >> w >> h;
        if (w == 0 && h == 0) {
            break;
        }

        memset(world, 0, sizeof(world));

        for (int i = 1; i <= h; i++) {
            for (int j = 1; j <= w; j++) {
                cin >> world[i][j];
            }
        }

        for (int i = 1; i <= h; i++) {
            for (int j = 1; j <= w; j++) {
                if (world[i][j] == 1) {
                    dfs(i, j);
                    result++;
                }
            }
        }

        cout << result << "\n";
    }

    return 0;
}