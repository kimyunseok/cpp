/*
* 백준 23288번 주사위 굴리기 2
* https://www.acmicpc.net/problem/23288
* 구현 / 시뮬레이션 / 그래프 탐색 이론
*/
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int height, width, moveCnt;
int map[21][21];
bool visit[21][21];
int curDiceBottomNum = 6;
int curDirection = 1;
int curR = 1;
int curC = 1;
int reverseDiceNum[7] = { -1, 6, 5, 4, 3, 2, 1 };
int reverseDirection[4] = { 2, 3, 0, 1 };
int adj[4] = { 2, 3, 5, 4 }; // 순서 : 북(0), 동(1), 남(2), 서(3)
pair<int, int> directions[4] = {
	{-1, 0},
	{0, 1},
	{1, 0},
	{0, -1}
};
int ans;

void move() {
	int nxtR = curR + directions[curDirection].first;
	int nxtC = curC + directions[curDirection].second;
	if (nxtR < 1 || nxtR > height || nxtC < 1 || nxtC > width) {
		curDirection = reverseDirection[curDirection];
		nxtR = curR + directions[curDirection].first;
		nxtC = curC + directions[curDirection].second;
	}
	curR = nxtR;
	curC = nxtC;

	int prevDiceBottom = curDiceBottomNum;
	curDiceBottomNum = adj[curDirection];
	int reverse = reverseDirection[curDirection];
	adj[reverse] = prevDiceBottom;
	adj[curDirection] = reverseDiceNum[prevDiceBottom];
}

void getScore() {
	int cnt = 1;
	int num = map[curR][curC];
	queue<pair<int, int>> q;
	vector<pair<int, int>> visitPointVec;
	q.push({ curR, curC });
	visitPointVec.push_back({ curR, curC });
	visit[curR][curC] = true;
	while (!q.empty()) {
		int r = q.front().first;
		int c = q.front().second;
		q.pop();

		for (pair<int, int> dir : directions) {
			int nxtR = r + dir.first;
			int nxtC = c + dir.second;
			if (nxtR < 1 || nxtR > height || nxtC < 1 || nxtC > width ||
				visit[nxtR][nxtC] || map[nxtR][nxtC] != num) {
				continue;
			}

			visit[nxtR][nxtC] = true;
			q.push({ nxtR, nxtC });
			visitPointVec.push_back({ nxtR, nxtC });
			cnt++;
		}
	}
	for (int i = 0; i < visitPointVec.size(); i++) {
		int r = visitPointVec[i].first;
		int c = visitPointVec[i].second;
		visit[r][c] = false;
	}
	ans = ans + (cnt * num);
}

void setDirection() {
	int mapNum = map[curR][curC];
	if (curDiceBottomNum > mapNum) {
		curDirection = curDirection + 1;
	}
	else if (curDiceBottomNum < mapNum) {
		curDirection = curDirection - 1;
	}

	//오래걸린이유, 주사위의 방향 조건을 < 0일 땐 3으로 주고 > 3일 땐 0으로 줘야하는데, 두 조건 모두 0으로 줘버림.
	if (curDirection < 0) {
		curDirection = 3;
	}
	else if (curDirection > 3) {
		curDirection = 0;
	}
}

void go(int idx) {
	if (idx > moveCnt) { return; }

	move();
	getScore();
	setDirection();
	go(idx + 1);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> height >> width >> moveCnt;

	for (int i = 1; i <= height; i++) {
		for (int j = 1; j <= width; j++) {
			cin >> map[i][j];
		}
	}

	go(1);

	cout << ans;

	return 0;
}
