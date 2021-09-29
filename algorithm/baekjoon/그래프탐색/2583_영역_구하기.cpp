/*
* 백준 2583번 영역 구하기
* https://www.acmicpc.net/problem/2583
* 그래프 탐색 이론
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int height, width, numOfSquare;
int board[101][101];
int region;
vector<int> result;

void dfs(int _y, int _x) {
    if (_y < 1 || _y > height || _x < 1 || _x > width) { return; }
    if (board[_y][_x] == 1) { return; }
    board[_y][_x] = 1;
    region++;
    dfs(_y - 1, _x);
    dfs(_y + 1, _x);
    dfs(_y, _x - 1);
    dfs(_y, _x + 1);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> height >> width >> numOfSquare;
    int x1, y1, x2, y2;
    for (int i = 1; i <= numOfSquare; i++) {
        cin >> x1 >> y1 >> x2 >> y2;
        for (int _y = y1 + 1; _y <= y2; _y++) {
            for (int _x = x1 + 1; _x <= x2; _x++) {
                board[_y][_x] = 1;
            }
        }
    }

    for (int _y = 1; _y <= height; _y++) {
        for (int _x = 1; _x <= width; _x++) {
            if (board[_y][_x] == 0) {
                region = 0;
                dfs(_y, _x);
                result.push_back(region);
            }
        }
    }

    sort(result.begin(), result.end());

    cout << result.size() << "\n";

    for (int num : result) {
        cout << num << " ";
    }

    return 0;
}
