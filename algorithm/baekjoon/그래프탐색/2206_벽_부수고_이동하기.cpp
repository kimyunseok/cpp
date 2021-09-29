/*
* 백준 2206번 벽 부수고 이동하기
* https://www.acmicpc.net/problem/2206
* 그래프 탐색 이론 - 너비 우선 탐색
*/
#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

int height, width;
int board[1001][1001];
bool visit[1001][1001][2];
bool check;
int result = 1e10;

pair<int, int> direction[4] = {
    {-1, 0},
    {1, 0},
    {0, -1},
    {0, 1}
};

class Node {
public:
    int yPoint;
    int xPoint;
    int distance;
    bool alreadyCrash;
    Node(int y, int x, int dist, int already) {
        yPoint = y;
        xPoint = x;
        distance = dist;
        alreadyCrash = already;
    }
};

void bfs() {
    queue<Node> q;
    q.push(Node(1, 1, 1, false));
    visit[1][1][0] = true;

    while (!q.empty()) {
        Node curNode = q.front();
        q.pop();
        int curYPoint = curNode.yPoint;
        int curXPoint = curNode.xPoint;
        int curDistance = curNode.distance;
        bool checkCrash = curNode.alreadyCrash;

        if (curYPoint == height && curXPoint == width) {
            check = true;
            result = min(result, curDistance);
        }

        for (pair<int, int> p : direction) {
            int nxtYPoint = curYPoint + p.first;
            int nxtXPoint = curXPoint + p.second;

            if (nxtYPoint > 0 && nxtYPoint <= height
                && nxtXPoint > 0 && nxtXPoint <= width
                && !visit[nxtYPoint][nxtXPoint][checkCrash]) {

                if (board[nxtYPoint][nxtXPoint] == 0) {
                    q.push(Node(nxtYPoint, nxtXPoint, curDistance + 1, checkCrash));
                    visit[nxtYPoint][nxtXPoint][checkCrash] = true;
                }
                else {
                    if (!checkCrash) {
                        q.push(Node(nxtYPoint, nxtXPoint, curDistance + 1, true));
                        visit[nxtYPoint][nxtXPoint][1] = true;
                    }
                }
            }
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> height >> width;

    string input;

    for (int i = 1; i <= height; i++) {
        cin >> input;
        for (int j = 0; j < input.length(); j++) {
            board[i][j + 1] = input[j] - '0';
        }
    }

    bfs();

    if (check) {
        cout << result;
    }
    else {
        cout << "-1";
    }



    return 0;
}