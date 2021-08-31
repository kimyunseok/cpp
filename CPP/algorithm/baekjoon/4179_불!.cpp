/*
* 백준 4179번 불!
* https://www.acmicpc.net/problem/4179
* 그래프 탐색 이론 - 너비 우선 탐색
*/
#include <iostream>
#include <queue>
using namespace std;

class Point {
public:
    int time;
    char type;
    int y;
    int x;
    Point(int time, char type, int y, int x) {
        this->time = time;
        this->type = type;
        this->y = y;
        this->x = x;
    }
};

struct comp {
    bool operator()(Point p1, Point p2) {
        if (p1.time > p2.time) {
            return true;
        }
        else if (p1.time == p2.time) {
            if (p1.type > p2.type) {
                return true;
            }
            else {
                return false;
            }
        }
        else {
            return false;
        }
    }
};

int width, height;
char maze[1002][1002];
bool visit[1002][1002][2];
priority_queue< Point, vector<Point>, comp > pq;
pair<int, int> direction[4] = {
    {-1, 0},
    {0, 1},
    {1, 0},
    {0, -1}
};
int ans;

void bfs() {
    while (!pq.empty()) {
        int curTime = pq.top().time;
        int curType = pq.top().type;
        int curY = pq.top().y;
        int curX = pq.top().x;
        int curTypeIdx = (curType == 'J') ? 0 : 1;
        pq.pop();

        if (curType == 'J' && maze[curY][curX] == 'F') { continue; }

        if (curType == 'J' && (curY == 1 || curY == height || curX == 1 || curX == width)) {
            ans = curTime + 1;
            return;
        }
        maze[curY][curX] = curType;

        //for (int i = 1; i <= height; i++) {
        //    for (int j = 1; j <= width; j++) {
        //        cout << maze[i][j] << " ";
        //    }
        //    cout << "\n";
        //}
        //cout << "\n\n";

        for (pair<int, int> dir : direction) {
            int nxtTime = curTime + 1;
            int nxtY = curY + dir.first;
            int nxtX = curX + dir.second;
            if (nxtY < 1 || nxtY > height || nxtX < 1 || nxtX > width) { continue; }
            if (visit[nxtY][nxtX][curTypeIdx] || maze[nxtY][nxtX] == '#' || maze[nxtY][nxtX] == 'F') { continue; }
            visit[nxtY][nxtX][curTypeIdx] = true;
            pq.push(Point(nxtTime, curType, nxtY, nxtX));
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> height >> width;

    for (int i = 1; i <= height; i++) {
        for (int j = 1; j <= width; j++) {
            cin >> maze[i][j];
            if (maze[i][j] == 'J' || maze[i][j] == 'F') {
                pq.push(Point(0, maze[i][j], i, j));
                int curTypeIdx = (maze[i][j] == 'J') ? 0 : 1;
                visit[i][j][curTypeIdx] = true;
            }
        }
    }

    bfs();

    if (ans != 0) {
        cout << ans;
    }
    else {
        cout << "IMPOSSIBLE";
    }

    return 0;
}