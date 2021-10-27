/*
* 백준 2638번 치즈
* https://www.acmicpc.net/problem/2638
* 구현 / 시뮬레이션 / 그래프 탐색 이론
*/
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int height, width;
int board[101][101];
int externalAdjCnt[101][101];
queue<pair<int, int>> externalVisitQ;
vector<pair<int, int>> cheeseVec;
bool visit[101][101];
pair<int, int> direction[4] = {
	{-1, 0},
	{0, 1},
	{1, 0},
	{0, -1}
};
int ans;

// 외부공기
void bfs() {
	while (!externalVisitQ.empty()) {
		int r = externalVisitQ.front().first;
		int c = externalVisitQ.front().second;
		externalVisitQ.pop();
		visit[r][c] = false;
	}

	queue<pair<int, int>> q;
	visit[1][1] = true;
	q.push({ 1,1 });
	externalVisitQ.push({ 1,1 });
	while (!q.empty()) {
		int r = q.front().first;
		int c = q.front().second;
		q.pop();

		for (pair<int, int> dir : direction) {
			int nxtR = r + dir.first;
			int nxtC = c + dir.second;
			if (nxtR < 1 || nxtR > height || nxtC < 1 || nxtC > width ||
				visit[nxtR][nxtC]) {
				continue;
			}

			if (board[nxtR][nxtC] == 0) {
				visit[nxtR][nxtC] = true;
				q.push({ nxtR, nxtC });
				externalVisitQ.push({ nxtR, nxtC });
			}
			else {
				externalAdjCnt[nxtR][nxtC]++;
			}
		}
	}
}

void findMeltCheese() {
	for (int i = 0; i < cheeseVec.size(); i++) {
		int r = cheeseVec[i].first;
		int c = cheeseVec[i].second;
		if (externalAdjCnt[r][c] >= 2) {
			cheeseVec.erase(cheeseVec.begin() + i);
			board[r][c] = 0;
			i--;
		}
		externalAdjCnt[r][c] = 0;
	}
}

void go(int hr) {
	bfs();
	findMeltCheese();
	if (cheeseVec.size() != 0) {
		go(hr + 1);
	}
	else {
		ans = hr;
		return;
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> height >> width;

	for (int i = 1; i <= height; i++) {
		for (int j = 1; j <= width; j++) {
			cin >> board[i][j];
			if (board[i][j] == 1) {
				cheeseVec.push_back({ i, j });
			}
		}
	}

	if (cheeseVec.size() != 0) {
		go(1);
	}

	cout << ans;

	return 0;
}
