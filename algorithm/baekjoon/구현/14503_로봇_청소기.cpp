/*
* 백준 14503번 로봇 청소기
* https://www.acmicpc.net/problem/14503
* 구현 / 시뮬레이션
*/
#include <iostream>
using namespace std;

int height, width;
int room[51][51]; // 0 : 빈칸, 1 : 벽 그리고 2는 청소한 곳
int robotY, robotX, robotDirection; // 0: 북, 1: 동, 2: 남, 3: 서
int result;
/*
* 왼쪽방향에 대한 계산
* 북쪽(0)일 경우 왼쪽방향은 서쪽(3)이고 왼쪽 index는 x가 -1, 후진은 y가 +1
* 동쪽(1)일 경우 왼쪽방향은 북쪽(0)이고 왼쪽 index는 y가 -1, 후진은 x가 -1
* 남쪽(2)일 경우 왼쪽방향은 동쪽(1)이고 왼쪽 index는 x가 +1, 후진은 y가 -1
* 서쪽(3)일 경우 왼쪽방향은 남쪽(2)이고 왼쪽 index는 y가 +1, 후진은 x가 +1
*/
pair<int, pair<int, int>> directionGoSystem[4] = {
    { 3, {0, -1} },
    { 0, {-1, 0} },
    { 1, {0, 1} },
    { 2, {1, 0} }
};
pair<int, int> directionBackSystem[4] = {
    {1, 0},
    {0, -1},
    {-1, 0},
    {0, 1}
};

void cleanSystem(int y, int x, int direction) {
    if (y < 1 || y > height || x < 1 || x > width) { return; }
    if (room[y][x] == 0) {
        room[y][x] = 2; // 1. 현재 위치를 청소한다.
        result++;
    }
    //2. 현재 위치, 현재 방향을 기준으로 왼쪽방향부터 탐색
    int leftDirection = directionGoSystem[direction].first;
    int leftY = y + directionGoSystem[direction].second.first;
    int leftX = x + directionGoSystem[direction].second.second;

    int backY = y + directionBackSystem[direction].first;
    int backX = x + directionBackSystem[direction].second;

    if (room[leftY][leftX] == 0) {
        cleanSystem(leftY, leftX, leftDirection);
        return;
    }
    else if (room[leftY][leftX] != 0) {
        if (room[y - 1][x] != 0 && room[y + 1][x] != 0 && room[y][x - 1] != 0 && room[y][x + 1] != 0) {
            if (room[backY][backX] == 1) { return; }
            else {
                cleanSystem(backY, backX, direction);
            }
        }
        else {
            while (room[leftY][leftX] != 0) {
                leftY = y + directionGoSystem[leftDirection].second.first;
                leftX = x + directionGoSystem[leftDirection].second.second;
                leftDirection = directionGoSystem[leftDirection].first;
            }
            cleanSystem(leftY, leftX, leftDirection);
        }
        return;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> height >> width;

    cin >> robotY >> robotX >> robotDirection;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            cin >> room[i][j];
        }
    }

    cleanSystem(robotY, robotX, robotDirection);

    cout << result;

    return 0;
}