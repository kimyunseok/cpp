/*
* 백준 11048번 이동하기
* https://www.acmicpc.net/problem/11048
* 다이나믹 프로그래밍
*/
#include <iostream>
#include <algorithm>
using namespace std;

int height, width;
int maze[1001][1001];
int maxCandy[1002][1002];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> height >> width;
    for (int i = 1; i <= height; i++) {
        for (int j = 1; j <= width; j++) {
            cin >> maze[i][j];
        }
    }

    for (int i = 1; i <= height; i++) {
        for (int j = 1; j <= width; j++) {
            if (i == 1 && j == 1) { maxCandy[i][j] = maze[i][j]; }
            else {
                maxCandy[i][j] = max(maxCandy[i - 1][j], max(maxCandy[i][j - 1], maxCandy[i - 1][j - 1])) + maze[i][j];
            }
        }
    }

    cout << maxCandy[height][width];

    return 0;
}