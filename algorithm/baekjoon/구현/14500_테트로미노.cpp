/*
* 백준 14500번 테트로미노
* https://www.acmicpc.net/problem/14500
* 브루트 포스 / 구현
*/
#include <iostream>
#include <algorithm>
using namespace std;

class Direction {
public:
    pair<int, int> direc1;
    pair<int, int> direc2;
    pair<int, int> direc3;
    pair<int, int> direc4;
    Direction(pair<int, int> direc1, pair<int, int> direc2, pair<int, int> direc3, pair<int, int> direc4) {
        this->direc1 = direc1;
        this->direc2 = direc2;
        this->direc3 = direc3;
        this->direc4 = direc4;
    }
};

int height, width;
int board[501][501];
Direction direc[19] = {
    //ㅡ 모양
    Direction({0, 0}, {0, 1}, {0, 2}, {0, 3}),
    Direction({0, 0}, {1, 0}, {2, 0}, {3, 0}),

    //ㅁ 모양
    Direction({0, 0}, {0, 1}, {1, 0}, {1, 1}),

    //ㄴ자 모양
    Direction({0, 0}, {1, 0}, {2, 0}, {2, 1}),
    Direction({0, 0}, {0, 1}, {0, 2}, {1, 0}),
    Direction({0, 0}, {0, 1}, {1, 1}, {2, 1}),
    Direction({0, 0}, {1, 0}, {1, -1}, {1, -2}),
    Direction({0, 0}, {1, 0}, {2, 0}, {2, -1}),
    Direction({0, 0}, {1, 0}, {1, 1}, {1, 2}),
    Direction({0, 0}, {0, 1}, {1, 0}, {2, 0}),
    Direction({0, 0}, {0, 1}, {0, 2}, {1, 2}),

    //지그재그 모양
    Direction({0, 0}, {1, 0}, {1, 1}, {2, 1}),
    Direction({0, 0}, {0, 1}, {1, 0}, {1, -1}),
    Direction({0, 0}, {1, 0}, {1, -1}, {2, -1}),
    Direction({0, 0}, {0, 1}, {1, 1}, {1, 2}),

    //ㅗ 모양
    Direction({0, 0}, {1, 0}, {1, 1}, {1, -1}),
    Direction({0, 0}, {1, 0}, {1, 1}, {2, 0}),
    Direction({0, 0}, {0, 1}, {0, 2}, {1, 1}),
    Direction({0, 0}, {0, 1}, {-1, 1}, {1, 1}),
};
int result;

void checkSum(int _y, int _x) {

    for (Direction dir : direc) {
        int sum = 0;
        pair<int, int> dir1 = dir.direc1;
        pair<int, int> dir2 = dir.direc2;
        pair<int, int> dir3 = dir.direc3;
        pair<int, int> dir4 = dir.direc4;

        if (_y + dir1.first > height || _y + dir1.first < 1 || _x + dir1.second > width || _x + dir1.second < 1) {
            continue;
        }
        else if (_y + dir2.first > height || _y + dir2.first < 1 || _x + dir2.second > width || _x + dir2.second < 1) {
            continue;
        }
        else if (_y + dir3.first > height || _y + dir3.first < 1 || _x + dir3.second > width || _x + dir3.second < 1) {
            continue;
        }
        else if (_y + dir4.first > height || _y + dir4.first < 1 || _x + dir4.second > width || _x + dir4.second < 1) {
            continue;
        }
        else {
            sum = board[_y + dir1.first][_x + dir1.second] + board[_y + dir2.first][_x + dir2.second]
                + board[_y + dir3.first][_x + dir3.second] + board[_y + dir4.first][_x + dir4.second];
        }
        result = max(result, sum);
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> height >> width;
    result = 0;

    for (int i = 1; i <= height; i++) {
        for (int j = 1; j <= width; j++) {
            cin >> board[i][j];
        }
    }

    for (int i = 1; i <= height; i++) {
        for (int j = 1; j <= width; j++) {
            checkSum(i, j);
        }
    }

    cout << result;

    return 0;
}
