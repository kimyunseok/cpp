/*
* 백준 10026번 적록색약
* https://www.acmicpc.net/problem/10026
* 그래프 탐색 이론
*/
#include <iostream>
#include <cstring>
using namespace std;

int widthHeight;
char board[101][101];
bool visit[101][101];
int normalResult, redGreenSameResult;

void normalDFS(int y, int x, char color) {
    if (y < 1 || y > widthHeight || x < 1 || x > widthHeight) { return; }
    if (visit[y][x]) { return; }
    if (board[y][x] != color) { return; }

    visit[y][x] = true;
    normalDFS(y - 1, x, color);
    normalDFS(y + 1, x, color);
    normalDFS(y, x - 1, color);
    normalDFS(y, x + 1, color);
}

void redGreenSameDFS(int y, int x, char color) {
    if (y < 1 || y > widthHeight || x < 1 || x > widthHeight) { return; }
    if (visit[y][x]) { return; }
    if (board[y][x] != color) {
        if (!((board[y][x] == 'R' && color == 'G') || (board[y][x] == 'G' && color == 'R'))) {
            return;
        }
    }

    visit[y][x] = true;
    redGreenSameDFS(y - 1, x, color);
    redGreenSameDFS(y + 1, x, color);
    redGreenSameDFS(y, x - 1, color);
    redGreenSameDFS(y, x + 1, color);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> widthHeight;
    for (int i = 1; i <= widthHeight; i++) {
        for (int j = 1; j <= widthHeight; j++) {
            cin >> board[i][j];
        }
    }

    for (int i = 1; i <= widthHeight; i++) {
        for (int j = 1; j <= widthHeight; j++) {
            if (!visit[i][j]) {
                normalDFS(i, j, board[i][j]);
                normalResult++;
            }
        }
    }

    memset(visit, 0, sizeof(visit));

    for (int i = 1; i <= widthHeight; i++) {
        for (int j = 1; j <= widthHeight; j++) {
            if (!visit[i][j]) {
                redGreenSameDFS(i, j, board[i][j]);
                redGreenSameResult++;
            }
        }
    }

    cout << normalResult << " " << redGreenSameResult;

    return 0;
}