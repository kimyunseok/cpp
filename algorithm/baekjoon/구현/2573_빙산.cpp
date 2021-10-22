/*
* 백준 2573번 빙산
* https://www.acmicpc.net/problem/2573
* 구현 / 그래프 탐색 이론
*/
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int height, width;
int iceAge[301][301];
bool visit[301][301];
int ans;
vector<pair<int, int>> icePoint;
queue<pair<int, pair<int, int>>> q;
pair<int, int> direction[4] = {
	{-1, 0},
	{1, 0},
	{0, -1},
	{0, 1}
};

void findZeroCnt() {
	for (int i = 0; i < icePoint.size(); i++) {
		int r = icePoint[i].first;
		int c = icePoint[i].second;

		visit[r][c] = false; // 겸사겸사초기화

		if (iceAge[r][c] == 0) {
			icePoint.erase(icePoint.begin() + i);
			i--;
			continue;
		}

		int adjZero = 0;
		for (pair<int, int> dir : direction) {
			int adjR = r + dir.first;
			int adjC = c + dir.second;

			if (adjR <= 0 || adjR > height || adjC <= 0 || adjC > width) { continue; }

			if (iceAge[adjR][adjC] == 0) { adjZero++; }
		}

		q.push({ adjZero, {r, c} });
	}
}

void minusAdjZeroCnt() {
	while (!q.empty()) {
		int minusNum = q.front().first;
		int r = q.front().second.first;
		int c = q.front().second.second;
		q.pop();
		iceAge[r][c] -= minusNum;
		if (iceAge[r][c] < 0) { iceAge[r][c] = 0; }
	}
}

void dfs(int r, int c) {
	visit[r][c] = true;

	for (pair<int, int> dir : direction) {
		int adjR = r + dir.first;
		int adjC = c + dir.second;

		if (adjR <= 0 || adjR > height || adjC <= 0 || adjC > width ||
			iceAge[adjR][adjC] == 0 || visit[adjR][adjC]) {
			continue;
		}

		dfs(adjR, adjC);
	}
}

bool checkSeparate() {
	int connectedComponents = 0;

	for (int i = 0; i < icePoint.size(); i++) {
		int r = icePoint[i].first;
		int c = icePoint[i].second;
		if (!visit[r][c] && iceAge[r][c] > 0) {
			connectedComponents++;
			dfs(r, c);
		}
	}
	return (connectedComponents >= 2);
}

int go(int curYear) {
	findZeroCnt();

	if (q.size() == 0) { return -1; }

	minusAdjZeroCnt();

	if (checkSeparate()) {
		return curYear;
	}
	else {
		return go(curYear + 1);
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> height >> width;

	for (int i = 1; i <= height; i++) {
		for (int j = 1; j <= width; j++) {
			cin >> iceAge[i][j];
			if (iceAge[i][j] > 0) { icePoint.push_back({ i, j }); }
		}
	}

	if (!checkSeparate()) {
		ans = go(1);
	}

	if (ans != -1) {
		cout << ans;
	}
	else {
		cout << 0;
	}

	return 0;
}
