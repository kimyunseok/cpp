/*
* 백준 20057번 마법사 상어와 토네이도
* https://www.acmicpc.net/problem/20057
* 구현 / 시뮬레이션
*/
#include <iostream>
using namespace std;

class Direction {
public:
    int r;
    int c;
    int percentage;
    Direction(int r, int c, int percentage) {
        this->r = r;
        this->c = c;
        this->percentage = percentage;
    }
};

int widthHeight;
pair<int, int> curPoint;
int maxMoveCnt = 1; // 이동하는 횟수. 최초 좌, 하 1번하고 우 상 2번씩 하고 다시 좌, 하 3번씩... 이렇게 만들려는 용도.
int curMoveCnt = 0;
int board[500][500];
int ans;
int curDirection = 0; // 0 : 좌, 1 : 하, 2: 우, 3: 상
Direction moveDirection[4][10] = { // 이동한 칸 기준.
    //9 idx에 있는 것은 나머지 이동할 곳
    {
        Direction(-1, 1, 1), Direction(1, 1, 1), Direction(-1, 0, 7),  Direction(-2, 0, 2), Direction(1, 0, 7),
     Direction(2, 0, 2),  Direction(-1, -1, 10),  Direction(1, -1, 10),  Direction(0, -2, 5),  Direction(0, -1, 100)
    },
    {
        Direction(-1, -1, 1), Direction(-1, 1, 1), Direction(0, -1, 7), Direction(0, -2, 2), Direction(0, 1, 7),
    Direction(0, 2, 2), Direction(1, -1, 10), Direction(1, 1, 10), Direction(2, 0, 5), Direction(1, 0, 100)
    },
    {
        Direction(-1, -1, 1), Direction(1, -1, 1), Direction(-1, 0, 7),  Direction(-2, 0, 2), Direction(1, 0, 7),
     Direction(2, 0, 2),  Direction(-1, 1, 10),  Direction(1, 1, 10),  Direction(0, 2, 5),  Direction(0, 1, 100)
    },
    {
        Direction(1, -1, 1), Direction(1, 1, 1), Direction(0, -1, 7), Direction(0, -2, 2), Direction(0, 1, 7),
    Direction(0, 2, 2), Direction(-1, -1, 10), Direction(-1, 1, 10), Direction(-2, 0, 5), Direction(-1, 0, 100)
    },
};

void moveTornado() {
    //1. 토네이도 이동시킴.
    int nxtR = curPoint.first + moveDirection[curDirection][9].r;
    int nxtC = curPoint.second + moveDirection[curDirection][9].c;
    curPoint = { nxtR, nxtC };
    int initialSand = board[nxtR][nxtC];
    int totalMoveSand = 0;

    //2. 각 좌표별 % 계산
    for (int i = 0; i <= 8; i++) {
        int checkR = curPoint.first + moveDirection[curDirection][i].r;
        int checkC = curPoint.second + moveDirection[curDirection][i].c;
        int moveSand = initialSand * ((double)(moveDirection[curDirection][i].percentage) / 100);
        totalMoveSand += moveSand;
        if (checkR <= 0 || checkR > widthHeight || checkC <= 0 || checkC > widthHeight) {
            ans += moveSand;
        }
        else {
            board[checkR][checkC] += moveSand;
        }
    }
    board[nxtR][nxtC] -= totalMoveSand;

    //3. 남은 모래 마지막 좌표로 이동.
    int remainSand = board[nxtR][nxtC];
    board[nxtR][nxtC] = 0;
    int sandMoveR = nxtR + moveDirection[curDirection][9].r;
    int sandMoveC = nxtC + moveDirection[curDirection][9].c;
    if (sandMoveR <= 0 || sandMoveR > widthHeight || sandMoveC <= 0 || sandMoveC > widthHeight) {
        ans += remainSand;
    }
    else {
        board[sandMoveR][sandMoveC] += remainSand;
    }

    //4. 이동횟수 Check
    curMoveCnt++;
    if (curMoveCnt == maxMoveCnt) {
        curMoveCnt = 0;

        if (curDirection == 1 || curDirection == 3) {
            maxMoveCnt++;
        }

        curDirection = curDirection + 1;
        if (curDirection > 3) { curDirection = 0; }
    }
}

void go() {
    if (curPoint.first == 1 && curPoint.second == 1) { return; }
    else {
        moveTornado();
        go();
    }

}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> widthHeight;

    curPoint.first = (widthHeight / 2) + 1;
    curPoint.second = (widthHeight / 2) + 1;

    for (int i = 1; i <= widthHeight; i++) {
        for (int j = 1; j <= widthHeight; j++) {
            cin >> board[i][j];
        }
    }

    go();

    cout << ans;

    return 0;
}