/*
* 백준 2636번 치즈
* https://www.acmicpc.net/problem/2636
* 그래프 탐색 - 너비 우선 탐색 / 구현 / 시뮬레이션
*/
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int height, width;
bool visit[101][101];
int map[101][101];
int currentCheeseCnt;
int totalMeltingTime, previousOneHour;
pair<int, int> directions[4] = {
	{-1, 0},
	{0, 1},
	{1, 0},
	{0, -1}
};
vector<pair<int, int>> meltingPointVec;

void bfs(int r, int c) {
	queue<pair<int, int>> q;
	q.push({ r,c });
	visit[r][c] = true;
	while (!q.empty()) {
		int currentR = q.front().first;
		int currentC = q.front().second;
		q.pop();

		for (pair<int, int> dir : directions) {
			int nextR = currentR + dir.first;
			int nextC = currentC + dir.second;

			if (nextR < 1 || nextR > height || nextC < 1 
				|| nextC > width || visit[nextR][nextC]) {
				continue;
			}

			visit[nextR][nextC] = true;
			if (map[nextR][nextC] == 1) {
				meltingPointVec.push_back({ nextR, nextC });
			}
			else {
				q.push({ nextR, nextC });
			}
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
			cin >> map[i][j];
			if (map[i][j] == 1) { currentCheeseCnt++; }
		}
	}

	while (currentCheeseCnt) {
		for (int i = 1; i <= height; i++) {
			for (int j = 1; j <= width; j++) {
				visit[i][j] = false;
			}
		}
		meltingPointVec.clear();

		bfs(1, 1);

		previousOneHour = currentCheeseCnt;

		for (pair<int, int> point : meltingPointVec) {
			int r = point.first;
			int c = point.second;

			map[r][c] = 0;
			currentCheeseCnt--;
		}

		totalMeltingTime++;
	}

	cout << totalMeltingTime << "\n" << previousOneHour;

	return 0;
}