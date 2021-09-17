/*
* 백준 14890번 경사로
* https://www.acmicpc.net/problem/14890
* 구현
*/
#include <iostream>
#include <cstring>
#include <math.h>
using namespace std;

int widthHeight, floorLength;
int map[101][101];
bool setFloor[101];
int ans;

void checkVerticalUpToDown(int prevData, int r, int c) {
    if (r > widthHeight) {
        ans++;
        return;
    }

    if (abs(map[r][c] - prevData) > 1) { return; }
    else {
        if (map[r][c] == prevData) {
            checkVerticalUpToDown(map[r][c], r + 1, c);
        }
        else if (map[r][c] - prevData < 0) {

            // 1 더 작은 높이가 나왔다면, 앞으로의 길들에 경사로를 세워준다.
            if (r + floorLength - 1 > widthHeight) { return; } // 범위 벗어난 경우, 경사로 설치 불가.

            //길이 다 같은지, 설치한 곳 있는지 check
            for (int i = r; i < r + floorLength; i++) {
                if (map[i][c] != map[r][c] || setFloor[i]) { return; }
            }

            for (int i = r; i < r + floorLength; i++) {
                setFloor[i] = true;
            }

            int nxtR = r + floorLength;

            checkVerticalUpToDown(map[nxtR - 1][c], nxtR, c);
        }
        else { // 1 더 큰 높이가 나왔다면, 이전까지 길들에 경사로를 세워준다.
            int prevR = r - 1;
            if (prevR - floorLength + 1 < 1) { return; } // 범위 벗어난 경우, 경사로 설치 불가.

            //길이 다 같은지, 설치한 곳 있는지 check
            for (int i = prevR; i > prevR - floorLength; i--) {
                if (map[i][c] != map[prevR][c] || setFloor[i]) { return; }
            }

            for (int i = prevR; i > prevR - floorLength; i--) {
                setFloor[i] = true;
            }

            checkVerticalUpToDown(map[r][c], r + 1, c);
        }
    }
}

void checkHorizontalLeftToRight(int prevData, int r, int c) {

    if (c > widthHeight) {
        ans++;
        return;
    }

    if (abs(map[r][c] - prevData) > 1) { return; }
    else {
        if (map[r][c] == prevData) {
            checkHorizontalLeftToRight(map[r][c], r, c + 1);
        }
        else if (map[r][c] - prevData < 0) {
            // 1 더 작은 높이가 나왔다면, 앞으로의 길들에 경사로를 세워준다.
            if (c + floorLength - 1 > widthHeight) { return; } // 범위 벗어난 경우, 경사로 설치 불가.

            //길이 다 같은지, 설치한 곳 있는지 check
            for (int i = c; i < c + floorLength; i++) {
                if (map[r][i] != map[r][c] || setFloor[i]) { return; }
            }

            for (int i = c; i < c + floorLength; i++) {
                setFloor[i] = true;
            }

            int nxtC = c + floorLength;

            checkHorizontalLeftToRight(map[r][nxtC - 1], r, nxtC);
        }
        else { // 1 더 큰 높이가 나왔다면, 경사로를 세워준다.
            int prevC = c - 1;
            if (prevC - floorLength + 1 < 1) { return; } // 범위 벗어난 경우, 경사로 설치 불가.

            //길이 다 같은지, 설치한 곳 있는지 check
            for (int i = prevC; i > prevC - floorLength; i--) {
                if (map[r][i] != map[r][prevC] || setFloor[i]) { return; } //이미 설치한 곳이 있다면 설치불가.
            }

            for (int i = prevC; i > prevC - floorLength; i--) {
                setFloor[i] = true;
            }

            checkHorizontalLeftToRight(map[r][c], r, c + 1);
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> widthHeight >> floorLength;

    for (int i = 1; i <= widthHeight; i++) {
        for (int j = 1; j <= widthHeight; j++) {
            cin >> map[i][j];
        }
    }

    for (int i = 1; i <= widthHeight; i++) {
        memset(setFloor, false, sizeof(setFloor));
        checkVerticalUpToDown(map[1][i], 2, i);

        memset(setFloor, false, sizeof(setFloor));
        checkHorizontalLeftToRight(map[i][1], i, 2);
    }

    cout << ans;

    return 0;
}