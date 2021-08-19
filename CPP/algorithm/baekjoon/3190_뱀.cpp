/*
* 백준 3190번 뱀
* https://www.acmicpc.net/problem/3190
* 구현 / 시뮬레이션 / 자료구조 - 큐, 덱
*/
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Snake {
public:
    pair<int, int> headPoint;
    queue<pair<int, int>> movePoint;
    int direction;
    Snake(pair<int, int> startPoint, int direction) {
        headPoint = startPoint;
        movePoint.push(startPoint);
        this->direction = direction;
    }
};

int board[101][101];
queue<pair<int, char>> direcChangeQueue;
pair<int, int> direction[4] = { // 오른쪽 90도는 (+1%4) / 왼쪽 90도는 (-1, 0보다 작으면 3)
    {0, 1}, // 우 방향
    {1, 0}, // 아래 방향
    {0, -1}, // 좌 방향
    {-1, 0} // 위 방향
};
int widthHeight, numOfApple, numOfDirectionChange;
int timeCnt;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    Snake snake({ 1, 1 }, 0);

    cin >> widthHeight >> numOfApple;

    int _x, _y;
    for (int i = 1; i <= numOfApple; i++) {
        cin >> _y >> _x;
        board[_y][_x] = 1;
    }

    cin >> numOfDirectionChange;

    int whenChange;
    char direc;
    for (int i = 1; i <= numOfDirectionChange; i++) {
        cin >> whenChange;
        cin >> direc;
        direcChangeQueue.push({ whenChange, direc });
    }

    while (true) {
        int curY = snake.headPoint.first;
        int curX = snake.headPoint.second;
        if (curY < 1 || curY > widthHeight || curX < 1 || curX > widthHeight) { break; }
        else if (board[curY][curX] == 2) { break; }

        timeCnt++;
        int moveIdx = snake.direction;
        snake.headPoint = { curY + direction[moveIdx].first
            , curX + direction[moveIdx].second };

        snake.movePoint.push({ curY, curX });
        if (!snake.movePoint.empty() && board[curY][curX] == 0) {
            int tailY = snake.movePoint.front().first;
            int tailX = snake.movePoint.front().second;
            snake.movePoint.pop();

            board[tailY][tailX] = 0;
        }
        board[curY][curX] = 2;

        if (!direcChangeQueue.empty() && timeCnt == direcChangeQueue.front().first) {
            char direcChar = direcChangeQueue.front().second;
            direcChangeQueue.pop();
            if (direcChar == 'L') {
                snake.direction -= 1;
                if (snake.direction < 0) { snake.direction = 3; }
            }
            else {
                snake.direction = (snake.direction + 1) % 4;
            }
        }
    }

    cout << timeCnt;

    return 0;
}
