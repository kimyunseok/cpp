/*
* 백준 {문제번호} {문제이름}
* https://www.acmicpc.net/problem/{문제번호}
* 문제 유형
*/
#include <iostream>
#include <queue>

using namespace std;

queue<pair<pair<int, int>, int>> dochiQ;
queue<pair<int, int>> waterQ[2501];
int height, width;
pair<int, int> bieberHomePoint;
pair<int, int> dochiPoint;
char map[51][51];
bool dochiVisit[51][51];
bool waterVisit[51][51];
pair<int, int> directions[4] = {
	{-1, 0},
	{0, 1},
	{1, 0},
	{0, -1}
};
bool canFindTime;
int ans = 1000000000;

void findMinTime() {
	dochiVisit[dochiQ.front().first.first][dochiQ.front().first.second] = true;
	while (!dochiQ.empty()) {
		int dochiR = dochiQ.front().first.first;
		int dochiC = dochiQ.front().first.second;
		int arriveTime = dochiQ.front().second;
		dochiQ.pop();

		if (dochiR == bieberHomePoint.first && dochiC == bieberHomePoint.second) {
			ans = arriveTime;
			canFindTime = true;
			break;
		}

		while (!waterQ[arriveTime].empty()) {
			int waterR = waterQ[arriveTime].front().first;
			int waterC = waterQ[arriveTime].front().second;
			int nxtTime = arriveTime + 1;
			waterQ[arriveTime].pop();

			for (pair<int, int> dir : directions) {
				int nxtR = waterR + dir.first;
				int nxtC = waterC + dir.second;
				if (nxtR < 1 || nxtR > height || nxtC < 1 || nxtC > width ||
					waterVisit[nxtR][nxtC] || map[nxtR][nxtC] == 'D' || map[nxtR][nxtC] == 'X') {
					continue;
				}

				waterVisit[nxtR][nxtC] = true;
				map[nxtR][nxtC] = '*';
				waterQ[nxtTime].push({ nxtR, nxtC });
			}
		}

		for (pair<int, int> dir : directions) {
			int nxtR = dochiR + dir.first;
			int nxtC = dochiC + dir.second;

			if (nxtR < 1 || nxtR > height || nxtC < 1 || nxtC > width ||
				dochiVisit[nxtR][nxtC] || map[nxtR][nxtC] == 'X' || map[nxtR][nxtC] == '*') {
				continue;
			}

			dochiVisit[nxtR][nxtC] = true;
			dochiQ.push({ {nxtR, nxtC}, arriveTime + 1 });
		}
	}
}

int main() {
	cin >> height >> width;

	for (int i = 1; i <= height; i++) {
		for (int j = 1; j <= width; j++) {
			cin >> map[i][j];
			if (map[i][j] == '*') {
				waterQ[0].push({ i, j });
				waterVisit[i][j] = true;
			} else if (map[i][j] == 'S') {
				dochiQ.push({ { i, j }, 0 });
				map[i][j] = '.';
				dochiVisit[i][j] = true;
			}
			else if (map[i][j] == 'D') {
				bieberHomePoint.first = i;
				bieberHomePoint.second = j;
			}
		}
	}
	
	findMinTime();

	if (!canFindTime) {
		cout << "KAKTUS";
	}
	else {
		cout << ans;
	}

	return 0;
}